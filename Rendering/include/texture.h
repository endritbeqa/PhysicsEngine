#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>
#include "Rendering/libs/glad/glad.h"
#include "Rendering/libs/stbi/stb_image.h"

class Texture {
public:
    std::string filepath;
    std::string type;
    int width, height, nrChannels;
    unsigned int id;
    unsigned char *data;

    Texture(std::string texturePath);
};



#endif //TEXTURE_H
