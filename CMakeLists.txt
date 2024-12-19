cmake_minimum_required(VERSION 3.24)
project(PhysicsEngine)
set(CMAKE_CXX_STANDARD 20)


include_directories(${CMAKE_SOURCE_DIR})

set(ENGINE_HEADERS
        include/core/objects/3D/Object3.h
        include/core/objects/3D/Particle.h
        include/core/objects/3D/RigitBody.h
        include/forces/Force.h
        include/forces/GravityForce.h
        include/forces/FrictionForce.h
        include/forces/SpringForce.h
        include/forces/DragForce.h
        include/math/Vector2.h
        include/math/Vector3.h
        include/math/Matrix2.h
        include/math/Matrix3.h
        include/math/Quaternion.h
        include/solvers/Solver.h
        include/solvers/Euler.h
        include/solvers/RK4.h
        include/collisions/Plane.h
        include/core/systems/ParticleSystem.h
        include/collisions/utils/Octree.h
)


set(ENGINE_SOURCES
        src/core/objects/3D/Object3.cpp
        src/core/objects/3D/Particle.cpp
        src/forces/GravityForce.cpp
        src/forces/FrictionForce.cpp
        src/forces/SpringForce.cpp
        src/forces/DragForce.cpp
        src/collisions/Plane.cpp
        src/core/objects/3D/RigitBody.cpp
        src/core/systems/ParticleSystem.cpp
        include/collisions/utils/AABB.h
        include/math/Point3.h
        src/core/systems/RigitBodySystem.cpp

)

add_library(Engine ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_compile_features(Engine PUBLIC cxx_std_20)


add_executable(Demo  Demos/RigitBodyDemo.cpp)
target_include_directories(Demo PRIVATE /include)
target_link_libraries(Demo PUBLIC Engine)
