#include "Physics/include/collisions/BoundingVolumes/Sphere.h"
#include "math/include/Vector3.h"
#include "math/include/utils.h"

#include <random>

Sphere::Sphere() : center(Vector3()), radius(0.5) {}

Sphere::Sphere(Vector3 center, double radius) : center(center), radius(radius) {}

bool Sphere::intersects(Sphere &other) {
    Vector3 d = Vector3(center.x - other.center.x, center.y - other.center.y, center.z - other.center.z);
    double dist2 = d.normSquared();
    double sum_radius2 = radius * radius + other.radius * other.radius;
    return dist2 <= sum_radius2;
}

void Sphere::updateSphere(Vector3 *p) {

    Vector3 centerToP = Vector3(center - *p);
    double distToCenter = centerToP.norm();

    if (distToCenter > radius) {
        double newRadius = (distToCenter + radius) / 2.0;
        double k = (newRadius - radius) / distToCenter;
        radius = newRadius;
        center = center * k;
    }

}

template<std::size_t n>
void Sphere::RitterIterative(std::array<Vector3, n> &points) {
    const int NUM_ITER = 8;
    RitterSphere(points);
    std::random_device rd;  // Seed for randomness
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine
    Sphere s2 = Sphere();
    for (int k = 0; k < NUM_ITER; k++) {
        s2.radius = s2.radius * 0.95f;
        for (int i = 0; i < n; i++) {
            std::uniform_int_distribution<std::size_t> dist(i, n - 1);
            std::size_t index1 = dist(gen);
            std::size_t index2 = dist(gen);
            while (index1 == index2) {
                index2 = dist(gen);
            }
            std::swap(points[index1], points[index2]);
            SphereOfSphereAndPt(s2, points[i]);
        }
        if (s2.radius < radius) *this = s2;
    }
}

template<std::size_t n>
void Sphere::RitterSphere(std::array<Vector3, n> &points) {

    sphereFromExtremePoints(points);

    for (Vector3 *p: points) {
        updateSphere(p);
    }
}

template<std::size_t n>
void Sphere::sphereFromExtremePoints(std::array<Vector3, n> &points) {
    Vector3 *min;
    Vector3 *max;

    std::array<Vector3 *, 2> extremePoints = getMostSeperatedPoints(points);
    min = extremePoints[0];
    max = extremePoints[1];

    center = (*min + *max) / 2.0;
    radius = Vector3(center - *max).norm();
}

template<std::size_t n>
std::array<Vector3 *, 2> Sphere::getMostSeperatedPoints(std::array<Vector3, n> &points) {
    std::array<Vector3 *, 6> extremePoints{&points[0], &points[0], &points[0], &points[0], &points[0], &points[0]};

    for (Vector3 &p: points) {
        if (p.x < extremePoints[0]->x) extremePoints[0] = &p;
        if (p.x > extremePoints[1]->x) extremePoints[1] = &p;
        if (p.y < extremePoints[2]->y) extremePoints[2] = &p;
        if (p.y > extremePoints[3]->y) extremePoints[3] = &p;
        if (p.z < extremePoints[4]->z) extremePoints[4] = &p;
        if (p.z > extremePoints[5]->z) extremePoints[5] = &p;
    }

    Vector3 dist2X = *extremePoints[0] - (*extremePoints[1]);
    double distX = Vector3(&dist2X).normSquared();
    Vector3 dist2Y = *extremePoints[2] - (*extremePoints[3]);
    double distY = Vector3(&dist2Y).normSquared();
    Vector3 dist2Z = *extremePoints[4] - (*extremePoints[5]);
    double distZ = Vector3(&dist2Z).normSquared();

    Vector3 *min = extremePoints[0];
    Vector3 *max = extremePoints[1];

    if (distY > distX && distY > distZ) {
        min = extremePoints[2];
        max = extremePoints[3];
    }

    if (distZ > distX && distZ > distY) {
        min = extremePoints[4];
        max = extremePoints[5];
    }

    return std::array<Vector3 *, 2>{min, max};
}
