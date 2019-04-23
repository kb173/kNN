#include "KFold.h"
#include <cstdlib>
#include <tgmath.h>
#include <iostream>

std::vector<std::vector<std::vector<double>>> KFold::getFoldedDataBlocks(std::vector<std::vector<double>> data,
                                                                         int kValue) {
    std::vector<std::vector<std::vector<double>>> dataBlocks;

    // find out the block size for this data set and round up so every data gets used
    int blockSize = ceil((float) data.size() / (float) kValue);

    // a new block to be pushed back into the list of all k blocks
    std::vector<std::vector<double>> block;

    while (data.size() != 0) {
        // grab a random number to get a random entry of the dataset and push it to our new block then delete the entry
        int randomNum = (int) rand() % data.size();
        std::vector<double> randomEntry = data[randomNum];
        data.erase(data.begin() + randomNum);
        block.push_back(randomEntry);

        // if the block has the appropriate size or if there are no more entries left push it to our list of blocks
        // and clear the block for new entries
        if (block.size() == blockSize || data.size() == 0) {
            dataBlocks.push_back(block);
            block.clear();
        }
    }

    return dataBlocks;
}

