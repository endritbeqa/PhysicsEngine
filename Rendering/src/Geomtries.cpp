#include "Rendering/include/Geomtries.h"




    Geometry::Geometry() {};

    Geometry::~Geometry() {};

    void Geometry::bindGeometry() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);
        //glEnableVertexAttribArray(2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(float), &indices[0], GL_STATIC_DRAW);
    }

    void Geometry::draw() {
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, indices.size() , GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }



    Plane::Plane(float width, float height) {
        vertices = {
            -width / 2, -height / 2, 0, 1, 1, 0, 0.0, 0.0,
             width / 2, -height / 2, 0, 1, 1, 0, 1.0, 0.0,
             width / 2,  height / 2, 0, 1, 1, 0, 1.0, 1.0,
            -width / 2, -height / 2, 0, 1, 1, 0, 0.0, 0.0,
             width / 2,  height / 2, 0, 1, 1, 0, 1.0, 1.0,
            -width / 2,  height / 2, 0, 1, 1, 0, 0.0, 1.0
        };
    };


    //TODO this doesn't work the base class function gets called
    void Plane::bindGeometry() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
       }

    //TODO this doesn't work the base class function gets called
    void Plane::draw() {
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    Sphere::Sphere(float radius, int sectorCount, int stackCount) {
        float x, y, z, xy;
        float nx, ny, nz, lengthInv = 1.0f / radius;
        float s, t;

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

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
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
            -halfSize, -halfSize, halfSize,   //1.0f, 0.0f, 0.0f, // 0, 0,
            halfSize, -halfSize, halfSize,    //1.0f, 0.0f, 0.0f, // 1, 0,
            halfSize, halfSize, halfSize,     //1.0f, 0.0f, 0.0f, // 1, 1,
            -halfSize, halfSize, halfSize,    //1.0f, 0.0f, 0.0f, // 0, 1,
                                              //
            -halfSize, -halfSize, -halfSize,  //1.0f, 0.0f, 0.0f, // 0, 1,
            halfSize, -halfSize, -halfSize,   //1.0f, 0.0f, 0.0f, // 1, 1,
            halfSize, halfSize, -halfSize,    //1.0f, 0.0f, 0.0f, // 1, 0.5,
            -halfSize, halfSize, -halfSize   //1.0f, 0.0f, 0.0f // 1, 1
        };

        indices = {
            0, 1, 2,
            2, 3, 0,
            4, 7, 6,
            6, 5, 4,
            0, 3, 7,
            7, 4, 0,
            1, 5, 6,
            6, 2, 1,
            0, 1, 5,
            5, 4, 0,
            3, 2, 6,
            6, 7, 3

        };
    }



