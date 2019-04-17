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

const std::shared_ptr<Point> &Rectangle::getStart() const {
    return start;
}

void Rectangle::setStart(const std::shared_ptr<Point> &start) {
    Rectangle::start = start;
}

const std::shared_ptr<Point> &Rectangle::getEnd() const {
    return end;
}

void Rectangle::setEnd(const std::shared_ptr<Point> &end) {
    Rectangle::end = end;
}

const std::shared_ptr<Point> &Circle::getOrigin() const {
    return origin;
}

void Circle::setOrigin(const std::shared_ptr<Point> &origin) {
    Circle::origin = origin;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(double radius) {
    Circle::radius = radius;
}

bool RectangleCircleIntersection::intersects(Rectangle rect, Circle circ) {
    return false;
}

bool RectangleCircleEncasement::encases(Rectangle rect, Circle circ) {
    return false;
}
