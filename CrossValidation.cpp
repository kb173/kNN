//
// Created by mathias on 23.04.19.
//

#include <iostream>
#include "CrossValidation.h"
#include "Geometry.h"
#include "Statistics.h"
#include "KDTree.h"
#include "KDTreePreparation.h"
#include <map>
#include <algorithm>

std::list<std::vector<int>>
CrossValidation::getGuessedVersusExpected(std::vector<std::vector<std::vector<double>>> blocks, int k) {

    auto guessExpectList = std::list<std::vector<int>>();

    for (int testBlock = 0; testBlock < blocks.size(); testBlock++) {
        auto testPoints = ZScore().twoDimVectorToPoints(blocks[testBlock]);
        std::list<std::shared_ptr<Point>> trainingPoints = std::list<std::shared_ptr<Point>>();

        KDTree kdtree = KDTree();

        for (int trainingBlock = 0; trainingBlock < blocks.size(); trainingBlock++) {
            if (trainingBlock == testBlock) {
                continue;
            }

            trainingPoints.splice(trainingPoints.end(), ZScore().twoDimVectorToPoints(blocks[trainingBlock]));
        }

        KDTreePreparation().insertSorted(trainingPoints, kdtree);

        for (const auto &expected : testPoints) {
            std::shared_ptr<ClassifiedPoint> classifiedExpected = std::dynamic_pointer_cast<ClassifiedPoint>(expected);
            std::list<std::shared_ptr<Point>> guesses = kdtree.search(expected, k);

            int expectedClassification = classifiedExpected->getClassification();
            std::list<int> guessClassifications = std::list<int>();

            for (const auto &guess : guesses) {
                std::shared_ptr<ClassifiedPoint> classifiedGuess = std::dynamic_pointer_cast<ClassifiedPoint>(guess);

                guessClassifications.push_back(classifiedGuess->getClassification());
            }

            int guessedClassification = getMostCommon(guessClassifications);

            guessExpectList.push_back(std::vector<int>{guessedClassification, expectedClassification});
        }
    }

    return guessExpectList;
}

int CrossValidation::getMostCommon(const std::list<int> &intList) {
    std::map<int, int> occuranceCounts = std::map<int, int>();

    for (int element : intList) {
        occuranceCounts[element]++;
    }

    auto maxElement = std::max_element(occuranceCounts.begin(), occuranceCounts.end(),
                                       [](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
                                           return p1.second < p2.second;
                                       });

    return maxElement->first;
}
