cmake_minimum_required(VERSION 3.24)
project(PhysicsEngine)
set(CMAKE_CXX_STANDARD 20)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})

set(Math_Library ${PARENT_DIR}/math/build/libMath.a)

set(ENGINE_HEADERS
        include/core/objects/3D/Object3.h
        include/core/objects/3D/Particle.h
        include/core/objects/3D/RigitBody.h
        include/forces/Force.h
        include/forces/GravityForce.h
        include/forces/FrictionForce.h
        include/forces/SpringForce.h
        include/forces/DragForce.h
        include/solvers/Solver.h
        include/solvers/Euler.h
        include/solvers/RK4.h
        include/core/systems/ParticleSystem.h
        include/collisions/Plane.h
        include/collisions/utils/Octree.h
        include/collisions/utils/AABB.h
        include/collisions/BoundingVolumes/BoundingVolume.h
        include/collisions/BoundingVolumes/Sphere.h
        include/collisions/BoundingVolumes/OBB.h
        include/collisions/BoundingVolumes/AABB.h
        include/collisions/PrimitiveTests/PrimitiveTests.h
        include/collisions/PrimitiveTests/ClosestPoint.h
        include/collisions/BoundingVolumeHierarchies/TopDown.h
        include/collisions/BoundingVolumeHierarchies/BottomUp.h
        include/collisions/BoundingVolumeHierarchies/Insertion.h

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
        src/core/systems/RigitBodySystem.cpp
        src/collisions/BoundingVolumes/AABB.cpp
        src/collisions/BoundingVolumes/Sphere.cpp
        src/collisions/BoundingVolumes/OBB.cpp
)

add_library(Engine ${ENGINE_HEADERS} ${ENGINE_SOURCES} ${Math_Library})
target_compile_features(Engine PUBLIC cxx_std_20)

add_executable(Demo  Demos/RigitBodyDemo.cpp)
target_include_directories(Demo PRIVATE /include)
target_link_libraries(Demo PUBLIC Engine)
