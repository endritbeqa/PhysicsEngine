//
// Created by endrit on 18.12.24.
//

#include "include/core/systems/ParticleSystem.h"


ParticleSystem::ParticleSystem(){}

void ParticleSystem::step() {

    for (std::shared_ptr<Force> force: forces) {
        force->apply();
    }
    for (std::shared_ptr<Particle> p: particles) {
        solver.step(p, dt);
        p->resetForces();
    }

    for (std::shared_ptr<Particle> p: particles) {
        for (std::shared_ptr<Plane> plane: planes) {
            if (plane->checkCollision(p)) {
                //std::cout << "collision detected";
            }
        }
    }

    time = time + dt;

}