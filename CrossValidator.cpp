//
// Created by mathias on 23.04.19.
//

#include "CrossValidator.h"
#include <cstdlib>
#include <tgmath.h>
#include <iostream>

void CrossValidator::kCrossValidation(std::vector<std::vector<double>> data, int kValue) {
    // find out the block size for this data set and round up so every data gets used
    int blockSize = ceil((float) data.size() / (float) kValue);

    // a new block to be pushed back into the list of all k blocks
    std::vector<std::vector<double>> block;

    while(data.size() != 0) {
        std::cout << data.size() << std::endl;

        // grab a random number to get a random entry of the dataset and push it to our new block then delete the entry
        int randomNum = (int) rand() % data.size();
        std::vector<double> randomEntry = data[randomNum];
        data.erase(data.begin() + randomNum);
        block.push_back(randomEntry);

        // if the block has the appropriate size or if there are no more entries left push it to our list of blocks
        // and clear the block for new entries
        if(block.size() == blockSize || data.size() == 0) {
            this->dataBlocks.push_back(block);
            block.clear();
        }
    }
}

std::vector<std::vector<std::vector<double>>> CrossValidator::getDataBlocks() {
    return this->dataBlocks;
}
