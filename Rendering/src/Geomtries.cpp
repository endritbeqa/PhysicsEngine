#include <iostream>
#include "Rendering/include/Geomtries.h"
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/libs/glad/glad.h"


Vertex::Vertex(Vector3 &pos, Vector3 &nor, Vector2 &tex) {
    position = pos;
    normal = nor;
    textureCoord = tex;
}

Mesh::Mesh(std::vector<Vertex> &verts, std::vector<unsigned int> &inds, std::vector<Texture> &texs) {
    vertices = verts;
    indices = inds;
    textures = texs;
    setupMesh();
}


Mesh::Mesh() {
}


void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Mesh::draw() {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
            //shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}


Sphere::Sphere(float radius, int sectorCount, int stackCount) {
    float x, y, z, xy;

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            vertices.push_back(Vertex(Vector3(x, y, z), Vector3(0, 0, 1), Vector2(x*x, y*y)));
        }
    }

    for (int i = 0; i < stackCount; ++i) {
        int k1 = i * (sectorCount + 1);
        int k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}


CubeMesh::CubeMesh(float size) {
    float halfSize = size / 2.0f;

    vertices = {
        Vertex(Vector3(-halfSize, -halfSize, halfSize), Vector3(0.0f, 0.0f, 1.0f), Vector2(0, 0)),
        Vertex(Vector3(halfSize, -halfSize, halfSize), Vector3(0.0f, 0.0f, 1.0f), Vector2(1, 0)),
        Vertex(Vector3(halfSize, halfSize, halfSize), Vector3(0.0f, 0.0f, 1.0f), Vector2(1, 1)),
        Vertex(Vector3(-halfSize, halfSize, halfSize), Vector3(0.0f, 0.0f, 1.0f), Vector2(0, 1)),

        Vertex(Vector3(-halfSize, -halfSize, -halfSize), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 0)),
        Vertex(Vector3(halfSize, -halfSize, -halfSize), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 0)),
        Vertex(Vector3(halfSize, halfSize, -halfSize), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 1)),
        Vertex(Vector3(-halfSize, halfSize, -halfSize), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 1))
    };

    indices = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        1, 5, 6,
        6, 2, 1,
        3, 2, 6,
        6, 7, 3,
        0, 4, 5,
        5, 1, 0
    };
}


Plane::Plane(float width, float height) {
    vertices = {
        Vertex(Vector3(-width/2, -height/2 , 0), Vector3(0,0,1), Vector2(0,0)),
        Vertex(Vector3(width/2, -height/2 , 0), Vector3(0,0,1), Vector2(1,0)),
        Vertex(Vector3(width/2, height/2 , 0), Vector3(0,0,1), Vector2(1,1)),
        Vertex(Vector3(-width/2, height/2 , 0), Vector3(0,0,1), Vector2(0,1 ))
    };

    indices = {
    0, 1, 2,
    2, 3, 0};
}



