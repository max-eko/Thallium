#include "src/util/texture.h"

Texture::Texture(const char* name, const char* filepath)
{
    // Create unique texture unit
    textureUnit = objectCounter;
    objectCounter++;
    // Set name
    textureName = name;
    // Bind the textures
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, send to OpenGL
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;

        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else
        {
            std::cout << "Unsupported number of channels \n";
            stbi_image_free(data);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // De-allocate image memory, as it has been passed to OpenGL
    stbi_image_free(data);
}
unsigned int Texture::getID() const
{
    return ID;
}
unsigned int Texture::getUnit() const
{
    return textureUnit;
}
const std::string& Texture::getName() const
{
    return textureName;
}
void Texture::use()
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}