//
// Created by endrit on 19.12.24.
//


#include "include/core/systems/RigitBodySystem.h"


RigitBodySystem::RigitBodySystem(){}

void RigitBodySystem::step() {

    for (std::shared_ptr<Force> force: forces) {
        force->apply();
    }
    for (std::shared_ptr<RigitBody> body: bodies) {
        solver.step(body, dt);
        body->resetForces();
    }

    time = time + dt;

}