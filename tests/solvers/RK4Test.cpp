#include "include/core/systems/ParticleSystem.h"
#include <gtest/gtest.h>

TEST(SolverTest, Gravity){

    ParticleSystem system = ParticleSystem();
    RK4 solver = RK4();
    GravityForce gravity = GravityForce();
    system.solver = solver;
    system.time = 0;
    system.dt = 0.001;

    Particle p1(Vector3(1.0,10.0,1.0),Vector3(0.0,0.0,0.0), 2);
    system.particles.push_back(std::make_shared<Particle>(p1));

    for (std::shared_ptr<Particle> p: system.particles){
        gravity.objects.push_back(p);
    }

    system.forces.push_back(std::make_shared<GravityForce>(gravity));

    for(int i=0; i<1000; i++){
        system.step();
    }

    EXPECT_TRUE(4.9<p1.position.y<5.2);
}
