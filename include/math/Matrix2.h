
#ifndef PHYSICSENGINE_MATRIX2_H
#define PHYSICSENGINE_MATRIX2_H


#include "Vector2.h"

class Matrix2 {
public:
    double m[2][2];  // 2x2 matrix (2 rows, 2 columns)

    // Constructors
    Matrix2() {
        m[0][0] = 1.0f; m[0][1] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f;
    }

    Matrix2(double a, double b, double c, double d) {
        m[0][0] = a; m[0][1] = b;
        m[1][0] = c; m[1][1] = d;
    }

    Matrix2(Vector2& v1, Vector2& v2){
        m[0][0] = v1.x; m[0][1] = v1.y;
        m[1][0] = v2.x; m[1][1] = v2.y;
    }

    double get(int row, int col) const {
        return m[row][col];
    }

    void set(int row, int col, double value) {
        m[row][col] = value;
    }

    // Matrix-Vector multiplication
    Vector2 operator*(const Vector2& v) const {
        return Vector2(
                m[0][0] * v.x + m[0][1] * v.y,
                m[1][0] * v.x + m[1][1] * v.y
        );
    }

    // Matrix-Matrix multiplication
    Matrix2 operator*(const Matrix2& mat) const {
        return Matrix2(
                m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0],
                m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1],

                m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0],
                m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1]
        );
    }

    // Matrix addition
    Matrix2 operator+(const Matrix2& mat) const {
        return Matrix2(
                m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1],
                m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1]
        );
    }

    // Matrix subtraction
    Matrix2 operator-(const Matrix2& mat) const {
        return Matrix2(
                m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1],
                m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1]
        );
    }

    // Scalar multiplication
    Matrix2 operator*(double scalar) const {
        return Matrix2(
                m[0][0] * scalar, m[0][1] * scalar,
                m[1][0] * scalar, m[1][1] * scalar
        );
    }

    // Determinant of the matrix
    double determinant() const {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    // Inverse of the matrix
    Matrix2 inverse() const {
        double det = determinant();
        if (det == 0) {
            std::cerr << "Matrix is singular and cannot be inverted!" << std::endl;
            return *this;  // Return the original matrix if it cannot be inverted
        }
        double invDet = 1.0f / det;
        return Matrix2(
                m[1][1] * invDet, -m[0][1] * invDet,
                -m[1][0] * invDet, m[0][0] * invDet
        );
    }

    // Transpose of the matrix
    Matrix2 transpose() const {
        return Matrix2(
                m[0][0], m[1][0],
                m[0][1], m[1][1]
        );
    }

    // Print matrix to stream (useful for debugging)
    friend std::ostream& operator<<(std::ostream& os, const Matrix2& mat) {
        os << "[" << mat.m[0][0] << ", " << mat.m[0][1] << "]\n"
           << "[" << mat.m[1][0] << ", " << mat.m[1][1] << "]";
        return os;
    }
};


#endif //PHYSICSENGINE_MATRIX2_H