cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PARENT_DIR})
add_subdirectory(libs/glfw-3.4)
find_package(glm REQUIRED)

set(SHADER_FILES shaders/loadShader.cpp)
set(GLAD libs/glad/glad.c)
set(STBI libs/stbi/stb_image.cpp)

set(INCLUDE_FILES include/window.h
        include/Geomtries.h)

set(SOURCE_FILES src/window.cpp
        src/texture.cpp
        src/Geomtries.cpp)

add_library(DEPENDENCIES ${SHADER_FILES} ${GLAD} ${STBI} ${INCLUDE_FILES} ${SOURCE_FILES})

target_include_directories(DEPENDENCIES PUBLIC libs)
add_executable(RenderingEngine src/main.cpp)

target_link_libraries(RenderingEngine glfw DEPENDENCIES dl glm::glm-header-only)