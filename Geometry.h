#ifndef KNN_GEOMETRY_H
#define KNN_GEOMETRY_H

#include <vector>
#include <utility>

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
    virtual double getDistance(const Point &point1, const Point &point2) = 0;

};


class EuklidianPointDistance : public IPointDistance {

public:
    double getDistance(const Point &point1, const Point &point2) override;

};


class Shape {

public:
    explicit Shape(Point origin) : origin(std::move(origin)) {}

    virtual ~Shape() = default;

    virtual bool intersects(const Shape &other) = 0;

    virtual bool encases(const Shape &other) = 0;

protected:
    Point origin;

};


class Rect : public Shape {

public:
    Rect(const Point &origin, Point end) : Shape(origin), end(std::move(end)) {}

    virtual ~Rect() = default;

    bool intersects(const Shape &other) override;

    bool encases(const Shape &other) override;

private:
    Point end;

};


class Circ : public Shape {

public:
    Circ(const Point &origin, double radius) : Shape(origin), radius(radius) {}

    virtual ~Circ() = default;

    bool intersects(const Shape &other) override;

    bool encases(const Shape &other) override;

private:
    double radius;

};


#endif //KNN_GEOMETRY_H
