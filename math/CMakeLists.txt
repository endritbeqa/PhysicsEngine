cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        include/Vector2.h
        include/Vector3.h
        include/Matrix2.h
        include/Matrix3.h
        include/Quaternion.h
        include/Plane3.h
        include/utils.h
        include/math.cpp
)

add_library(Math STATIC ${SOURCES})
target_include_directories(Math PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

