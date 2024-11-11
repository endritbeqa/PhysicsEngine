//
// Created by endrit on 11.11.24.
//

#ifndef PHYSICSENGINE_VECTOR3_H
#define PHYSICSENGINE_VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3{
public:
    float x, y, z;
    Vector3(): x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float lengthSquared() const {
        return x * x + y * y * z * z;
    }

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    Vector3 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return Vector3(x / len, y / len, z / len);
        }
        return *this;
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        );
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

};

#endif //PHYSICSENGINE_VECTOR3_H
