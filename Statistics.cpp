#include <cmath>
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

std::list<std::shared_ptr<Point>> ZScore::twoDimVectorToPoints(const std::vector<std::vector<double>> &) {
    return std::list<std::shared_ptr<Point>>();
}