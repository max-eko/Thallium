#ifndef THALLIUM_SHADER_H
#define THALLIUM_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "src/util/texture.h"

class Shader
{
public:
    unsigned int ID;

    // Constructor reads files and builds shader
    Shader(const char* vertexPath, const char* fragmentPath);


    // Activate shader
    void use() const;
    // Uniform functions for utility
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setTexture(const Texture& texture) const;
};

#endif

