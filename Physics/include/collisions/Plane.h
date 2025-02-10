//
// Created by endrit on 14.12.24.
//

#ifndef PHYSICSENGINE_PLANE_H
#define PHYSICSENGINE_PLANE_H


#include <memory>
#include "math/include/Vector3.h"
#include "Physics/include/core/objects/3D/Object3.h"

class Plane{
public:
    Plane();
    Plane(Vector3 nor, Vector3 pos);

    Vector3 normal;
    Vector3 position;

    bool checkCollision(std::shared_ptr<Object3> obj);



};




#endif //PHYSICSENGINE_PLANE_H
