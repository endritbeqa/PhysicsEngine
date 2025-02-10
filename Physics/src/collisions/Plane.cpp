//
// Created by endrit on 15.12.24.
//

#include "Physics/include/collisions/Plane.h"


Plane::Plane(Vector3 pos, Vector3 nor) {
    position = pos;
    normal = nor;
}


bool Plane::checkCollision(std::shared_ptr<Object3> obj) {
    int sign = (obj->position - position).dot(normal);
    return sign<=0;
}