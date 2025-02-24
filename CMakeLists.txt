cmake_minimum_required(VERSION 3.24)
project(PhysicsEngine)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(math)
add_subdirectory(Physics)
add_subdirectory(Rendering)