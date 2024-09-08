#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh
{
private:
    // Mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Render Data
    unsigned int VAO, VBO, EBO;
    void setupMesh();
public:
    Mesh(const char* fileName);
    void draw();
};

#endif
