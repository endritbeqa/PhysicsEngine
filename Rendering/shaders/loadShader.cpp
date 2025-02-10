#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Rendering/libs/glad/glad.h"



int compileShader(std::string shaderPath, unsigned int shaderType){

    std::ifstream file(shaderPath);
    if(!file){
        std::cerr<<"ERROR: Could not open file at"<< shaderPath;
        return 0;
    }

    std::stringstream  buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    const char *shaderSource = content.c_str();

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::"<<shaderPath<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}



unsigned int createShaderProgram(std::vector<unsigned int> shaders) {

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

    return shaderProgram;
}
