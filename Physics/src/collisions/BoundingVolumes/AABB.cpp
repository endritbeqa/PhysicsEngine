#include "Physics/include/collisions/BoundingVolumes/AABB.h"
#include "math/include/utils.h"
#include <limits>


AABB::AABB(): center(Vector3()), halfSizes(Vector3()) {
};

AABB::AABB(Vector3 center, Vector3 halfSizes) : center(center), halfSizes(halfSizes){}

bool AABB::intersects(const AABB &other) {
    return !(center.x + halfSizes[0] < other.center.x - other.halfSizes[0] ||
             center.x - halfSizes[0] > other.center.x + other.halfSizes[0] ||
             center.y + halfSizes[1] < other.center.y - other.halfSizes[1] ||
             center.y - halfSizes[1] > other.center.y + other.halfSizes[1] ||
             center.z + halfSizes[2] < other.center.z - other.halfSizes[2] ||
             center.z - halfSizes[3] > other.center.z + other.halfSizes[2]);
}

//TODO improve performance on this one and test
void AABB::updateAABB(Matrix3 rotation, Vector3 translation) {
    center.x = center.x + translation.x;
    center.y = center.y + translation.y;
    center.z = center.z + translation.z;

    halfSizes = rotation * halfSizes;

}


void AABB::buildAABB(Mesh &mesh) {
    //extreme values in axis X,Y,Z
    std::array<Vector3, 3> axes = {Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)};
    std::array<float, 6> extremeValues = {
        std::numeric_limits<float>::min(), std::numeric_limits<float>::max(),
        std::numeric_limits<float>::min(), std::numeric_limits<float>::max(),
        std::numeric_limits<float>::min(), std::numeric_limits<float>::max()
    };

    for (Vertex &v: mesh.vertices) {
        for (unsigned int i = 0; i < 3; i++) {
            float proj = dot(axes[i], v.position);
            if (proj < extremeValues[2*i]) {
                 extremeValues[2*i] = proj;
            }
            if (proj > extremeValues[2*i+1]) {
                extremeValues[2*i+1] = proj;
            }
        }
    }

    halfSizes = Vector3((extremeValues[1]-extremeValues[0])/2.0f,
                        (extremeValues[3]-extremeValues[2])/2.0f,
                        (extremeValues[5]-extremeValues[4])/2.0f);
    center = Vector3(extremeValues[0]+halfSizes[0], extremeValues[2]+halfSizes[1], extremeValues[4]+halfSizes[2]);
}


std::array<Vector3, 2> AABB::getExtremePoints(Vector3 &direction, Mesh &mesh) {
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    Vector3 min = mesh.vertices[0].position;
    Vector3 max = mesh.vertices[0].position;

    for (Vertex &v: mesh.vertices) {
        double proj = dot(direction, v.position);
        if (proj < minValue) {
            minValue = proj;
            min = v.position;
        }
        if (proj > maxValue) {
            maxValue = proj;
            max = v.position;
        }
    }

    return std::array<Vector3, 2>{min, max};
}
