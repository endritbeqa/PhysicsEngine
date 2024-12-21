#ifndef PHYSICSENGINE_OBB_H
#define PHYSICSENGINE_OBB_H

#include <array>
#include "include/math/Point3.h"
#include "include/math/Vector3.h"

class OBB{
    Point3 center;
    std::array<Vector3, 3> localCoord;
    double halfSizeX;
    double halfSizeY;
    double halfSizeZ;


};


#endif //PHYSICSENGINE_OBB_H
