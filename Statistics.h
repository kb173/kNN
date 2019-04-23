#ifndef KNN_STATISTICS_H
#define KNN_STATISTICS_H

#include "Geometry.h"
#include <list>
#include <map>

class ClassifiedPoint : public Point {

public:
    ClassifiedPoint(std::vector<double> coordinates, int classification) : Point(std::move(coordinates)),
                                                                           classification(classification) {}

    int getClassification() const {
        return classification;
    }

protected:
    int classification;

};


class ZScore {

public:
    void standardize(std::vector<std::vector<double>> &);

    double getMeanOfCol(const std::vector<std::vector<double>> &, int);

    double getStdDeviationOfCol(const std::vector<std::vector<double>> &, int);

    std::list<std::shared_ptr<Point>> twoDimVectorToPoints(const std::vector<std::vector<double>> &);

};


class ConfusionMatrix {
public:
    std::map<int, std::map<int, int>> getConfusionMatrix(std::list<std::vector<int>> guessExpectList);
    void printConfusionMatrix(std::map<int, std::map<int, int>>);

};

class Statistics {
public:
    float getAccuracy(std::map<int, std::map<int, int>>);
};

#endif //KNN_STATISTICS_H
