#ifndef PHYSICSENGINE_PRIMITIVETESTS_H
#define PHYSICSENGINE_PRIMITIVETESTS_H


#include "ClosestPoint.h"
#include "include/math/Plane3.h"
#include "include/math/utils.h"
#include "include/collisions/BoundingVolumes/Sphere.h"
#include "include/collisions/BoundingVolumes/AABB.h"
#include "include/collisions/BoundingVolumes/OBB.h"


int TestSpherePlane(Sphere &s, Plane3 &p) {
    float dist = dot(Vector3(s.center), p.normal) - p.distance;
    return std::abs(dist) <= s.radius;
}

int InsideSpherePlane(Sphere &s, Plane3 &p) {
    float dist = dot(Vector3(s.center), p.normal) - p.distance;
    return dist < -s.radius;
}

int TestSphereHalfSpace(Sphere &s, Plane3 &p) {
    float dist = dot(Vector3(s.center), p.normal) - p.distance;
    return dist <= s.radius;
}

int TestOBBPlane(OBB &obb, Plane3 &p) {
    float r = obb.halfSizes[0] * std::abs(dot(Vector3(p.normal), Vector3(obb.localCoord.m[0]))) +
              obb.halfSizes[1] * std::abs(dot(Vector3(p.normal), Vector3(obb.localCoord.m[1]))) +
              obb.halfSizes[2] * std::abs(dot(Vector3(p.normal), Vector3(obb.localCoord.m[2])));

    float s = dot(p.normal, obb.center) - p.distance;
    return std::abs(s) <= r;
}

int TestAABBPlane(AABB &aabb, Plane3 &p) {

    float r = aabb.halfSizeX * std::abs(p.normal[0]) + aabb.halfSizeY * std::abs(p.normal[1]) +
              aabb.halfSizeZ * std::abs(p.normal[2]);
    float s = dot(p.normal, aabb.center) - p.distance;
    return std::abs(s) <= r;
}


int TestSphereAABB(Sphere &s, AABB &b) {
    float distance = DistPointAABB(s.center, b);
    return distance <= s.radius;
}


int TestSphereOBB(Sphere &s, OBB &obb) {
    Point3 p = ClosestPtPointToOBB(s.center, obb);
    Vector3 v = p - s.center;
    return dot(v, v) <= s.radius * s.radius;
}


int TestSphereTriangle(Sphere& s, Point3& a, Point3& b, Point3& c) {
    Point3 p = ClosestPtPointTriangle(s.center, a, b, c);
    Vector3 v = p - s.center;
    return dot(v, v) <= s.radius * s.radius;
}


//TODO implemet this
int TestTriangleAABB(Point3& v0, Point3& v1, Point3& v2, AABB& aabb) {
}

#endif //PHYSICSENGINE_PRIMITIVETESTS_H