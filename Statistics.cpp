#include <cmath>
#include <climits>
#include <iostream>
#include "Statistics.h"

void ZScore::standardize(std::vector<std::vector<double>> &data) {
    int rows = data.size();
    int cols = data.front().size();

    // 1 is subtracted from cols because the last column are the classes (which are supposed to stay integers)
    int colMax = cols - 1;

    for (int col = 0; col < colMax; col++) {
        double mean = getMeanOfCol(data, col);
        double stdDev = getStdDeviationOfCol(data, col);

        for (int row = 0; row < rows; row++) {
            data[row][col] = (data[row][col] - mean) / stdDev;
        }
    }
}

double ZScore::getMeanOfCol(const std::vector<std::vector<double>> &data, int col) {
    int rows = data.size();
    double sum = 0;

    for (int i = 0; i < rows; i++) {
        sum += data[i][col];
    }

    return sum / rows;
}

double ZScore::getStdDeviationOfCol(const std::vector<std::vector<double>> &data, int col) {
    int rows = data.size();
    double variance = 0;

    double mean = getMeanOfCol(data, col);

    for (int i = 0; i < rows; i++) {
        variance += std::pow(data[i][col] - mean, 2);
    }

    return std::sqrt(variance / (rows - 1));
}

std::list<std::shared_ptr<Point>> ZScore::twoDimVectorToPoints(const std::vector<std::vector<double>> &data) {
    auto points = std::list<std::shared_ptr<Point>>();

    int rows = data.size();
    int cols = data.front().size();

    // 1 is subtracted from cols because the last column are the classes (which are supposed to stay integers)
    int colMax = cols - 1;

    for (int row = 0; row < rows; row++) {
        std::vector<double> coordinates = std::vector<double>();

        for (int col = 0; col < colMax; col++) {
            coordinates.push_back(data[row][col]);
        }

        int classification = (int) data[row].back();

        points.push_back(std::make_shared<ClassifiedPoint>(ClassifiedPoint(coordinates, classification)));
    }

    return points;
}

std::map<int, std::map<int, int>> ConfusionMatrix::getConfusionMatrix(std::list<std::vector<int>> guessExpectList) {
    std::map<int, std::map<int, int>> confusionMatrix = std::map<int, std::map<int, int>>();

    for (const auto &guessedExpected : guessExpectList) {
        int guessed = guessedExpected.front();
        int expected = guessedExpected.back();


        confusionMatrix[guessed][expected]++;
    }

    return confusionMatrix;
}

void ConfusionMatrix::printConfusionMatrix(std::map<int, std::map<int, int>> confusionMatrix) {

    int min = INT_MAX;
    int max = 0;

    for (auto const &row : confusionMatrix) {
        for (auto const &col : row.second) {
            if (row.first < min) {
                min = row.first;
            }

            if (row.first > max) {
                max = row.first;
            }

            if (col.first < min) {
                min = col.first;
            }

            if (col.first > max) {
                max = col.first;
            }
        }
    }


    for (int row = min; row <= max; row++) {
        for (int col = min; col <= max; col++) {
            std::cout << confusionMatrix[row][col] << "\t";
        }

        std::cout << std::endl;
    }


}


float Statistics::getAccuracy(std::map<int, std::map<int, int>> confusionMatrix) {
    int goodGuesses = 0;
    int totalGuesses = 0;

    for (auto const &row : confusionMatrix) {
        for (auto const &col : row.second) {
            totalGuesses += col.second;

            if (row.first == col.first) {
                goodGuesses += col.second;
            }
        }
    }

    return ((float) goodGuesses / (float) totalGuesses);
}