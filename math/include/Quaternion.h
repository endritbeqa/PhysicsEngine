//
// Created by endrit on 11.11.24.
//

#ifndef PHYSICSENGINE_QUATERNION_H
#define PHYSICSENGINE_QUATERNION_H

#include "Vector3.h"
#include <cmath>
#include <iostream>

class Quaternion {
public:
    double w, x, y, z;

    Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

    Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}
    Quaternion(double w, Vector3 v) : w(w), x(v.x), y(v.y), z(v.z) {}

    Quaternion operator+(const Quaternion &other) {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    Quaternion operator-(const Quaternion &other) {
        return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    Quaternion operator*(const Quaternion &other) {
        return Quaternion(w * other.w - x * other.x - y * other.y - z * other.z,
                          w + other.x + x * other.w + y * other.z - z - other.y,
                          w * other.y - x * other.z + y * other.w + z * other.x,
                          w * other.z + x * other.y - y * other.x + z * other.w);
    }

    Quaternion operator*(const double &scalar) {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    double magnitude() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    void normalize() {
        double norm = magnitude();
        if (norm == 0) {
            std::cerr << "Quaternion has magnitude 0!" << std::endl;
        } else {
            w /= norm;
            x /= norm;
            y /= norm;
            z /= norm;
        }
    }

    Quaternion normalized() {
        double norm = magnitude();
        if (norm == 0) {
            std::cerr << "Quaternion has magnitude 0!" << std::endl;
            return (*this);
        } else {
            return Quaternion(
                    w / norm,
                    x / norm,
                    y / norm,
                    z / norm);
        }
    }

    Quaternion inverse() const {
        double norm = magnitude();
        return conjugate() * (1.0f / (norm * norm));
    }

    Quaternion rotate(Vector3 &v) {
        Quaternion vec(0, v.x, v.y, v.z);
        Quaternion result = (*this) * vec * inverse();
        return result;
    }

    static Quaternion fromAxisAngle(double angle, Vector3 &v) {
        double halfAngle = angle / 2.0f;
        double sinHalfAngle = std::sin(halfAngle);
        return Quaternion(std::cos(halfAngle),
                          v.x * sinHalfAngle,
                          v.y * sinHalfAngle,
                          v.z * sinHalfAngle).normalized();
    }


    Matrix3 toMatrix(){
        return Matrix3(1-2*y*y-2*z*z,2*x*y-2*w*z, 2*x*z+2*w*y,
                       2*x*y+2*w*z, 1-2*x*x-2*z*z, 2*y*z-2*w*x,
                       2*x*z-2*w*y, 2*y*z+2*w*x, 1-2*x*x-2*y*y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &v) {
        os << "(" << v.w << ", " << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

};


//TODO fix this so it doesn't cause double declaration
/*
Quaternion rotationMatrixToQuaternion(const Matrix3& R) {
    //TODO A bit hacky but works since I can't overload the [] operator twice in C++20 (is possible in C++23)
    std::array<std::array<double,3>,3> data = R.m;
    Quaternion q;
    double trace = data[0][0] + data[1][1] + data[2][2]; // Trace of the matrix

    if (trace > 0.0) {
        double S = sqrt(trace + 1.0) * 2.0; // S = 4 * q.w
        q.w = 0.25 * S;
        q.x = (data[2][1] - data[1][2]) / S;
        q.y = (data[0][2] - data[2][0]) / S;
        q.z = (data[1][0] - data[0][1]) / S;
    } else if ((data[0][0] > data[1][1]) && (data[0][0] > data[2][2])) {
        double S = sqrt(1.0 + data[0][0] - data[1][1] - data[2][2]) * 2.0;
        q.w = (data[2][1] - data[1][2]) / S;
        q.x = 0.25 * S;
        q.y = (data[0][1] + data[1][0]) / S;
        q.z = (data[0][2] + data[2][0]) / S;
    } else if (data[1][1] > data[2][2]) {
        double S = sqrt(1.0 + data[1][1] - data[0][0] - data[2][2]) * 2.0;
        q.w = (data[0][2] - data[2][0]) / S;
        q.x = (data[0][1] + data[1][0]) / S;
        q.y = 0.25 * S;
        q.z = (data[1][2] + data[2][1]) / S;
    } else {
        double S = sqrt(1.0 + data[2][2] - data[0][0] - data[1][1]) * 2.0;
        q.w = (data[1][0] - data[0][1]) / S;
        q.x = (data[0][2] + data[2][0]) / S;
        q.y = (data[1][2] + data[2][1]) / S;
        q.z = 0.25 * S;
    }

    return q;
}
*/

#endif //PHYSICSENGINE_QUATERNION_H
