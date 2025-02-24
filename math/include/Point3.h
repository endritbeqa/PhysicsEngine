#ifndef PHYSICSENGINE_POINT3_H
#define PHYSICSENGINE_POINT3_H


#include <stdexcept>
#include <array>

class Vector3;

class Point3{
public:
    float x, y, z;
    Point3(): x(0.0f), y(0.0f), z(0.0f) {}
    Point3(float x, float y, float z): x(x), y(y), z(z) {};
    Point3(std::array<float,3> &a) : x(a[0]), y(a[1]), z(a[2]) {};
    Point3(Vector3&& v);

    Point3 operator+(const Point3& other) const {
        return Point3(x + other.x, y + other.y, z + other.z);
    }

    Point3 operator-(const Point3& other) const {
        return Point3(x - other.x, y - other.y, z - other.z);
    }

    Point3 operator*(const Point3& other) const {
        return Point3(x * other.x, y * other.y, z * other.z);
    }

    Point3 operator*(float scalar) const {
        return Point3(x * scalar, y * scalar, z * scalar);
    }

    Point3 operator/(float scalar) const {
        return Point3(x / scalar, y / scalar, z / scalar);
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


};

#endif //PHYSICSENGINE_POINT3_H
