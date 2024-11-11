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
    float w, x, y, z;

    Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}

    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

    float getW() const { return w; }

    float getX() const { return x; }

    float getY() const { return y; }

    float getZ() const { return z; }


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

    Quaternion operator*(const float &scalar) {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    float magnitude() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    void normalize() {
        float norm = magnitude();
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
        float norm = magnitude();
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
        float norm = magnitude();
        return conjugate() * (1.0f / (norm * norm));
    }

    Quaternion rotate(Vector3 &v) {
        Quaternion vec(0, v.x, v.y, v.z);
        Quaternion result = (*this) * vec * inverse();
        return result;
    }

    static Quaternion fromAxisAngle(float angle, Vector3 &v) {
        float halfAngle = angle / 2.0f;
        float sinHalfAngle = std::sin(halfAngle);
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
