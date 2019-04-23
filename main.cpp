#include <iostream>
#include "CrossValidator.h"
#include "CSVReader.h"
#include "Statistics.h"

int main() {
    CSVReader reader;
    std::vector<std::vector<double>> data = reader.readAs2dArray("/home/mathias/Documents/FH/sem_4/MLE/kNN/winequality-red.csv", ';');
    ZScore().standardize(data);
    CrossValidator validator;
    validator.kCrossValidation(data, 10);
    std::vector<std::vector<std::vector<double>>> blocks = validator.getDataBlocks();

    std::cout << blocks.size() << std::endl << std::endl;


    


    return 0;
}