#include "include/core/systems/RigitBodySystem.h"
#include "include/forces/GravityForce.h"


int main() {

    RigitBodySystem system = RigitBodySystem();

    RK4 solver = RK4();
    GravityForce gravity = GravityForce();

    system.solver = solver;
    system.time = 0;
    system.dt = 0.001;

    RigitBody body1();
    RigitBody body2();
    RigitBody body3();

    system.bodies.push_back(std::make_shared<RigitBody>(body1));
    system.bodies.push_back(std::make_shared<RigitBody>(body2));
    system.bodies.push_back(std::make_shared<RigitBody>(body3));


    for (std::shared_ptr<RigitBody> p: system.bodies){
        gravity.objects.push_back(p);
    }

    system.forces.push_back(std::make_shared<GravityForce>(gravity));

    for(int i=0; i<10000; i++){
        system.step();
        std::cout<<i<<": "<<system.time<<"  "<<"Position:"<<system.bodies[0]->position<<"\n";
    }

    std::cout << "Breakpoint";

}