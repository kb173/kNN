//
// Created by mathias on 23.04.19.
//

#ifndef KNN_CROSSVALIDATION_H
#define KNN_CROSSVALIDATION_H


#include <list>
#include <vector>

class CrossValidation {
public:
    std::list<std::vector<int>> getGuessedVersusExpected (std::vector<std::vector<std::vector<double>>> blocks, int k);

private:
    int getMostCommon(const std::list<int>&);

};


#endif //KNN_CROSSVALIDATION_H
