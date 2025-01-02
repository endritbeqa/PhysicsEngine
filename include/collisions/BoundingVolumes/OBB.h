#ifndef PHYSICSENGINE_OBB_H
#define PHYSICSENGINE_OBB_H

#include <array>
#include "include/math/Point3.h"
#include "include/math/Vector3.h"
#include "include/math/Matrix3.h"


//TODO localCoord should be guaranteed to be orthogonal unit vectors.
class OBB{
public:
    Point3 center;
    Matrix3 localCoord;
    Vector3 halfSizes;

    OBB(Point3 center, Matrix3 &localCoord, Vector3 halfSizes);

    bool intersects(OBB &other);

    //TODO implement this using convex hull covariance and using PCA Real-Time Collision Detection Book pg.108
    //or Mirtich96a algorithm
    template<size_t n>
    void calculateTightOBB(std::array<Point3*, n> &points);


};


#endif //PHYSICSENGINE_OBB_H
