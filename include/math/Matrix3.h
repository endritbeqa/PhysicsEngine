#ifndef PHYSICSENGINE_MATRIX3_H
#define PHYSICSENGINE_MATRIX3_H


#include "Vector3.h"
#include <iostream>
#include <cmath>

class Matrix3 {
public:
    float m[3][3]; // 3x3 matrix stored in a 2D array

    // Default constructor: Identity matrix
    Matrix3() {
        // Initialize as identity matrix
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
    }

    // Constructor to initialize matrix with specific values
    Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    Matrix3(Vector3& v1, Vector3& v2, Vector3& v3){
        m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z;
        m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z;
        m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z;
    }



    // Access element at (row, col)
    float& operator()(int row, int col) {
        return m[row][col];
    }

    // Access element at (row, col) (const version)
    const float& operator()(int row, int col) const {
        return m[row][col];
    }

    // Matrix multiplication
    Matrix3 operator*(const Matrix3& other) const {
        Matrix3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    // Matrix-vector multiplication (3D vector)
    Vector3 operator*(const Vector3& vec) const {
        Vector3 result;
        result.x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z;
        result.y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z;
        result.z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z;
        return result;
    }

    // Transpose of the matrix
    Matrix3 transpose() const {
        return Matrix3(
                m[0][0], m[1][0], m[2][0],
                m[0][1], m[1][1], m[2][1],
                m[0][2], m[1][2], m[2][2]
        );
    }

    // Determinant of the matrix
    float determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    // Inverse of the matrix (only if determinant is non-zero)
    Matrix3 inverse() const {
        float det = determinant();
        if (det == 0.0f) {
            // Matrix is singular (cannot invert)
            std::cerr << "Matrix is singular, cannot invert!" << std::endl;
            return Matrix3();  // Return identity matrix as a fallback
        }

        float invDet = 1.0f / det;

        Matrix3 result(
                (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet,
                (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet,
                (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet,

                (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet,
                (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet,
                (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet,

                (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet,
                (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet,
                (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet
        );
        return result;
    }

    // Print the matrix to the console
    void print() const {
        std::cout << "[ " << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << " ]\n";
        std::cout << "[ " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << " ]\n";
        std::cout << "[ " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << " ]\n";
    }

    // Static method to create rotation matrix around Z-axis
    static Matrix3 rotationZ(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);
        return Matrix3(
                cosA, -sinA, 0.0f,
                sinA, cosA, 0.0f,
                0.0f, 0.0f, 1.0f
        );
    }

    // Static method to create rotation matrix around X-axis
    static Matrix3 rotationX(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);
        return Matrix3(
                1.0f, 0.0f, 0.0f,
                0.0f, cosA, -sinA,
                0.0f, sinA, cosA
        );
    }

    // Static method to create rotation matrix around Y-axis
    static Matrix3 rotationY(float angle) {
        float cosA = cos(angle);
        float sinA = sin(angle);
        return Matrix3(
                cosA, 0.0f, sinA,
                0.0f, 1.0f, 0.0f,
                -sinA, 0.0f, cosA
        );
    }
};



#endif //PHYSICSENGINE_MATRIX3_H