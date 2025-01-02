#ifndef PHYSICSENGINE_PLANE3_H
#define PHYSICSENGINE_PLANE3_H

#include "Vector3.h"
#include "include/core/objects/3D/Object3.h"
#include <memory>

//Plane has 4 component representation and has a unit length normal vector

class Plane3{
public:
    Plane3();
    Plane3(Vector3 nor, float d):normal(nor.normalized()), distance(d){}

    Vector3 normal;
    float distance;


};

#endif //PHYSICSENGINE_PLANE3_H