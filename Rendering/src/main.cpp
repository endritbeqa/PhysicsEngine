#include <array>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/libs/glad/glad.h"

#include "Shader.cpp"
#include "include/Camera.h"
#include "Rendering/include/Geomtries.h"
#include "Rendering/include/Wireframe.h"
#include "Rendering/include/window.h"
#include "Rendering/libs/glfw-3.4/include/GLFW/glfw3.h"

const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 1000;
const unsigned int WIRE = 1;


void processInput(GLFWwindow *window, Camera* camera) {
    float cameraSpeed = 0.01f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position += cameraSpeed * camera->front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position -= cameraSpeed * camera->front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;

}

int main() {
    GLFWwindow *window = getGLFWwindow(SCREEN_WIDTH, SCREEN_HEIGHT, true);

    Texture tex = Texture("/home/endrit/CLionProjects/PhysicsEngine/Rendering/resources/textures/checkerboard.jpg");
    std::vector<unsigned int> textures;
    textures.push_back(tex.id);
    std::vector<Mesh> meshes;
    std::vector<Wireframe> wireframes;

    Shader meshVertexShader = Shader("/home/endrit/CLionProjects/PhysicsEngine/Rendering/shaders/sources/vertex.txt",GL_VERTEX_SHADER);
    Shader meshFragmentShader = Shader("/home/endrit/CLionProjects/PhysicsEngine/Rendering/shaders/sources/fragment.txt", GL_FRAGMENT_SHADER);
    ShaderProgram meshShaderProgram = ShaderProgram(std::vector<unsigned int>{meshVertexShader.ID, meshFragmentShader.ID});
    meshShaderProgram.createShaderProgram();

    Shader wireframeVertexShader = Shader("/home/endrit/CLionProjects/PhysicsEngine/Rendering/shaders/sources/wireframe/vertex.txt",GL_VERTEX_SHADER);
    Shader wireframeFragmentShader = Shader("/home/endrit/CLionProjects/PhysicsEngine/Rendering/shaders/sources/wireframe/fragment.txt", GL_FRAGMENT_SHADER);
    ShaderProgram wireframeShaderProgram = ShaderProgram(std::vector<unsigned int>{wireframeVertexShader.ID, wireframeFragmentShader.ID});
    wireframeShaderProgram.createShaderProgram();


    CubeWireframe cubeWire = CubeWireframe(0.5);
    SphereWireframe sphereWire = SphereWireframe(0.5, 50, 50);
    cubeWire.setupWireframe();
    sphereWire.setupWireframe();
    cubeWire.shaderProgram = &wireframeShaderProgram;
    sphereWire.shaderProgram = &wireframeShaderProgram;
    wireframes.push_back(sphereWire);
    //wireframes.push_back(cubeWire);


    CubeMesh cube = CubeMesh(0.5);
    Sphere sphere = Sphere(0.5, 30, 20);
    Plane plane = Plane(1.0,1.0);
    plane.model = glm::translate(plane.model, glm::vec3(0.0f, -1.0f, 0.0f));
    plane.model = glm::rotate(plane.model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


    cube.setupMesh();
    sphere.setupMesh();
    plane.setupMesh();
    cube.textures.push_back(tex);
    sphere.textures.push_back(tex);
    plane.textures.push_back(tex);
    cube.shaderProgram = &meshShaderProgram;
    sphere.shaderProgram = &meshShaderProgram;
    plane.shaderProgram = &meshShaderProgram;

    //meshes.push_back(cube);
    meshes.push_back(sphere);
    meshes.push_back(plane);


    Camera camera = Camera(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 view;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.01f, 1000.0f);


    while (!glfwWindowShouldClose(window)) {
        processInput(window, &camera);
        camera.update();
        view = camera.view;

        glEnable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (WIRE) {
            for (Wireframe &wire: wireframes) {
                glUseProgram(wire.shaderProgram->ID);
                wire.shaderProgram->setMat4("model", wire.model);
                wire.shaderProgram->setMat4("view", view);
                wire.shaderProgram->setMat4("projection", projection);
                wire.draw();
            }
        }
        else {
            for (Mesh &mesh: meshes) {
                glUseProgram(mesh.shaderProgram->ID);
                mesh.shaderProgram->setMat4("model", mesh.model);
                mesh.shaderProgram->setMat4("view", view);
                mesh.shaderProgram->setMat4("projection", projection);
                mesh.draw();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Cleanup
    //glDeleteVertexArrays(geometries.size(), VAOs.data());
    //glDeleteBuffers(NUM_TRIANGLES, VBOs.data());
    //glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
