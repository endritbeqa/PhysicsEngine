#include "include/forces/GravityForce.h"

GravityForce::GravityForce() {
    type = Unary;
    direction = Vector3(0.0, 9.81, 0.0);
}

GravityForce::GravityForce(Vector3 v) {
    type = Unary;
    direction = v;
}

void GravityForce::apply() {
    for (std::shared_ptr<Object3> obj: objects){
        obj->forceAccum = obj->forceAccum + direction* obj->mass;
    }
}

