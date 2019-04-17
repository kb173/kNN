#include <stdexcept>
#include <cmath>
#include "Geometry.h"

const std::vector<double> &Point::getCoordinates() const {
    return coordinates;
}

void Point::setCoordinates(const std::vector<double> &coordinates) {
    Point::coordinates = coordinates;
}

double EuklidianPointDistance::getDistance(std::shared_ptr<Point> point1, std::shared_ptr<Point> point2) {
    int p1_dimension = point1->getCoordinates().size();
    int p2_dimension = point2->getCoordinates().size();

    if (p1_dimension != p2_dimension) {
        throw std::invalid_argument("Points need to have the same dimension (number of coordinates)"
                                    "to be able to measure distances!");
    }

    double squared_sum = 0;

    for (int i = 0; i < p1_dimension; i++) {
        squared_sum += std::pow(point1->getCoordinates()[i] - point2->getCoordinates()[i], 2);
    }

    return std::sqrt(squared_sum);
}

bool Rect::intersects(const Shape &other) {
    return false;
}

bool Rect::encases(const Shape &other) {
    return false;
}

bool Circ::intersects(const Shape &other) {
    return false;
}

bool Circ::encases(const Shape &other) {
    return false;
}
