#include "include/core/objects/3D/Particle.h"

Particle::Particle(){}

Particle::Particle(Vector3 pos, Vector3 vel, float m): Object3(pos,vel,m) {}

Particle::Derivative Particle::calculateDerivative(Particle p, float dt) {
    Particle::Derivative d ={
            p.velocity*dt,
            (p.forceAccum/p.mass)*dt
    };
    return d;
}

void Particle::updateState(Particle::Derivative d) {
    position = position+d.velocity;
    velocity = velocity+d.accelaration;
}

Particle Particle::calculateState(Particle::Derivative d) {
    return Particle(position+d.velocity,velocity+d.accelaration, mass);
}