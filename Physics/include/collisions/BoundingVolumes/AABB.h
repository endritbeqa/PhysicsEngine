#ifndef PHYSICSENGINE_AABB_H
#define PHYSICSENGINE_AABB_H

#include "math/include/Vector3.h"
#include "math/include/Matrix3.h"
#include "Rendering/include/Geometries.h"


class AABB {
public:
    Vector3 center;
    Vector3 halfSizes;

    AABB();
    AABB(Vector3 center, Vector3 halfSizes);

    bool intersects(const AABB &other);

    void buildAABB(Mesh &mesh);

    std::array<Vector3,2> getExtremePoints(Vector3 &direction, Mesh &mesh);

    void updateAABB(Matrix3 rotation, Vector3 translation);


};


#endif //PHYSICSENGINE_AABB_H
