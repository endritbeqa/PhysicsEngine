#include "include/collisions/BoundingVolumes/AABB.h"
#include <limits>


AABB::AABB():center(Point3()), halfSizeX(0.5), halfSizeY(0.5), halfSizeZ(0.5){};
AABB::AABB(Point3 center, double halfSizeX, double halfSizeY, double halfSizeZ) : center(center), halfSizeX(halfSizeX), halfSizeY(halfSizeY), halfSizeZ(halfSizeZ) {}

bool AABB::intersects(const AABB &other) {
    return !(center.x + halfSizeX < other.center.x - other.halfSizeX ||
             center.x - halfSizeX > other.center.x + other.halfSizeX ||
             center.y + halfSizeY < other.center.y - other.halfSizeY ||
             center.y - halfSizeY > other.center.y + other.halfSizeY ||
             center.z + halfSizeZ < other.center.z - other.halfSizeZ ||
             center.z - halfSizeZ > other.center.z + other.halfSizeZ);
}

//TODO improve performance on this one and test
void AABB::updateAABB(Matrix3 rotation, Vector3 translation) {
    center.x = center.x + translation.x;
    center.y = center.y + translation.y;
    center.z = center.z + translation.z;

    Vector3 halfSizes = Vector3(halfSizeX, halfSizeY, halfSizeZ);
    Vector3 newHalfSizes = rotation*halfSizes;
    halfSizeX = newHalfSizes.x;
    halfSizeY = newHalfSizes.y;
    halfSizeZ = newHalfSizes.z;

}

template<std::size_t n>
std::array<Point3*, 2> AABB::getExtremePoints(Vector3& direction, std::array<Point3, n>& points) {
    double minValue= std::numeric_limits<double>::max();
    double maxValue= std::numeric_limits<double>::min();
    Point3* min = &points[0];
    Point3* max = &points[0];

    for(Point3& p: points){
        double proj = direction.dot(Vector3(p));
        if(proj < minValue){
            minValue = proj;
            min = &p;
        }
        if(proj > maxValue){
            maxValue = proj;
            max = &p;
        }
    }

    return std::array<Point3*, 2>{min, max};
}




