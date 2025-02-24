#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Rendering/include/Shader.h"
#include "Rendering/libs/glad/glad.h"
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(std::string shaderPath, unsigned int shaderType){

    type = shaderType;
    std::ifstream file(shaderPath);
    if(!file){
        std::cerr<<"ERROR: Could not open file at"<< shaderPath;
    }

    std::stringstream  buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    const char *shaderSource = content.c_str();

    ID = glCreateShader(shaderType);
    glShaderSource(ID, 1, &shaderSource, nullptr);
    glCompileShader(ID);

    int success;
    char infoLog[512];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::"<<shaderPath<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


ShaderProgram::ShaderProgram(std::vector<unsigned int> shaders) {
    this->shaders = shaders;
}

void ShaderProgram::setMat4(std::string name, glm::mat4 matrix) {
    int viewLoc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}


void ShaderProgram::createShaderProgram() {

    int success;
    char infoLog[512];
    unsigned int shaderProgram = glCreateProgram();
    for(unsigned int shader: shaders) {

        glAttachShader(shaderProgram, shader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(shader);
    }

    ID = shaderProgram;
}
