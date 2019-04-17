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
    auto results = std::list<std::shared_ptr<Point>>();

    searchRec(root, results, target, amount);

    return results;
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

void KDTree::searchRec(std::shared_ptr<KDTree::Node> current, std::list<std::shared_ptr<Point>> &foundList,
                       std::shared_ptr<Point> target, int amount) {
    if (current == nullptr) {
        return;
    }

    searchRec(current->getLeft(), foundList, target, amount);
    searchRec(current->getRight(), foundList, target, amount);
}
