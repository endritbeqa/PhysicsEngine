#ifndef PHYSICSENGINE_PARTICLE_H
#define PHYSICSENGINE_PARTICLE_H

#include <memory>
#include "Object3.h"

class Particle: public Object3{

public:
    Particle();
    Particle(Vector3 pos, Vector3 vel, double m);

    struct Derivative{
    public:
        Vector3 velocity;
        Vector3 accelaration;

        Derivative operator+(const Derivative& d){
            return Derivative(
                    this->velocity + d.velocity,
                    this->accelaration + d.accelaration
            );
        }

        Derivative operator*(double d){
            return Derivative(
                    this->velocity * d,
                    this->accelaration * d
            );
        }

    };

    Particle::Derivative calculateDerivative();
    Particle::Derivative calculateDerivative(Particle p);
    void updateState(Derivative d);
    Particle calculateState(Derivative d);

};


#endif //PHYSICSENGINE_PARTICLE_H

