#ifndef PHYSICSENGINE_SPHERE_H
#define PHYSICSENGINE_SPHERE_H

#include <array>
#include "math/include/Vector3.h"

class Sphere{
public:
    Vector3 center;
    double radius;

    Sphere();
    Sphere(Vector3 center, double radius);

    bool intersects(Sphere &other);

    void updateSphere(Vector3* p);

    template<std::size_t n>
    std::array<Vector3*, 2> getMostSeperatedPoints(std::array<Vector3, n>& points);

    template<std::size_t n>
    void sphereFromExtremePoints(std::array<Vector3, n>& points);

    template<std::size_t n>
    void RitterSphere(std::array<Vector3, n>& points);

    template<std::size_t n>
    void RitterIterative(std::array<Vector3, n>& points);


//TODO implement this real-time collision book pg.97
    template<std::size_t n>
    void EigenSphere(std::array<Vector3, n>& points);


    //TODO implement this real-time collision book pg.100
    template<std::size_t n>
    void WeltzSphere(std::array<Vector3, n>& points);



};


#endif //PHYSICSENGINE_SPHERE_H
