#include <iostream>
#include "KFold.h"
#include "CSVReader.h"
#include "Statistics.h"
#include "KDTree.h"
#include "KDTreePreparation.h"
#include "CrossValidation.h"
#include <map>
#include <climits>

int main() {
    CSVReader reader;
    std::vector<std::vector<double>> data = reader.readAs2dArray("/home/mathias/Documents/FH/sem_4/MLE/kNN/winequality-red.csv", ';');
    ZScore().standardize(data);
    KFold validator;
    std::vector<std::vector<std::vector<double>>> blocks = validator.getFoldedDataBlocks(data, 10);

    int k = 9; // k points are evaluated (as in kNN)

    clock_t validateBegin = clock();

    std::list<std::vector<int>> guessExpectList = CrossValidation().getGuessedVersusExpected(blocks, k);

    clock_t validateEnd = clock();

    auto elapsedTime = double(validateEnd - validateBegin);

    std::cout << "Validating took " << elapsedTime << std::endl;


    std::cout << std::endl << std::endl;
    auto confusionMatrix = std::map<int, std::map<int, int>>();
    auto confusionMatrix2 = std::map<int, std::map<int, int>>();

    confusionMatrix = ConfusionMatrix().getConfusionMatrix(guessExpectList);
    ConfusionMatrix().printConfusionMatrix(confusionMatrix);
    float accuracy = Statistics().getAccuracy(confusionMatrix);
    std::cout << "Accuracy: " << accuracy << std::endl;


    return 0;
}