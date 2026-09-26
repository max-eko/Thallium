#ifndef THALLIUM_MESH_H
#define THALLIUM_MESH_H

#include <glad/glad.h>

#include <vector>


class Mesh
{
    public:
        Mesh(const std::vector<float>& vert, const std::vector<unsigned int>& ind);
        void draw();
    private:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        unsigned int EBO, VBO, VAO;



};

#endif
