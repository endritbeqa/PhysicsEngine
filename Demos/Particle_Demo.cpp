

#include "include/core/systems/ParticleSystem.h"
#include "include/forces/GravityForce.h"
#include "include/forces/SpringForce.h"


int main() {

    ParticleSystem system = ParticleSystem();

    RK4 solver = RK4();
    GravityForce gravity = GravityForce();
    SpringForce spring1 = SpringForce(10, 1, 3);
    Plane plane1 = Plane(Vector3(0,0,0), Vector3(0,1,0));

    system.solver = solver;
    system.time = 0;
    system.dt = 0.001;

    Particle p1(Vector3(1.0,10.0,1.0),Vector3(0.0,0.0,0.0), 2);
    Particle p2(Vector3(1.0,0,0),Vector3(0,0,0), 0.2);
    Particle p3(Vector3(2.0,0,0),Vector3(0,0,0), 0.2);

    system.particles.push_back(std::make_shared<Particle>(p1));
    system.particles.push_back(std::make_shared<Particle>(p2));
    system.particles.push_back(std::make_shared<Particle>(p3));

    system.planes.push_back(std::make_shared<Plane>(plane1));

    for (std::shared_ptr<Particle> p: system.particles){
        gravity.objects.push_back(p);
    }

    spring1.add_objects(system.particles[1], system.particles[2]);
    system.forces.push_back(std::make_shared<GravityForce>(gravity));
    system.forces.push_back(std::make_shared<SpringForce>(spring1));

    for(int i=0; i<10000; i++){
        system.step();
        //std::cout<<i<<": "<<system.time<<"  "<<"Position:"<<system.particles[0]->position<<"\n";
        std::cout<<i<<": "<<system.time<<"  "<<"Position:"<<system.particles[1]->position<<"\n";
        std::cout<<i<<": "<<system.time<<"  "<<"Position:"<<system.particles[2]->position<<"\n";

    }

    std::cout << "Breakpoint";

}