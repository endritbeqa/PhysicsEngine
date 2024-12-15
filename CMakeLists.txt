cmake_minimum_required(VERSION 3.24)
project(PhysicsEngine)
set(CMAKE_CXX_STANDARD 20)


include_directories(${CMAKE_SOURCE_DIR})

set(ENGINE_HEADERS
        #Core objects
        "include/core/objects/3D/Object3.h"
        "include/core/objects/3D/Particle.h"
        #Forces
        "include/forces/Force.h"
        "include/forces/GravityForce.h"
        "include/forces/FrictionForce.h"
        "include/forces/SpringForce.h"
        "include/forces/DragForce.h"
        #Maths
        "include/math/Vector2.h"
        "include/math/Vector3.h"
        "include/math/Matrix2.h"
        "include/math/Matrix3.h"
        "include/math/Quaternion.h"
        #Solvers
        "include/solvers/Solver.h"
        "include/solvers/Euler.h"
        "include/solvers/RK4.h"
)


set(ENGINE_SOURCES
        #Core objects
        "src/core/objects/3D/Object3.cpp"
        "src/core/objects/3D/Particle.cpp"
        #Forces
        "src/forces/GravityForce.cpp"
        "src/forces/FrictionForce.cpp"
        "src/forces/SpringForce.cpp"
        "src/forces/DragForce.cpp"
        include/core/objects/3D/Plane.h
        #Maths
        #"src/math/Vector2.cpp"
        #"src/math/Vector3.cpp"
        #"src/math/Matrix2.cpp"
        #"src/math/Matrix3.cpp"
        #"src/math/Quaternion.cpp"
        #Solvers
)

add_library(Engine ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_compile_features(Engine PUBLIC cxx_std_20)


add_executable(Particle_Demo Demos/Particle_Demo.cpp)
target_include_directories(Particle_Demo PRIVATE /include)
target_link_libraries(Particle_Demo PUBLIC Engine)
