#ifndef PHYSICSENGINE_POINT3_H
#define PHYSICSENGINE_POINT3_H


class Point3{
public:
    double x, y, z;
    Point3(): x(0.0f), y(0.0f), z(0.0f) {}
    Point3(double x, double y, double z): x(x), y(y), z(z) {}

    Point3 operator+(const Point3& other) const {
        return Point3(x + other.x, y + other.y, z + other.z);
    }

    Point3 operator-(const Point3& other) const {
        return Point3(x - other.x, y - other.y, z - other.z);
    }

    Point3 operator*(const Point3& other) const {
        return Point3(x * other.x, y * other.y, z * other.z);
    }

    Point3 operator*(double scalar) const {
        return Point3(x * scalar, y * scalar, z * scalar);
    }

    Point3 operator/(double scalar) const {
        return Point3(x / scalar, y / scalar, z / scalar);
    }
    
    
};

#endif //PHYSICSENGINE_POINT3_H
