#include "Rendering/include/Wireframe.h"
#include "Rendering/libs/glad/glad.h"

Wireframe::Wireframe(std::vector<Vector3>& verts, std::vector<unsigned int> &inds){
  vertices = verts;
  indices = inds;
}


void Wireframe::setupWireframe(){
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void *) 0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}


void Wireframe::draw(){
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glUseProgram(0);
}


SphereWireframe::SphereWireframe(float radius, int sectorCount, int stackCount) {
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

            vertices.push_back(Vector3(x, y, z));
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


CubeWireframe::CubeWireframe(float size) {
    float halfSize = size / 2.0f;

    vertices = {
        Vector3(-halfSize, -halfSize, halfSize),
        Vector3(halfSize, -halfSize, halfSize),
        Vector3(halfSize, halfSize, halfSize),
        Vector3(-halfSize, halfSize, halfSize),

        Vector3(-halfSize, -halfSize, -halfSize),
        Vector3(halfSize, -halfSize, -halfSize),
        Vector3(halfSize, halfSize, -halfSize),
        Vector3(-halfSize, halfSize, -halfSize)
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



AABBWireframe::AABBWireframe(Vector3 &center, Vector3 &halfSizes) {


    vertices = {
        Vector3(center[0]-halfSizes[0], center[1]-halfSizes[1], center[2]+halfSizes[2]),
        Vector3(center[0]+halfSizes[0], center[1]-halfSizes[1], center[2]+halfSizes[2]),
        Vector3(center[0]+halfSizes[0], center[1]+halfSizes[1], center[2]+halfSizes[2]),
        Vector3(center[0]-halfSizes[0], center[1]+halfSizes[1], center[2]+halfSizes[2]),
        Vector3(center[0]-halfSizes[0], center[1]-halfSizes[1], center[2]-halfSizes[2]),
        Vector3(center[0]+halfSizes[0], center[1]-halfSizes[1], center[2]-halfSizes[2]),
        Vector3(center[0]+halfSizes[0], center[1]+halfSizes[1], center[2]-halfSizes[2]),
        Vector3(center[0]-halfSizes[0], center[1]+halfSizes[1], center[2]-halfSizes[2])
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

