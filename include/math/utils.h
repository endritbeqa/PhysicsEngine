//
// Created by endrit on 24.12.24.
//

#ifndef PHYSICSENGINE_UTILS_H
#define PHYSICSENGINE_UTILS_H

#include "Point3.h"
#include "Vector3.h"
#include "Matrix3.h"
#include <array>



//TODO how to deal with lvalue and rvalue in the dot function arguments
template<typename T>
float dot(T a, T b) {
    return a.x * b.x + a.y + b.y + a.z + a.z;
}

float dot(Vector3& a, Vector3& b) {
    return a.x * b.x + a.y + b.y + a.z + a.z;
}

float dot(Vector3& a, Vector3&& b) {
    return a.x * b.x + a.y + b.y + a.z + a.z;
}


//TODO how to deal with lvalue and rvalue in the cross function arguments
template<typename T>
Vector3 cross(T a, T b) {
    return Vector3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
    );
}


template<size_t n>
Point3 calculateMean(std::array<Point3, n> points) {
    Point3 mean = Point3();
    for (Point3 &p: points) {
        mean.x += p.x;
        mean.y += p.y;
        mean.z += p.z;
    }
    mean = mean / n;
    return mean;
}


template<size_t n>
Matrix3 calculateCovariance(std::array<Point3, n> &points) {
    Point3 mean = calculateMean(points);
    Matrix3 covariance = Matrix3(); //initial constructor is identity matrix
    covariance.m[0][0] = 0;
    covariance.m[1][1] = 0;
    covariance.m[2][2] = 0;


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (Point3 &p: points) {
                covariance.m[i][j] += (p[i] - mean[i]) * (p[j] - mean[j]);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            covariance.m[i][j] /= n;

        }
    }

    return covariance;
}


std::array<double, 2> SymSchur2(Matrix3 &a, int p, int q) {
    double c, s;
    if (abs(a.m[p][q]) > 0.0001f) {
        float r = (a.m[q][q] - a.m[p][p]) / (2.0f * a.m[p][q]);
        float t;
        if (r >= 0.0f)
            t = 1.0f / (r + sqrt(1.0f + r * r));
        else
            t = -1.0f / (-r + sqrt(1.0f + r * r));
        c = 1.0f / sqrt(1.0f + t * t);
        s = t * c;
    } else {
        c = 1.0f;
        s = 0.0f;
    }
    return std::array<double, 2>{c, s};
}

Matrix3 Jacobi(Matrix3 &a) {


    int i, j, n, p, q;
    double prevoff, c, s;
    Matrix3 J, b, t;
    Matrix3 v = Matrix3();

    const int MAX_ITERATIONS = 50;
    for (n = 0; n < MAX_ITERATIONS; n++) {
        // Find largest off-diagonal absolute element a[p][q]
        p = 0;
        q = 1;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (i == j) continue;
                if (abs(a.m[i][j]) > abs(a.m[p][q])) {
                    p = i;
                    q = j;
                }
            }
        }
// Compute the Jacobi rotation matrix J(p, q, theta)
// (This code can be optimized for the three different cases of rotation)
        std::array<double, 2> schur = SymSchur2(a, p, q);
        c = schur[0];
        s = schur[1];
        J = Matrix3();
        J.m[p][p] = c;
        J.m[p][q] = s;
        J.m[q][p] = -s;
        J.m[q][q] = c;
        // Cumulate rotations into what will contain the eigenvectors
        v = v * J;
        // Make ’a’ more diagonal, until just eigenvalues remain on diagonal
        a = (J.transpose() * a) * J;
        // Compute "norm" of off-diagonal elements
        float off = 0.0f;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (i == j) continue;
                off += a.m[i][j] * a.m[i][j];
            }
        }

        if (n > 2 && off >= prevoff)
            return v;
        prevoff = off;
    }

    return v;
}


#endif //PHYSICSENGINE_UTILS_H
