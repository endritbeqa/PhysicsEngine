/*
Spatial Median (Middle Split)
The splitting plane is placed at the median of the bounding volume along a chosen axis.
Objects are assigned to the left or right child based on their centroids.
Pros: Simple to implement, ensures balanced trees.
Cons: Does not consider object distribution, which can lead to inefficient partitions.

Object Median (Median Cut)
Objects are sorted along a selected axis, and then split at the median index.
Ensures an equal number of objects in each child node.
Pros: Keeps the tree balanced.
Cons: Can create large overlapping bounding boxes, reducing efficiency.

Surface Area Heuristic (SAH)
Chooses a split that minimizes the cost function:
Tries multiple candidate split positions and picks the one that minimizes cost.
Pros: Often results in highly efficient trees for ray tracing.
Cons: Expensive to compute, especially for large datasets.

Minimizing Overlap
Aims to reduce the amount of overlap between child nodes.
Overlap leads to unnecessary traversal in queries, reducing efficiency.
Often combined with SAH or heuristics based on object bounding boxes.

K-Means or K-D Tree Partitioning
Uses clustering techniques to group objects based on their spatial properties.
Sometimes used for highly irregular object distributions.
*/

#ifndef PARTITIONINGSTRATEGIES_H
#define PARTITIONINGSTRATEGIES_H

#include "Physics/include/collisions/BoundingVolumeHierarchies/TopDown/PartitioningAxisChoice.h"

class SpatialMedian{
  public:

   AxisSelector axisSelector = RoundRobin();



   void partion(){

   }





};


class ObjectMedian{
  public:
};




#endif //PARTITIONINGSTRATEGIES_H
