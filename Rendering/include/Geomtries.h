#ifndef GEOMTRIES_H
#define GEOMTRIES_H

#include <array>
#include <iostream>
#include <math.h>
#include <vector>
#include <glm/vec3.hpp>
#include <Rendering/libs/glad/glad.h>


class Vertex {
    Vertex(float x,float y,float z,float r,float g,float b,float s,float t,float Nx,float Ny,float Nz);
    Vertex(glm::vec3 p);

    std::array<float, 3> position;
    std::array<float, 3> color;
    std::array<float, 2> textureCoord;
    std::array<float, 3> normal;
};


class Geometry {

public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;

    Geometry();
    virtual ~Geometry();
    virtual void bindGeometry();
    virtual void draw();
};


class Plane{
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    unsigned int texture;
    Plane(float width, float height);
    void bindGeometry();
    void draw();

};



class Sphere : public Geometry {
public:
    Sphere(float radius, int sectorCount, int stackCount);

};


class CubeMesh : public Geometry {
public:
    CubeMesh(float size);
};




#endif //GEOMTRIES_H
