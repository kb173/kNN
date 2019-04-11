#include <utility>

#include <utility>

#ifndef KNN_KDTREE_H
#define KNN_KDTREE_H

#include <list>
#include "Geometry.h"
#include <vector>
#include <utility>
#include <memory>


class IKDTree {

public:
    virtual void insert(const Point &point) = 0;

    virtual std::list<Point> search(const Point &target, int amount) = 0;

    virtual std::list<Point> getAllPoints() = 0;

};


class KDTree : public IKDTree {

public:
    KDTree() : bounding_rect(Rect(Point(std::vector<double>(0, 0)), Point(std::vector<double>(0, 0)))) {}

    virtual ~KDTree() = default;

    void insert(const Point &point) override;

    std::list<Point> search(const Point &target, int amount);

    std::list<Point> getAllPoints();

private:
    class Node {

    public:
        Node(const Point& point, int splitting_dim) : point(point), splitting_dim(splitting_dim) {};

        virtual ~Node() = default;

        const Point &getPoint() const;

        int getSplittingDim() const;

        const std::shared_ptr<Node> &getLeft() const;

        void setLeft(std::shared_ptr<Node> left);

        const std::shared_ptr<Node> &getRight() const;

        void setRight(std::shared_ptr<Node> right);

    protected:
        Point point;
        int splitting_dim;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

    };

    void get_rec(std::shared_ptr<Node> current, std::list<Point> &point_list);

    std::shared_ptr<Node> root;

    Rect bounding_rect;

};


#endif //KNN_KDTREE_H
