//
// Created by mathias on 23.04.19.
//

#ifndef KNN_CROSSVALIDATOR_H
#define KNN_CROSSVALIDATOR_H

#include <vector>

class CrossValidator {
public:
    void kCrossValidation(std::vector<std::vector<double>> data, int kValue);
    std::vector<std::vector<std::vector<double>>> getDataBlocks();

private:
    std::vector<std::vector<std::vector<double>>> dataBlocks;
};


#endif //KNN_CROSSVALIDATOR_H
