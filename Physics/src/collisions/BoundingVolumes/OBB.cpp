#include "Physics/include/collisions/BoundingVolumes/OBB.h"

OBB::OBB(Vector3 center, Matrix3 &localCoord, Vector3 halfSizes) : center(center), localCoord(localCoord),
                                                                  halfSizes(halfSizes) {}

bool OBB::intersects(OBB &other) {
    double rA, rB;
    Matrix3 R, AbsR;
    double epsilon = 1e-8;

    R = localCoord * other.localCoord.transpose();
    Vector3 t = Vector3(other.center - center);
    t = localCoord * t;
    AbsR = AbsR + epsilon;

    // Test axes L = A0, L = A1, L = A2
    for (int i = 0; i < 3; i++) {
        rA = halfSizes[i];
        rB = other.halfSizes[0] * AbsR.m[i][0] + other.halfSizes[1] * AbsR.m[i][1] + other.halfSizes[2] * AbsR.m[i][2];
        if (abs(t[i]) > rA + rB) return false;;
    }

    // Test axes L = B0, L = B1, L = B2
    for (int i = 0; i < 3; i++) {
        rA = halfSizes[0] * AbsR.m[0][i] + halfSizes[1] * AbsR.m[1][i] + halfSizes[2] * AbsR.m[2][i];
        rB = other.halfSizes[i];
        if (abs(t[0] * R.m[0][i] + t[1] * R.m[1][i] + t[2] * R.m[2][i]) > rA + rB) return false;;
    }

    // Test axis L = A0 x B0
    rA = halfSizes[1] * AbsR.m[2][0] + halfSizes[2] * AbsR.m[1][0];
    rB = other.halfSizes[1] * AbsR.m[0][2] + other.halfSizes[2] * AbsR.m[0][1];
    if (abs(t[2] * R.m[1][0] - t[1] * R.m[2][0]) > rA + rB) return false;;

    // Test axis L = A0 x B1
    rA = halfSizes[1] * AbsR.m[2][1] + halfSizes[2] * AbsR.m[1][1];
    rB = other.halfSizes[0] * AbsR.m[0][2] + other.halfSizes[2] * AbsR.m[0][0];
    if (abs(t[2] * R.m[1][1] - t[1] * R.m[2][1]) > rA + rB) return false;;

    // Test axis L = A0 x B2
    rA = halfSizes[1] * AbsR.m[2][2] + halfSizes[2] * AbsR.m[1][2];
    rB = other.halfSizes[0] * AbsR.m[0][1] + other.halfSizes[1] * AbsR.m[0][0];
    if (abs(t[2] * R.m[1][2] - t[1] * R.m[2][2]) > rA + rB) return false;;

    // Test axis L = A1 x B0
    rA = halfSizes[0] * AbsR.m[2][0] + halfSizes[2] * AbsR.m[0][0];
    rB = other.halfSizes[1] * AbsR.m[1][2] + other.halfSizes[2] * AbsR.m[1][1];
    if (abs(t[0] * R.m[2][0] - t[2] * R.m[0][0]) > rA + rB) return false;;

    // Test axis L = A1 x B1
    rA = halfSizes[0] * AbsR.m[2][1] + halfSizes[2] * AbsR.m[0][1];
    rB = other.halfSizes[0] * AbsR.m[1][2] + other.halfSizes[2] * AbsR.m[1][0];
    if (abs(t[0] * R.m[2][1] - t[2] * R.m[0][1]) > rA + rB) return false;;

    // Test axis L = A1 x B2
    rA = halfSizes[0] * AbsR.m[2][2] + halfSizes[2] * AbsR.m[0][2];
    rB = other.halfSizes[0] * AbsR.m[1][1] + other.halfSizes[1] * AbsR.m[1][0];
    if (abs(t[0] * R.m[2][2] - t[2] * R.m[0][2]) > rA + rB) return false;;

    // Test axis L = A2 x B0
    rA = halfSizes[0] * AbsR.m[1][0] + halfSizes[1] * AbsR.m[0][0];
    rB = other.halfSizes[1] * AbsR.m[2][2] + other.halfSizes[2] * AbsR.m[2][1];
    if (abs(t[1] * R.m[0][0] - t[0] * R.m[1][0]) > rA + rB) return false;;

    // Test axis L = A2 x B1
    rA = halfSizes[0] * AbsR.m[1][1] + halfSizes[1] * AbsR.m[0][1];
    rB = other.halfSizes[0] * AbsR.m[2][2] + other.halfSizes[2] * AbsR.m[2][0];
    if (abs(t[1] * R.m[0][1] - t[0] * R.m[1][1]) > rA + rB) return false;;

    // Test axis L = A2 x B2
    rA = halfSizes[0] * AbsR.m[1][2] + halfSizes[1] * AbsR.m[0][2];
    rB = other.halfSizes[0] * AbsR.m[2][1] + other.halfSizes[1] * AbsR.m[2][0];
    if (abs(t[1] * R.m[0][2] - t[0] * R.m[1][2]) > rA + rB) return false;

    return true;

}

void OBB::calculateTightOBB(Mesh &mesh) {

}
