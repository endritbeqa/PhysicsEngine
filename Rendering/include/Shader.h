#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

class Shader {
public:
  Shader(std::string shaderPath, unsigned int shaderType);
  unsigned int ID;
  unsigned int type;
};

class ShaderProgram {
public:

  ShaderProgram(std::vector<unsigned int> shaders);
  unsigned int ID;
  std::vector<unsigned int> shaders;

  void createShaderProgram();
  void setMat4(std::string name, glm::mat4 mat4);

};


#endif //SHADER_H
