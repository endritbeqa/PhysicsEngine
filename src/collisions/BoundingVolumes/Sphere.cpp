#include "include/collisions/BoundingVolumes/Sphere.h"
#include "include/math/Vector3.h"

Sphere::Sphere() : center(Point3()), radius(0.5) {}

Sphere::Sphere(Point3 center, double radius) : center(center), radius(radius) {}

bool Sphere::intersects(Sphere &other) {
    Vector3 d = Vector3(center.x - other.center.x, center.y - other.center.y, center.z - other.center.z);
    double dist2 = d.normSquared();
    double sum_radius2 = radius * radius + other.radius * other.radius;
    return dist2 <= sum_radius2;
}

void Sphere::updateSphere(Point3 *p) {

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
void Sphere::RitterSphere(std::array<Point3, n> &points) {

    sphereFromExtremePoints(points);

    for (Point3 *p: points) {
        updateSphere(p);
    }
}

template<std::size_t n>
void Sphere::sphereFromExtremePoints(std::array<Point3, n> &points) {
    Point3 *min;
    Point3 *max;

    std::array<Point3 *, 2> extremePoints = getMostSeperatedPoints(points);
    min = extremePoints[0];
    max = extremePoints[1];

    center = (*min + *max) / 2.0;
    radius = Vector3(center - *max).norm();
}

template<std::size_t n>
std::array<Point3 *, 2> Sphere::getMostSeperatedPoints(std::array<Point3, n> &points) {
    std::array<Point3 *, 6> extremePoints{&points[0], &points[0], &points[0], &points[0], &points[0], &points[0]};

    for (Point3 &p: points) {
        if (p.x < extremePoints[0]->x) extremePoints[0] = &p;
        if (p.x > extremePoints[1]->x) extremePoints[1] = &p;
        if (p.y < extremePoints[2]->y) extremePoints[2] = &p;
        if (p.y > extremePoints[3]->y) extremePoints[3] = &p;
        if (p.z < extremePoints[4]->z) extremePoints[4] = &p;
        if (p.z > extremePoints[5]->z) extremePoints[5] = &p;
    }

    Point3 dist2X = *extremePoints[0] - (*extremePoints[1]);
    double distX = Vector3(&dist2X).normSquared();
    Point3 dist2Y = *extremePoints[2] - (*extremePoints[3]);
    double distY = Vector3(&dist2Y).normSquared();
    Point3 dist2Z = *extremePoints[4] - (*extremePoints[5]);
    double distZ = Vector3(&dist2Z).normSquared();

    Point3 *min = extremePoints[0];
    Point3 *max = extremePoints[1];

    if (distY > distX && distY > distZ) {
        min = extremePoints[2];
        max = extremePoints[3];
    }

    if (distZ > distX && distZ > distY) {
        min = extremePoints[4];
        max = extremePoints[5];
    }

    return std::array<Point3 *, 2>{min, max};
}
