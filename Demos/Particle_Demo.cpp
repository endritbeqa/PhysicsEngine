#include <vector>
#include "../include/core/objects/3D/Particle.h"
#include "../include/forces/GravityForce.h"
#include "../include/forces/SpringForce.h"
#include "../include/solvers/RK4.h"
#include <memory>


class ParticleSystem {
public:
    std::vector<std::shared_ptr<Particle>> particles;
    float time;
    float dt;
    std::vector<std::shared_ptr<Force>> forces;
    RK4 solver;


    void step() {
        for (std::shared_ptr<Force> force: forces) {
            force->apply();
            }

        for(std::shared_ptr<Particle> p: particles){
            solver.step(p, time, dt);
            p->resetForces();
        }
        time = time+dt;
    }

};


int main() {

    RK4 solver = RK4();
    GravityForce gravity = GravityForce();

    SpringForce spring1 = SpringForce(3.5, 0.1, 1);
    ParticleSystem system = ParticleSystem();
    system.solver = solver;
    system.time = 0;
    system.dt = 0.01;



    Particle p1(Vector3(1.0,1.0,1.0),Vector3(0.0,0.0,0.0), 1);
    Particle p2(Vector3(1.0,0,0),Vector3(0,0,0), 2);
    Particle p3(Vector3(5,0,0),Vector3(0,0,0), 2);

    system.particles.push_back(std::make_shared<Particle>(p1));
    system.particles.push_back(std::make_shared<Particle>(p2));
    system.particles.push_back(std::make_shared<Particle>(p3));



    for (std::shared_ptr<Particle> p: system.particles){
        gravity.objects.push_back(p);
    }

    spring1.add_objects(system.particles[1], system.particles[2]);
    system.forces.push_back(std::make_shared<GravityForce>(gravity));
    system.forces.push_back(std::make_shared<SpringForce>(spring1));

    for(int i=0; i<100; i++){
        system.step();
        std::cout<<i<<"Position:"<<system.particles[1]->position<<"\n";
        std::cout<<i<<"Velocity:"<<system.particles[1]->velocity<<"\n";

    }




    std::cout << "Breakpoint";

}