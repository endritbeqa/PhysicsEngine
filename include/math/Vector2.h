#ifndef PHYSICSENGINE_VECTOR2_H
#define PHYSICSENGINE_VECTOR2_H

#include <cmath>
#include <iostream>

class Vector2 {
public:
    double x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void set(double x, double y) { this->x = x; this->y = y; }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(double scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    double dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // Squared length (no square root for optimization)
    double lengthSquared() const {
        return x * x + y * y;
    }

    // Normalize the vector (make it unit length)
    void normalize() {
        double len = length();
        if (len > 0.0f) {
            x /= len;
            y /= len;
        }
    }

    // Return a normalized copy of the vector
    Vector2 normalized() const {
        double len = length();
        if (len > 0.0f) {
            return Vector2(x / len, y / len);
        }
        return *this;
    }

    Vector2 perp() const {
        return Vector2(-y, x);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};



#endif //PHYSICSENGINE_VECTOR2_H
