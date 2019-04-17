#ifndef KNN_GEOMETRY_H
#define KNN_GEOMETRY_H

#include <vector>
#include <utility>
#include <memory>

class Point {

public:
    Point(std::vector<double> coordinates) : coordinates(std::move(coordinates)) {}

    virtual ~Point() = default;

    const std::vector<double> &getCoordinates() const;

    void setCoordinates(const std::vector<double> &coordinates);

protected:
    std::vector<double> coordinates;

};


class IPointDistance {

public:
    virtual double getDistance(std::shared_ptr<Point> point1, std::shared_ptr<Point> point2) = 0;

};


class EuklidianPointDistance : public IPointDistance {

public:
    double getDistance(std::shared_ptr<Point> point1, std::shared_ptr<Point> point2) override;

};

class Rectangle {

public:
    const std::shared_ptr<Point> &getStart() const;

    void setStart(const std::shared_ptr<Point> &start);

    const std::shared_ptr<Point> &getEnd() const;

    void setEnd(const std::shared_ptr<Point> &end);

private:
    std::shared_ptr<Point> start;

    std::shared_ptr<Point> end;

};

class Circle {

public:
    const std::shared_ptr<Point> &getOrigin() const;

    void setOrigin(const std::shared_ptr<Point> &origin);

    double getRadius() const;

    void setRadius(double radius);

private:
    std::shared_ptr<Point> origin;

    double radius;

};

class RectangleCircleIntersection {

public:
    bool intersects(Rectangle rect, Circle circ);

};

class RectangleCircleEncasement {

public:
    bool encases(Rectangle rect, Circle circ);

};

#endif //KNN_GEOMETRY_H
