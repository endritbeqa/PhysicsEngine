cmake_minimum_required(VERSION 3.27)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(PhysicsEngine src/main.cpp
        include/math/Vector2.h
        include/core/Object2.h
        include/math/Vector3.h
        include/core/Object3.h
        include/math/Matrix3.h
        include/math/Quaternion.h
        include/forces/Force.h
)
