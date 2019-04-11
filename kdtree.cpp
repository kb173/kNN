#include <utility>

#include "KDTree.h"

const Point &KDTree::Node::getPoint() const {
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

void KDTree::insert(const Point &point) {
    std::shared_ptr<Node> new_node = std::make_shared<Node>(Node(point, 0)); // TODO: Fix splitting dim

    if (root == nullptr) {
        root = new_node;
        return;
    }

    std::shared_ptr<Node> current = root;
    int current_dimension = 0;

    while (true) {
        if (new_node->getPoint().getCoordinates()[current_dimension] <
            current->getPoint().getCoordinates()[current_dimension]) {
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
        current_dimension = current_dimension % current->getPoint().getCoordinates().size();

    }
}

std::list<Point> KDTree::search(const Point &target, int amount) {
    return std::list<Point>();
}

std::list<Point> KDTree::getAllPoints() {
    std::list<Point> points = std::list<Point>();

    get_rec(root, points);

    return points;
}

void KDTree::get_rec(std::shared_ptr<KDTree::Node> current, std::list<Point> &point_list) {
    if (current == nullptr) {
        return;
    }

    point_list.push_back(current->getPoint());

    get_rec(current->getLeft(), point_list);
    get_rec(current->getRight(), point_list);
}