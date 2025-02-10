#include "Physics/include/core/objects/3D/Object3.h"

Object3::Object3(Vector3 pos, Vector3 vel, double m) {
    velocity = vel;
    position = pos;
    mass = m;
}

Object3::Object3() {
    velocity = Vector3();
    position = Vector3();
    mass = 1;
}

void Object3::resetForces() {
    forceAccum = Vector3();
}