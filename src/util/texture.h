#ifndef THALLIUM_TEXTURE_H
#define THALLIUM_TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <iostream>
#include <string>

class Texture
{

public:
    Texture(const char* name, const char* filepath);
    unsigned int getID() const;
    unsigned int getUnit() const;
    const std::string& getName() const;
    void use();

private:
    unsigned int textureUnit;
    unsigned int ID;
    unsigned char *data;
    int width, height, nrChannels;
    std::string textureName;

    static inline unsigned int objectCounter = 0;
};

#endif
