#include <utility>

#include <utility>

#include "KDTree.h"

std::shared_ptr<Point> KDTree::Node::getPoint() const {
    return point;
}

int KDTree::Node::getSplittingDim() const {
    return splitting_dim;
}

const std::shared_ptr<KDTree::Node> &KDTree::Node::getLeft() const {
    return left;
}

void KDTree::Node::setLeft(std::shared_ptr<KDTree::Node> left) {
    Node::left = std::move(left);
}

const std::shared_ptr<KDTree::Node> &KDTree::Node::getRight() const {
    return right;
}

void KDTree::Node::setRight(std::shared_ptr<KDTree::Node> right) {
    Node::right = std::move(right);
}

void KDTree::insert(std::shared_ptr<Point> point) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(Node(point, 0)); // TODO: Fix splitting dim

    if (root == nullptr) {
        root = new_node;
        return;
    }

    std::shared_ptr<Node> current = root;
    int current_dimension = 0;

    while (true) {
        // Go right or left depending on the current dimension, then recurse of insert
        if (new_node->getPoint()->getCoordinates()[current_dimension] <
            current->getPoint()->getCoordinates()[current_dimension]) {
            if (current->getLeft() == nullptr) {
                current->setLeft(new_node);
                return;
            } else {
                current = current->getLeft();
            }
        } else {
            if (current->getRight() == nullptr) {
                current->setRight(new_node);
                return;
            } else {
                current = current->getRight();
            }
        }

        current_dimension++;
        current_dimension = current_dimension % current->getPoint()->getCoordinates().size();

    }
}

std::list<std::shared_ptr<Point>> KDTree::search(std::shared_ptr<Point> target, int amount) {
    PointHeap results = PointHeap(amount);

    searchRec(root, results, target, amount);

    return results.getPoints();
}

std::list<std::shared_ptr<Point>> KDTree::getAllPoints() {
    auto points = std::list<std::shared_ptr<Point>>();

    getRec(root, points);

    return points;
}

void KDTree::getRec(std::shared_ptr<KDTree::Node> current, std::list<std::shared_ptr<Point>> &point_list) {
    if (current == nullptr) {
        return;
    }

    point_list.push_back(current->getPoint());

    getRec(current->getLeft(), point_list);
    getRec(current->getRight(), point_list);
}

void KDTree::searchRec(std::shared_ptr<KDTree::Node> current, PointHeap &foundHeap,
                       std::shared_ptr<Point> target, int amount) {
    if (current == nullptr) {
        return;
    }

    auto distanceMeasurer = EuklidianPointDistance();
    double distance = distanceMeasurer.getDistance(current->getPoint(), target);

    foundHeap.add(current->getPoint(), distance);

    searchRec(current->getLeft(), foundHeap, target, amount);
    searchRec(current->getRight(), foundHeap, target, amount);
}

bool KDTree::PointHeap::add(std::shared_ptr<Point> p, double dist) {
    if (dist < getWorstDist()) {
        if (heap.size() == amount) {
            heap.pop();
        }
        heap.push(PointHeapEntry(std::move(p), dist));
        return true;
    }

    return false; // Heap is full and dist of new point is greater than dist of furthest point in heap
}

double KDTree::PointHeap::getWorstDist() {
    // Return infinity if heap is not full, worst distance if full
    if (heap.size() < amount)
        return std::numeric_limits<double>::max();

    return heap.top().dist;
}

std::list<std::shared_ptr<Point>> KDTree::PointHeap::getPoints() {
    std::list points = std::list<std::shared_ptr<Point>>();

    while (!heap.empty()) {
        points.push_back(heap.top().point);
        heap.pop();
    }

    return points;
}
