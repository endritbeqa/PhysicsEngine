#ifndef PHYSICSENGINE_OBJECT3_H
#define PHYSICSENGINE_OBJECT3_H

#include <array>
#include "math/include/Vector3.h"

class Object3 {
public:

    Vector3 position;
    Vector3 velocity;
    double mass;
    Vector3 forceAccum;

    Object3(Vector3 pos, Vector3 vel, double mass);
    Object3();
    virtual ~Object3() = default;

    Object3(const Object3& other)
            : position(other.position), velocity(other.velocity), mass(other.mass), forceAccum(other.forceAccum) {
    }

    Object3(Object3&& other) noexcept
            : position(std::move(other.position)),
              velocity(std::move(other.velocity)),
              mass(other.mass),
              forceAccum(std::move(other.forceAccum)) {
        other.mass = 0.0f;
    }


    void resetForces();

};

#endif //PHYSICSENGINE_OBJECT3_H
