#include <fstream>
#include <sstream>
#include "CSVReader.h"

std::vector<std::vector<double>> CSVReader::readAs2dArray(const std::string &filepath, const char &separator) {
    auto data = std::vector<std::vector<double>>();
    std::ifstream file(filepath);
    std::string line;

    while (getline(file, line)) {
        std::vector<double> row;

        std::stringstream iss(line);
        std::string val;

        while (getline(iss, val, separator)) {
            // no need for converting as you are reading string.
            row.push_back(std::stod(val));
        }

        data.push_back(row);
    }

    return data;
}
