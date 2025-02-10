#include "Physics/include/core/systems/RigitBodySystem.h"
#include "Physics/include/forces/GravityForce.h"


int main() {

    RigitBodySystem system = RigitBodySystem();

    RK4 solver = RK4();
    GravityForce gravity = GravityForce();

    system.solver = solver;
    system.time = 0;
    system.dt = 0.001;


    RigitBody body1(Vector3(1.0,10.0,1.0),Vector3(0.0,0.0,0.0), 2);
    RigitBody body2(Vector3(1.0,0,0),Vector3(0,0,0), 0.2);
    RigitBody body3(Vector3(2.0,0,0),Vector3(0,0,0), 0.2);

    system.bodies.push_back(std::make_shared<RigitBody>(body1));
    system.bodies.push_back(std::make_shared<RigitBody>(body2));
    system.bodies.push_back(std::make_shared<RigitBody>(body3));


    for (std::shared_ptr<RigitBody> p: system.bodies){
        gravity.objects.push_back(p);
    }

    system.forces.push_back(std::make_shared<GravityForce>(gravity));

    for(int i=0; i<100; i++){
        system.step();
        std::cout<<i<<": "<<system.time<<"  "<<"Position:"<<system.bodies[0]->position<<"\n";
    }

    std::cout << "Breakpoint";

}
