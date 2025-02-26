#ifndef PHYSICSENGINE_TOPDOWN_H
#define PHYSICSENGINE_TOPDOWN_H

#include "include/collisions/utils/AABB.h"


class BVTreeNode {
public:
    bool isLeaf;
    BVTreeNode *right;
    BVTreeNode *left;
    AABB BV;


};


class TopDownBVTree {
public:

    BVTreeNode root;
    TopDownBVTree();
    ~TopDownBVTree();




};







class PartitioningMethods {




};




#endif //PHYSICSENGINE_TOPDOWN_H
