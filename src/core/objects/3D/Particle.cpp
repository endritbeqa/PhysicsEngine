#include "include/core/objects/3D/Particle.h"

Particle::Particle() = default;

Particle::Particle(Vector3 pos, Vector3 vel, double m): Object3(pos,vel,m) {}


Particle::Derivative Particle::calculateDerivative() {
    Particle::Derivative d ={
            velocity,
            (forceAccum/mass)
    };
    return d;
}

Particle::Derivative Particle::calculateDerivative(Particle p) {
    Particle::Derivative d ={
            p.velocity,
            (p.forceAccum/p.mass)
    };
    return d;
}

void Particle::updateState(Particle::Derivative d) {
    position = position+d.velocity;
    velocity = velocity+d.accelaration;
}


//TODO how to make this not return a new particle
Particle Particle::calculateState(Particle::Derivative d) {
    Particle result = *this;
    result.position = result.position+d.velocity;
    result.velocity = result.velocity+d.accelaration;
    return result;
}