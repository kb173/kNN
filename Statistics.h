#ifndef KNN_STATISTICS_H
#define KNN_STATISTICS_H

#include "Geometry.h"

class ClassifiedPoint : public Point {

public:
    ClassifiedPoint(std::vector<double> coordinates, int classification) : Point(std::move(coordinates)),
                                                                           classification(classification) {}

protected:
    int classification;

};

#endif //KNN_STATISTICS_H
