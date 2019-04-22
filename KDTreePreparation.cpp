//
// Created by karl on 21.04.19.
//

#include "KDTreePreparation.h"
#include <algorithm>

void KDTreePreparation::insertSorted(std::list<std::shared_ptr<Point>> list, IKDTree &kdtree) {
    int dimension = list.begin()->get()->getCoordinates().size();
    int currentDimension = 0;

    // Turn the list into a vector because it's more efficient to get the median from a vector
    std::vector<std::shared_ptr<Point>> pointVector{ std::begin(list), std::end(list) };

    for (int i = 0; i < list.size(); i++) {
        // Sort the list based on the median point of the current dimension
        std::sort(pointVector.begin(), pointVector.end(),
                  [i](const std::shared_ptr<Point> &a, const std::shared_ptr<Point> &b) -> bool {
                      return a->getCoordinates()[i] < b->getCoordinates()[i];
                  });

        // Insert the median
        kdtree.insert(pointVector[pointVector.size() / 2]);
        pointVector.erase(pointVector.begin() + pointVector.size() / 2);

        // Increment current dimension
        currentDimension++;
        currentDimension = currentDimension % dimension;
    }
}
