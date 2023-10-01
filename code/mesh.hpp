#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "point.hpp"
#include "vector.hpp"

struct Vertex {
    Point Position;
    Vector Normal;
    Point Color;
    Vector Bary;
    //glm::vec2 TexCoords;

    Vertex(Point P, Vector N, Point C) :
        Position(P), Normal(N), Color(C), Bary(Vector(1, 0, 0)) {}

    Vertex(Point P, Vector N, Point C, Point B) :
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

    Point min_vertex{0, 0, 0};
    Point max_vertex{0, 0, 0};

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