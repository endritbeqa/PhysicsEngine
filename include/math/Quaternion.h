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

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &v) {
        os << "(" << v.w << ", " << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

};


#endif //PHYSICSENGINE_QUATERNION_H
