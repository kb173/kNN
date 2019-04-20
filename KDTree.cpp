#include <utility>

#include <utility>

#include "KDTree.h"

std::shared_ptr<Point> KDTree::Node::getPoint() const {
    return point;
}

int KDTree::Node::getSplittingDim() const {
    return splitting_dim;
}

void KDTree::Node::setSplittingDim(int newDim) {
    splitting_dim = newDim;
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
    adaptBounds(point);

    std::shared_ptr<Node> new_node = std::make_shared<Node>(Node(point, 0));

    if (root == nullptr) {
        root = new_node;
        return;
    }

    std::shared_ptr<Node> current = root;
    int current_dimension = 0;

    while (true) {
        current_dimension++;
        current_dimension = current_dimension % current->getPoint()->getCoordinates().size();
        new_node->setSplittingDim(current_dimension);

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
    }
}

std::list<std::shared_ptr<Point>> KDTree::search(std::shared_ptr<Point> target, int amount) {
    PointHeap results = PointHeap(amount);

    searchRec(root, results, target, amount, *boundingRect);

    return results.getPoints();
}

std::list<std::shared_ptr<Point>> KDTree::getAllPoints() {
    auto points = std::list<std::shared_ptr<Point>>();

    getRec(root, points);

    return points;
}

void KDTree::getRec(const std::shared_ptr<KDTree::Node>& current, std::list<std::shared_ptr<Point>> &point_list) {
    if (current == nullptr) {
        return;
    }

    point_list.push_back(current->getPoint());

    getRec(current->getLeft(), point_list);
    getRec(current->getRight(), point_list);
}

bool KDTree::searchRec(const std::shared_ptr<KDTree::Node> &current, PointHeap &foundHeap,
                       const std::shared_ptr<Point> &target, int amount, Rectangle currentBounds) {
    if (current == nullptr) {
        return false;
    }

    auto distanceMeasurer = EuklidianPointDistance();
    double distance = distanceMeasurer.getDistance(current->getPoint(), target);

    foundHeap.add(current->getPoint(), distance);

    // Update the bounding rectangle and target circle
    Circle checkingCircle = Circle(target, foundHeap.getWorstDist());

    int splittingDim = current->getSplittingDim();

    Rectangle leftBounds = currentBounds;
    Rectangle rightBounds = currentBounds;
    double valueAtSplittingDim = current->getPoint()->getCoordinates()[splittingDim];

    std::shared_ptr<Point> newLeftBoundEnd = std::make_shared<Point>(*leftBounds.getEnd());
    newLeftBoundEnd->setCoordinate(splittingDim, valueAtSplittingDim);

    std::shared_ptr<Point> newRightBoundStart = std::make_shared<Point>(*rightBounds.getStart());
    newRightBoundStart->setCoordinate(splittingDim, valueAtSplittingDim);

    leftBounds.setEnd(newLeftBoundEnd);
    rightBounds.setStart(newRightBoundStart);

    // If the target is on the left, continue left first
    if (target->getCoordinates()[splittingDim] < valueAtSplittingDim) {
        bool done = searchRec(current->getLeft(), foundHeap, target, amount, leftBounds);

        // If it makes sense to continue searching right too, do that
        if (!done && RectangleCircleIntersection().intersects(rightBounds, checkingCircle)) {
            searchRec(current->getRight(), foundHeap, target, amount, rightBounds);
        }
    } else {
        bool done = searchRec(current->getRight(), foundHeap, target, amount, rightBounds);

        if (!done && RectangleCircleIntersection().intersects(leftBounds, checkingCircle)) {
            searchRec(current->getLeft(), foundHeap, target, amount, leftBounds);
        }
    }

    // Update checking circle
    checkingCircle = Circle(target, foundHeap.getWorstDist());

    return RectangleCircleEncasement().encases(currentBounds, checkingCircle);
}

void KDTree::adaptBounds(const std::shared_ptr<Point> &adaptTo) {
    int dimension = adaptTo->getCoordinates().size();

    if (boundingRect == nullptr) {
        // If the bounding rectangle hasn't been initialized, copy the adaptTo point into its start and end variables
        boundingRect = std::make_unique<Rectangle>(Rectangle());

        boundingRect->setStart(std::make_shared<Point>(*adaptTo));
        boundingRect->setEnd(std::make_shared<Point>(*adaptTo));
    } else {
        // Expand the bounding rectangle wherever needed
        for (int i = 0; i < dimension; i++) {
            double valueAtCoordinate = adaptTo->getCoordinates()[i];

            if (valueAtCoordinate < boundingRect->getStart()->getCoordinates()[i]) {
                boundingRect->getStart()->setCoordinate(i, valueAtCoordinate);
            } else if (valueAtCoordinate > boundingRect->getEnd()->getCoordinates()[i]) {
                boundingRect->getEnd()->setCoordinate(i, valueAtCoordinate);
            }
        }
    }
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
