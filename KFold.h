//
// Created by mathias on 23.04.19.
//

#ifndef KNN_KFOLD_H
#define KNN_KFOLD_H

#include <vector>

class KFold {
public:
    std::vector<std::vector<std::vector<double>>> getFoldedDataBlocks(std::vector<std::vector<double>> data, int kValue);
};


#endif //KNN_KFOLD_H
