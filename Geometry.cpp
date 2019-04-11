#include "Geometry.h"

const std::vector<double> &Point::getCoordinates() const {
    return coordinates;
}

void Point::setCoordinates(const std::vector<double> &coordinates) {
    Point::coordinates = coordinates;
}

double EuklidianPointDistance::getDistance(const Point &point1, const Point &point2) {
    return 0;
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
