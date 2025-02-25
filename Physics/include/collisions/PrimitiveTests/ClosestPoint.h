//
// Created by endrit on 31.12.24.
//

#ifndef PHYSICSENGINE_CLOSESTPOINT_H
#define PHYSICSENGINE_CLOSESTPOINT_H

#include "math/include/Vector3.h"
#include "math/include/Plane3.h"
#include "math/include/Vector3.h"
#include "math/include/Matrix3.h"
#include "math/include/utils.h"
#include "Physics/include/collisions/BoundingVolumes/AABB.h"
#include "Physics/include/collisions/BoundingVolumes/OBB.h"
#include <algorithm>


Vector3 ClosestPtPointToPlane(Vector3 &q, Plane3 &p) {
    float t = dot(p.normal, Vector3(q)) - p.distance;
    return q - Vector3(p.normal * t);
}

float DistancePointToPlane(Vector3 &q, Plane3 &p) {
    return dot(p.normal, Vector3(q)) - p.distance;
}


Vector3 ClosestPtPointToSegment(Vector3 &a, Vector3 &b, Vector3 &c) {
    Vector3 ab = Vector3(b - a);

    float t = dot(ab, Vector3(c)) / ab.normSquared();
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return a + Vector3(ab * t);
}

float DistancePointToSegment(Vector3 &a, Vector3 &b, Vector3 &c) {

    Vector3 ab = b - a, ac = c - a, bc = c - b;

    float CProjAB = dot(ac, ab) / ab.norm();
    if (CProjAB < 0.0f) return ac.norm();
    float ABLength = ab.norm();
    if (CProjAB >= ABLength) return bc.norm();

    return sqrt(dot(ac, ac) - CProjAB * CProjAB);
}

Vector3 ClosestPtPointToAABB(Vector3 p, AABB aabb) {
    double x = std::clamp(p.x, aabb.center.x - aabb.halfSizeX, aabb.center.x + aabb.halfSizeX);
    double y = std::clamp(p.y, aabb.center.y - aabb.halfSizeY, aabb.center.y + aabb.halfSizeY);
    double z = std::clamp(p.z, aabb.center.z - aabb.halfSizeZ, aabb.center.z + aabb.halfSizeZ);

    return Vector3(x, y, z);
}


//TODO test this
float DistPointAABB(Vector3 p, AABB b) {
    float distance = 0.0f;

    float distX = std::abs(b.center.x - p.x) - b.halfSizeX;
    float distY = std::abs(b.center.y - p.y) - b.halfSizeY;
    float distZ = std::abs(b.center.z - p.z) - b.halfSizeZ;

    return std::sqrt(distX * distX + distY * distY + distZ * distZ);
}


Vector3 ClosestPtPointToOBB(Vector3 p, OBB obb) {

    Vector3 p_ObbCenter = Vector3(p - obb.center);
    Vector3 closestPoint = obb.center;
    double x = dot(p_ObbCenter, Vector3(obb.localCoord.m[0]));
    double y = dot(p_ObbCenter, Vector3(obb.localCoord.m[1]));
    double z = dot(p_ObbCenter, Vector3(obb.localCoord.m[2]));

    x = std::clamp(x, obb.center[0] - obb.halfSizes[0], obb.center[0] + obb.halfSizes[0]);
    y = std::clamp(y, obb.center[1] - obb.halfSizes[1], obb.center[1] + obb.halfSizes[1]);
    z = std::clamp(z, obb.center[2] - obb.halfSizes[2], obb.center[2] + obb.halfSizes[2]);

    closestPoint = closestPoint + Vector3(obb.localCoord.m[0]) * x;
    closestPoint = closestPoint + Vector3(obb.localCoord.m[1]) * y;
    closestPoint = closestPoint + Vector3(obb.localCoord.m[2]) * z;

    return closestPoint;
}

float DistPointToOBB(Vector3 p, OBB obb) {

    Vector3 p_ObbCenter = Vector3(p - obb.center);
    float distance = 0.0f;

    for (int i = 0; i < 3; i++) {
        float d = dot(p_ObbCenter, Vector3(obb.localCoord.m[i]));
        float excess = 0.0f;
        if (d < -obb.halfSizes[i])
            excess = d + obb.halfSizes[i];
        else if (d > obb.halfSizes[i])
            excess = d - obb.halfSizes[i];
        distance += excess;
    }
    return distance;
}


Vector3 ClosestPtPointTriangle(Vector3 &p, Vector3 &a, Vector3 &b, Vector3 &c) {

    Vector3 ab = Vector3(b - a);
    Vector3 ac = Vector3(c - a);
    Vector3 bc = Vector3(c - b);

    float snom = dot(Vector3(p - a), ab), sdenom = dot(p - b, a - b);

    float tnom = dot(Vector3(p - a), ac), tdenom = dot(p - c, a - c);
    if (snom <= 0.0f && tnom <= 0.0f) return a;

    float unom = dot(Vector3(p - b), bc), udenom = dot(p - c, b - c);
    if (sdenom <= 0.0f && unom <= 0.0f) return b;
    if (tdenom <= 0.0f && udenom <= 0.0f) return c;

    Vector3 n = cross(b - a, c - a);
    float vc = dot(n, cross(a - p, b - p));

    if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
        return a + ab * (snom / (snom + sdenom));
    float va = dot(n, cross(b - p, c - p));
    if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
        return b + bc * (unom / (unom + udenom));
    float vb = dot(n, cross(c - p, a - p));

    if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
        return a + ac * (tnom / (tnom + tdenom));
    float u = va / (va + vb + vc);
    float v = vb / (va + vb + vc);
    float w = 1.0f - u - v; // = vc / (va + vb + vc)
    return a * u + b * v + c * w;
}


#endif //PHYSICSENGINE_CLOSESTPOINT_H
