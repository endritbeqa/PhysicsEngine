#ifndef PHYSICSENGINE_RigitBODYSYSTEM_H
#define PHYSICSENGINE_RigitBODYSYSTEM_H

#include <vector>
#include <memory>
#include "include/core/objects/3D/RigitBody.h"
#include "include/forces/Force.h"
#include "include/solvers/RK4.h"



class RigitBodySystem {
public:

    std::vector<std::shared_ptr<RigitBody>> bodies;
    std::vector<std::shared_ptr<Force>> forces;
    RK4 solver;
    float time;
    double dt;

    RigitBodySystem();
    void step();

};





#endif //PHYSICSENGINE_RigitBODYSYSTEM_H
