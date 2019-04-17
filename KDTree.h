#include <utility>

#include <utility>

#include <utility>

#include <utility>

#ifndef KNN_KDTREE_H
#define KNN_KDTREE_H

#include <list>
#include "Geometry.h"
#include <vector>
#include <utility>
#include <memory>
#include <queue>


class IKDTree {

public:
    virtual void insert(std::shared_ptr<Point> point) = 0;

    virtual std::list<std::shared_ptr<Point>> search(std::shared_ptr<Point> target, int amount) = 0;

    virtual std::list<std::shared_ptr<Point>> getAllPoints() = 0;

};


class KDTree : public IKDTree {

public:
    KDTree() : bounding_rect(Rect(Point(std::vector<double>(0, 0)), Point(std::vector<double>(0, 0)))) {}

    virtual ~KDTree() = default;

    void insert(std::shared_ptr<Point> point) override;

    std::list<std::shared_ptr<Point>> search(std::shared_ptr<Point> target, int amount);

    std::list<std::shared_ptr<Point>> getAllPoints();

private:
    class Node {

    public:
        Node(std::shared_ptr<Point> point, int splitting_dim)
                : point(std::move(point)), splitting_dim(splitting_dim) {};

        virtual ~Node() = default;

        std::shared_ptr<Point> getPoint() const;

        int getSplittingDim() const;

        const std::shared_ptr<Node> &getLeft() const;

        void setLeft(std::shared_ptr<Node> left);

        const std::shared_ptr<Node> &getRight() const;

        void setRight(std::shared_ptr<Node> right);

    protected:
        std::shared_ptr<Point> point;
        int splitting_dim;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

    };

    class pointHeap {
    private:
        class pointHeapEntry {
        public:
            std::shared_ptr<Point> point;
            double dist;

            pointHeapEntry(std::shared_ptr<Point> p, double d) : point(std::move(p)), dist(d) {};

            ~pointHeapEntry() = default;
        };

        // Lambda expression for comparing in priority queue
        struct compare {
            bool operator()(const pointHeapEntry &p1, const pointHeapEntry &p2) {
                return p1.dist < p2.dist;
            }
        };

        std::priority_queue<pointHeapEntry, std::vector<pointHeapEntry>, compare> heap;
        int amount;

    public:
        explicit pointHeap(int a) : amount(a) {};

        bool add(std::shared_ptr<Point> p, double dist);

        double getWorstDist();

        std::list<std::shared_ptr<Point>> getPoints();
    };

    void getRec(std::shared_ptr<Node> current, std::list<std::shared_ptr<Point>> &point_list);

    void searchRec(std::shared_ptr<KDTree::Node> current, pointHeap &foundHeap,
                   std::shared_ptr<Point> target, int amount);

    std::shared_ptr<Node> root;

    Rect bounding_rect;

};


#endif //KNN_KDTREE_H
