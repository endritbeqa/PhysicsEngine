//
// Created by endrit on 11.11.24.
//

#ifndef PHYSICSENGINE_OBJECT3_H
#define PHYSICSENGINE_OBJECT3_H

#include "../math/Vector3.h"

class Object3 {
public:
    Object3();
    virtual ~Object3() = default;

    Vector3 getPosition() const;
    void setPosition(const Vector3& pos);

    Vector3 getVelocity() const;
    void setVelocity(const Vector3& vel);

    float getMass() const;
    void setMass(float mass);
    float getInverseMass() const;  // Useful for zero-mass objects (immovable)

    // Force management
    void applyForce(const Vector3& force); // Applies a force to the object for this frame
    void resetForces();                    // Resets the accumulated force

    // Update position and velocity based on accumulated forces (to be called per frame)
    virtual void integrate(float deltaTime);

protected:
    Vector3 position;   // Object's position in the world
    Vector3 velocity;   // Object's current velocity
    float mass;         // Object's mass
    float inverseMass;  // Cache inverse mass to avoid recalculating (1/mass if mass > 0, else 0)
    Vector3 forceAccum; // Accumulated force applied to the object this frame
};



#endif //PHYSICSENGINE_OBJECT3_H
