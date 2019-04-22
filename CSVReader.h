#ifndef KNN_CSVREADER_H
#define KNN_CSVREADER_H


#include <vector>
#include "Geometry.h"
#include <list>

class CSVReader {

public:
    std::vector<std::vector<double>> readAs2dArray(const std::string&, const char&);

};


#endif //KNN_CSVREADER_H
