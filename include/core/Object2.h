#ifndef PHYSICSENGINE_OBJECT2_H
#define PHYSICSENGINE_OBJECT2_H

#include "../math/Vector2.h"

class Object2 {
public:
    Object2();
    virtual ~Object2() = default;

    Vector2 getPosition() const;
    void setPosition(const Vector2& pos);

    Vector2 getVelocity() const;
    void setVelocity(const Vector2& vel);

    float getMass() const;
    void setMass(float mass);
    float getInverseMass() const;  // Useful for zero-mass objects (immovable)

    // Force management
    void applyForce(const Vector2& force); // Applies a force to the object for this frame
    void resetForces();                    // Resets the accumulated force

    // Update position and velocity based on accumulated forces (to be called per frame)
    virtual void integrate(float deltaTime);

protected:
    Vector2 position;   // Object's position in the world
    Vector2 velocity;   // Object's current velocity
    float mass;         // Object's mass
    float inverseMass;  // Cache inverse mass to avoid recalculating (1/mass if mass > 0, else 0)
    Vector2 forceAccum; // Accumulated force applied to the object this frame
};



#endif //PHYSICSENGINE_OBJECT2_H
