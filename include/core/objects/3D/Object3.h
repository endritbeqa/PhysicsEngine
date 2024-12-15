#ifndef PHYSICSENGINE_OBJECT3_H
#define PHYSICSENGINE_OBJECT3_H

#include <array>
#include "include/math/Vector3.h"

class Object3 {
public:
    Object3(Vector3 pos, Vector3 vel, float mass);
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


    Vector3 position;
    Vector3 velocity;
    float mass;
    Vector3 forceAccum;

    void resetForces();

};

#endif //PHYSICSENGINE_OBJECT3_H
