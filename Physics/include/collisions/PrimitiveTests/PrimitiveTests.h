#ifndef PHYSICSENGINE_PRIMITIVETESTS_H
#define PHYSICSENGINE_PRIMITIVETESTS_H


#include "ClosestPoint.h"
#include "math/include/Plane3.h"
#include "math/include/utils.h"
#include "Physics/include/collisions/BoundingVolumes/Sphere.h"
#include "Physics/include/collisions/BoundingVolumes/AABB.h"
#include "Physics/include/collisions/BoundingVolumes/OBB.h"


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


int TestSphereTriangle(Sphere &s, Point3 &a, Point3 &b, Point3 &c) {
    Point3 p = ClosestPtPointTriangle(s.center, a, b, c);
    Vector3 v = p - s.center;
    return dot(v, v) <= s.radius * s.radius;
}


//TODO implement this
int TestTriangleAABB(Point3 &v0, Point3 &v1, Point3 &v2, AABB &aabb) {
}


int IntersectSegmentPlane(Point3 &a, Point3 &b, Plane3 &p, Point3 &q) {
    Vector3 ab = b - a;
    float t = (p.distance - dot(p.normal, a)) / dot(p.normal, ab);
    if (t >= 0.0f && t <= 1.0f) {
        q = a + ab * t;
        return 1;
    }
    return 0;
}

int IntersectSegmentPlane(Point3 a, Point3 b, Point3 d, Point3 e, Point3 f, Point3 &q) {
    Plane3 p;
    p.normal = cross(e - d, f - d);
    p.distance = dot(p.normal, d);
    return IntersectSegmentPlane(a, b, p, q);
}

int IntersectRaySphere(Point3 p, Vector3 d, Sphere s, Point3 &q) {
    Vector3 m = p - s.center;
    float b = dot(m, d);
    float c = dot(m, m) - s.radius * s.radius;

    if (c > 0.0f && b > 0.0f) return 0;
    float discr = b * b - c;
    if (discr < 0.0f) return 0;
    float t = -b - std::sqrt(discr);
    if (t < 0.0f) t = 0.0f;
    q = p + d * t;
    return 1;
}

int TestRaySphere(Point3 p, Vector3 d, Sphere s) {
    Vector3 m = p - s.center;
    float c = dot(m, m) - s.radius * s.radius;
    if (c <= 0.0f) return 1;
    float b = dot(m, d);
    if (b > 0.0f) return 0;
    float disc = b * b - c;
    if (disc < 0.0f) return 0;
    return 1;
}


#endif //PHYSICSENGINE_PRIMITIVETESTS_H