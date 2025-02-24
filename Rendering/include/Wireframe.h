#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <vector>

#include "Shader.h"
#include "math/include/Vector3.h"


class Wireframe {
public:
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    ShaderProgram *shaderProgram;
    glm::mat4 model = glm::mat4(1.0f);
    unsigned int VAO, VBO, EBO;

    ~Wireframe(){};
    Wireframe(){};
    Wireframe(std::vector<Vector3> &vertices, std::vector<unsigned int> &indices);
    void draw();
    void setupWireframe();

};



class SphereWireframe : public Wireframe {
public:
    SphereWireframe(float radius, int sectorCount, int stackCount);

};


class CubeWireframe : public Wireframe {
public:
    CubeWireframe(float size);
};


class OBBWireframe : public Wireframe {
public:
    OBBWireframe(std::vector<Vector3> &halfSizes, std::vector<Vector3> &orientation);
};




#endif //WIREFRAME_H
