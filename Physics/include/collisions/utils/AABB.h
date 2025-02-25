#ifndef PHYSICSENGINE_AABB_H
#define PHYSICSENGINE_AABB_H

#include "math/include/Vector3.h"


class AABB {
public:
    Vector3 center;
    double halfSize;

    AABB():center(Vector3()), halfSize(0.5){};
    AABB(Vector3 center, double halfSize) : center(center), halfSize(halfSize) {}

    bool contains(const Vector3 &p) {
        return (p.x >= center.x - halfSize && p.x <= center.x + halfSize &&
                p.y >= center.y - halfSize && p.y <= center.y + halfSize &&
                p.z >= center.z - halfSize && p.z <= center.z + halfSize);
    }

    bool intersects(const AABB &other) {
        return !(center.x + halfSize < other.center.x - other.halfSize ||
                 center.x - halfSize > other.center.x + other.halfSize ||
                 center.y + halfSize < other.center.y - other.halfSize ||
                 center.y - halfSize > other.center.y + other.halfSize ||
                 center.z + halfSize < other.center.z - other.halfSize ||
                 center.z - halfSize > other.center.z + other.halfSize);
    }


};


#endif //PHYSICSENGINE_AABB_H
