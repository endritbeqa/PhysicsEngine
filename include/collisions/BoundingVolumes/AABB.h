#ifndef PHYSICSENGINE_AABB_H
#define PHYSICSENGINE_AABB_H

#include "include/math/Point3.h"
#include "include/math/Vector3.h"
#include "include/math/Matrix3.h"
#include <array>


class AABB {
public:
    Point3 center;
    double halfSizeX;
    double halfSizeY;
    double halfSizeZ;

    AABB();
    AABB(Point3 center, double halfSizeX, double halfSizeY, double halfSizeZ);

    bool intersects(const AABB &other);

    template<std::size_t n>
    std::array<Point3*,2> getExtremePoints(Vector3& direction, std::array<Point3, n>& points);

    void updateAABB(Matrix3 rotation, Vector3 translation);


};


#endif //PHYSICSENGINE_AABB_H
