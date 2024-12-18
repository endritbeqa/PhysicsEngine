//
// Created by endrit on 18.12.24.
//

#ifndef PHYSICSENGINE_PARTICLESYSTEM_H
#define PHYSICSENGINE_PARTICLESYSTEM_H

#include "include/core/objects/3D/Particle.h"
#include "include/forces/Force.h"
#include "include/solvers/RK4.h"
#include "include/collisions/Plane.h"
#include "include/solvers/Euler.h"
#include <memory>
#include <vector>

class ParticleSystem {
public:

    std::vector<std::shared_ptr<Particle>> particles;
    std::vector<std::shared_ptr<Plane>> planes;
    std::vector<std::shared_ptr<Force>> forces;
    RK4 solver;
    float time;
    double dt;

    ParticleSystem();
    void step();

};


#endif //PHYSICSENGINE_PARTICLESYSTEM_H
