#include <utility>

#include <stdexcept>
#include <cmath>
#include "Geometry.h"

const std::vector<double> &Point::getCoordinates() const {
    return coordinates;
}

void Point::setCoordinates(const std::vector<double> &coordinates) {
    Point::coordinates = coordinates;
}

void Point::setCoordinate(int dimension, double value) {
    coordinates[dimension] = value;
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

Rectangle::Rectangle() {
    start = std::make_shared<Point>(Point(std::vector<double>()));
    end = std::make_shared<Point>(Point(std::vector<double>()));
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

bool RectangleCircleIntersection::intersects(const Rectangle& rect, const Circle& circ) {
    int dimension = rect.getStart()->getCoordinates().size();

    // Get closest point within rectangle to circle
    std::vector<double> clampedCoordinates = std::vector<double>(dimension);

    for (int i = 0; i < dimension; i++)
    {
        // Make clamped be between the rectangle start and end
        if (circ.getOrigin()->getCoordinates()[i] < rect.getStart()->getCoordinates()[i])
        {
            clampedCoordinates[i] = rect.getStart()->getCoordinates()[i];
        } else if (circ.getOrigin()->getCoordinates()[i] > rect.getEnd()->getCoordinates()[i])
        {
            clampedCoordinates[i] = rect.getEnd()->getCoordinates()[i];
        } else
        {
            clampedCoordinates[i] = circ.getOrigin()->getCoordinates()[i];
        }
    }

    std::shared_ptr<Point> clampedPoint = std::make_shared<Point>(Point(clampedCoordinates));

    auto distanceMeasurer = EuklidianPointDistance();
    double distance = distanceMeasurer.getDistance(circ.getOrigin(), clampedPoint);

    // If distance is smaller than the circle radius, that means they're intersecting
    return distance < circ.getRadius();
}

bool RectangleCircleEncasement::encases(const Rectangle& rect, const Circle& circ) {
    return false;
}
