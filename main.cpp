#include <iostream>
#include "KFold.h"
#include "CSVReader.h"
#include "Statistics.h"
#include "KDTree.h"
#include "KDTreePreparation.h"
#include "CrossValidation.h"
#include <map>

double randomCoordinate() {
    return (0.5 - ((double) rand() / (RAND_MAX))) * 3.0;
}

int performanceTest() {
        CSVReader reader;
    std::vector<std::vector<double>> data = reader.readAs2dArray(
            "/home/karl/Data/Technikum/SEM4/MLE/kNN/datasets/winequality-red.csv", ';');
    ZScore().standardize(data);

    KDTree kdtree = KDTree();

    auto sortable = ZScore().twoDimVectorToPoints(data);
    KDTreePreparation().insertSorted(sortable, kdtree);

    int amount = 1500;
    int k = 40;

    clock_t searchBegin = clock();
    for (int i = 0; i < amount; i++) {
        ClassifiedPoint searchPoint = ClassifiedPoint(std::vector<double>{randomCoordinate(), randomCoordinate(),
                                                                          randomCoordinate(), randomCoordinate(),
                                                                          randomCoordinate(), randomCoordinate(),
                                                                          randomCoordinate(), randomCoordinate(),
                                                                          randomCoordinate(), randomCoordinate(),
                                                                          randomCoordinate()}, 5);

        std::shared_ptr search = std::make_shared<Point>(searchPoint);
        kdtree.search(search, k);
    }

    clock_t searchEnd = clock();
    auto elapsedTime = double(searchEnd - searchBegin) / 1000000;
    std::cout << "Training took " << elapsedTime << " seconds!" << std::endl;

    return 0;
}

int main() {
    CSVReader reader;
    std::vector<std::vector<double>> data = reader.readAs2dArray("/home/karl/Data/Technikum/SEM4/MLE/kNN/datasets/winequality-red.csv", ';');
    ZScore().standardize(data);
    KFold validator;
    std::vector<std::vector<std::vector<double>>> blocks = validator.getFoldedDataBlocks(data, 10);

    int k = 30; // k points are evaluated (as in kNN)

    clock_t validateBegin = clock();

    std::list<std::vector<int>> guessExpectList = CrossValidation().getGuessedVersusExpected(blocks, k);

    clock_t validateEnd = clock();

    auto elapsedTime = double(validateEnd - validateBegin);

    std::cout << "Validating took " << elapsedTime << std::endl;

    auto confusionMatrix = std::map<int, std::map<int, int>>();

    // TODO: Proper classes
    // TODO: general confusion matrix
    /*int guessedmin = std::numeric_limits<int>();
    int guessedmax = 0;*/

    int goodGuesses = 0;
    int totalGuesses = guessExpectList.size();

    for(const auto& guessedExpected : guessExpectList) {
        int guessed = guessedExpected.front();
        int expected = guessedExpected.back();

        if (guessed == expected) {
            goodGuesses++;
        }

        // if (guessed < guessMin)

        confusionMatrix[guessed][expected]++;
    }

    std::cout << "Accuracy: " << (float)goodGuesses / (float)totalGuesses << std::endl;

    for (int row = 3; row < 10; row++) {
        for (int col = 3; col < 10; col++) {
            std::cout << confusionMatrix[row][col] << "\t";
        }

        std::cout << std::endl;
    }

    return 0;
}