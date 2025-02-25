#ifndef PHYSICSENGINE_RIGITBODYSYSTEM_H
#define PHYSICSENGINE_RIGITBODYSYSTEM_H

#include <vector>
#include <memory>
#include "Physics/include/core/objects/3D/RigitBody.h"
#include "Physics/include/forces/Force.h"
#include "Physics/include/solvers/RK4.h"



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





#endif //PHYSICSENGINE_RIGITBODYSYSTEM_H
