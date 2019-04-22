//
// Created by karl on 21.04.19.
//

#ifndef KNN_KDTREEPREPARATION_H
#define KNN_KDTREEPREPARATION_H


#include "Geometry.h"
#include "KDTree.h"
#include <list>

class KDTreePreparation {

public:
    KDTreePreparation() = default;

    void insertSorted(std::list<std::shared_ptr<Point>>, IKDTree &);

};


#endif //KNN_KDTREEPREPARATION_H
