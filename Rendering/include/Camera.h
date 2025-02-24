#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>


class Camera{
public:

  glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 position;
  glm::vec3 target;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;
  glm::mat4 view;

  Camera(){};
  ~Camera(){};
  Camera(glm::vec3 pos, glm::vec3 tar){
    position = pos;
    target = tar;
    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(front,right));
    view = glm::lookAt(position, target, worldUp);
  }

  void update(){
    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(front,right));
    view = glm::lookAt(position, target, worldUp);
  }



};


#endif //CAMERA_H
