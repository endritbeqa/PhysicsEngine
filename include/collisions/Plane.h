//
// Created by endrit on 14.12.24.
//

#ifndef PHYSICSENGINE_PLANE_H
#define PHYSICSENGINE_PLANE_H


#include <memory>
#include "include/math/Vector3.h"
#include "include/core/objects/3D/Object3.h"

class Plane{
public:
    Plane();

    Vector3 normal;
    Vector3 postion;

    bool checkCollision(std::shared_ptr<Object3> obj);



};




#endif //PHYSICSENGINE_PLANE_H
