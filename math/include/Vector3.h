#ifndef PHYSICSENGINE_VECTOR3_H
#define PHYSICSENGINE_VECTOR3_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <array>


class Vector3 {
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

    Vector3(std::array<float,3> &a) : x(a[0]), y(a[1]), z(a[2]) {};

    Vector3(Vector3 &v) : x(v.x), y(v.y), z(v.z) {};

    Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {};

    Vector3 operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float operator[](int i) const {
        switch (i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::invalid_argument("Index out of bounds");
        }
    }


    float dot(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float normSquared() const {
        return x * x + y * y * z * z;
    }

    void normalize() {
        float len = norm();
        if (len > 0.0f) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    Vector3 normalized() const {
        float len = norm();
        if (len > 0.0f) {
            return Vector3(x / len, y / len, z / len);
        }
    }

    Vector3 cross(const Vector3 &other) const {
        return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        );
    }


    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }


};

#endif //PHYSICSENGINE_VECTOR3_H
