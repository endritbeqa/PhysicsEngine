#ifndef GEOMTRIES_H
#define GEOMTRIES_H

#include <vector>
#include <glm/mat4x4.hpp>

#include "Shader.h"
#include "math/include/Vector3.h"
#include "math/include/Vector2.h"
#include "Rendering/include/texture.h"


class Vertex {
public:
    Vertex(Vector3 &pos, Vector3 &nor, Vector2 &tex);

    Vertex(const Vector3 &pos, const Vector3 & nor,const Vector2 & tex):position(pos), normal(nor), textureCoord(tex){}

    Vector3 position;
    Vector3 normal;
    Vector2 textureCoord;
};


class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    glm::mat4 model = glm::mat4(1.0f);
    ShaderProgram *shaderProgram;//TODO convert this to smart pointer
    unsigned int VAO, VBO, EBO;

    ~Mesh(){};
    Mesh();
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
    void draw();
    void setupMesh();

};



class Plane :public  Mesh{
public:
    Plane(float width, float height);
};



class Sphere : public Mesh {
public:
    Sphere(float radius, int sectorCount, int stackCount);

};


class CubeMesh : public Mesh {
public:
    CubeMesh(float size);
};




#endif //GEOMTRIES_H
