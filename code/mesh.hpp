#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "vector.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Color;
    glm::vec3 Bary;
    //glm::vec2 TexCoords;

    Vertex(glm::vec3 P, glm::vec3 N, glm::vec3 C) :
        Position(P), Normal(N), Color(C), Bary(glm::vec3(1, 0, 0)) {}

    Vertex(glm::vec3 P, glm::vec3 N, glm::vec3 C, glm::vec3 B) :
        Position(P), Normal(N), Color(C), Bary(B) {}
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    glm::vec3 min_vertex{0, 0, 0};
    glm::vec3 max_vertex{0, 0, 0};

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::string path);
    ~Mesh() {};

    void Center();
    void Scale(double coeff);
    
    static Mesh Sphere(int size);

private:

    void AddAiNode(const aiNode* node, const aiScene* scene);
    void AddAiMesh(const aiMesh* mesh, const aiScene* scene);
};



#endif