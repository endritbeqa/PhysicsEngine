#include <array>
#include <cmath>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/libs/glad/glad.h"

#include "Rendering/shaders/loadShader.cpp"
#include "texture.cpp"
#include "Rendering/include/Geomtries.h"
#include "Rendering/include/window.h"
#include "Rendering/libs/glfw-3.4/include/GLFW/glfw3.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;


int main() {
    GLFWwindow *window = getGLFWwindow(SCREEN_WIDTH, SCREEN_HEIGHT, true);

    Texture tex = Texture("/home/endrit/CLionProjects/Rendering/resources/textures/checkerboard.jpg");
    std::vector<unsigned int> textures;
    std::vector<Geometry> geometries;

    textures.push_back(tex.id);

    CubeMesh cube = CubeMesh(0.5);
    Sphere sphere = Sphere(0.5, 20, 20);
    Plane plane = Plane(0.5, 0.5);

    //cube.bindGeometry();
    //sphere.bindGeometry();
    plane.bindGeometry();
    geometries.push_back(cube);

    plane.texture = textures[0];
    geometries.push_back(cube);
    //geometries.push_back(plane);
    geometries.push_back(sphere);

    unsigned int vertexShader = compileShader("/home/endrit/CLionProjects/Rendering/shaders/sources/vertex.txt",
                                              GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(
        "/home/endrit/CLionProjects/Rendering/shaders/sources/fragment.txt", GL_FRAGMENT_SHADER);
    unsigned int shaderProgram = createShaderProgram(std::vector<unsigned int>{vertexShader, fragmentShader});


    float angle = 1.0f;

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0, 0.5, 0.5));
        //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        glUseProgram(shaderProgram);
        for (Geometry geometry: geometries) {
            int intensityLocation = glGetUniformLocation(shaderProgram, "colorIntensity");
            glUniform1f(intensityLocation, 1.0);
            int transformLoc = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
            geometry.draw();
        }

        angle += 1.0f;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Cleanup
    // glDeleteVertexArrays(geometries.size(), VAOs.data());
    //glDeleteBuffers(NUM_TRIANGLES, VBOs.data());
    //glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
