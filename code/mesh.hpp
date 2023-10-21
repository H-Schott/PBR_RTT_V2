#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "point.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include "ray.hpp"

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:

    std::vector<Triangle> triangles;
    std::vector<Vector> normals;
    std::vector<Texture> textures;

    Point min_vertex{0, 0, 0};
    Point max_vertex{0, 0, 0};

    Mesh() {};
    Mesh(const std::vector<Point>& points,
         const std::vector<unsigned int>& indices,
         const std::vector<Texture>& _textures);
    Mesh(const std::vector<Triangle>& t);
    Mesh(const std::vector<Triangle>& t, const std::vector<Vector>& n);
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