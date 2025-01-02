#ifndef PHYSICSENGINE_SPHERE_H
#define PHYSICSENGINE_SPHERE_H

#include <array>
#include "include/math/Point3.h"


class Sphere{
public:
    Point3 center;
    double radius;

    Sphere();
    Sphere(Point3 center, double radius);

    bool intersects(Sphere &other);

    void updateSphere(Point3* p);

    template<std::size_t n>
    std::array<Point3*, 2> getMostSeperatedPoints(std::array<Point3, n>& points);

    template<std::size_t n>
    void sphereFromExtremePoints(std::array<Point3, n>& points);

    template<std::size_t n>
    void RitterSphere(std::array<Point3, n>& points);

    template<std::size_t n>
    void RitterIterative(std::array<Point3, n>& points);


//TODO implement this real-time collision book pg.97
    template<std::size_t n>
    void EigenSphere(std::array<Point3, n>& points);


    //TODO implement this real-time collision book pg.100
    template<std::size_t n>
    void WeltzSphere(std::array<Point3, n>& points);



};


#endif //PHYSICSENGINE_SPHERE_H
