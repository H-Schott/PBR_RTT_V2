#include "mesh.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    //std::cout << vertices.size() << std::endl;
    //std::cout << indices.size() / 3 << std::endl;

}


Mesh::Mesh(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    AddAiNode(scene->mRootNode, scene);

    std::cout << indices.size() / 3. << " faces." << std::endl;
    std::cout << vertices.size() << " vertices." << std::endl;
}


void Mesh::AddAiNode(const aiNode* node, const aiScene* scene) {
    for(int i = 0; i < node->mNumMeshes; i++) {
        AddAiMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for(int i = 0; i < node->mNumChildren; i++) {
        AddAiNode(node->mChildren[i], scene);
    }
}


void Mesh::AddAiMesh(const aiMesh* mesh, const aiScene* scene) {
    int offset = vertices.size();
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 p;
        p.x = mesh->mVertices[i].x;
        p.y = mesh->mVertices[i].y;
        p.z = mesh->mVertices[i].z;
        // update min/max
        for (int j = 0; j < 3; j++) {
            if (p[j] > max_vertex[j]) max_vertex[j] = p[j];
            if (p[j] < min_vertex[j]) min_vertex[j] = p[j];
        }
        
        glm::vec3 n;
        n.x = mesh->mNormals[i].x;
        n.y = mesh->mNormals[i].y;
        n.z = mesh->mNormals[i].z;
        //glm::vec3 c(0.8, 0.8, 0.8);
        glm::vec3 c(0.38, 0.306, 0.102);
        vertices.push_back(Vertex(p, n, c));
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(offset + face.mIndices[j]);
    }
}


void Mesh::Center() {
    glm::vec3 centre = (max_vertex + min_vertex);
    centre *= 0.5;
    int nb_vertices = vertices.size();
    for (int i = 0; i < nb_vertices; i++) {
        vertices[i].Position -= centre;
    }

    min_vertex -= centre;
    max_vertex -= centre;
}


void Mesh::Scale(double coeff) {
    int nb_vertices = vertices.size();
    for (int i = 0; i < nb_vertices; i++) {
        vertices[i].Position *= coeff;
    }

    min_vertex *= coeff;
    max_vertex *= coeff;
}


Mesh Mesh::Sphere(int size) {

    glm::vec3 white = glm::vec3(1, 1, 1);
    std::vector<Vertex> v;

    // top and bottom vertices
    v.push_back(Vertex(glm::vec3(0., 0., -1), glm::vec3(0., 0., -1), white));
    v.push_back(Vertex(glm::vec3(0., 0., 1),  glm::vec3(0., 0., 1),  white));

    // min / max vertices
    glm::vec3 mi{ 0, 0, 0 };
    glm::vec3 ma{ 0, 0, 0 };

    // fill other vertices
    for (int i = 0; i < size; i++) {
        double xy_angle = 2 * M_PI / size * i;
        for (int j = 1; j < size; j++) {
            double z_angle = M_PI / size * j;
            glm::vec3 point(cos(xy_angle) * sin(z_angle), sin(xy_angle) * sin(z_angle), cos(z_angle));
            v.push_back(Vertex(point, point, white));
            // update min/max
            for (int j = 0; j < 3; j++) {
                if (point[j] > ma[j]) ma[j] = point[j];
                if (point[j] < mi[j]) mi[j] = point[j];
            }
        }
    }

    // create triangles
    std::vector<unsigned int> ids;
    /*ids.push_back(0);
    ids.push_back(2);
    ids.push_back(2 + size - 1);*/
    for (int i = 0; i < size; i++) {
        // top triangle
        ids.push_back(0);
        ids.push_back(2 + size - 2 + ((i + 1) % size) * (size - 1));
        ids.push_back(2 + size - 2 + i * (size - 1));
        for (int j = 0; j < size - 2; j++) {
            ids.push_back(2 + i * (size - 1) + j);
            ids.push_back(2 + i * (size - 1) + j + 1);
            ids.push_back(2 + ((i + 1) % size) * (size - 1) + j);

            ids.push_back(2 + i * (size - 1) + j + 1);
            ids.push_back(2 + ((i + 1) % size) * (size - 1) + j + 1);
            ids.push_back(2 + ((i + 1) % size) * (size - 1) + j);
        }
        // top triangle
        ids.push_back(1);
        ids.push_back(2 + i * (size - 1));
        ids.push_back(2 + ((i + 1) % size) * (size - 1));
    }

    std::vector<Texture> t;

    Mesh m = Mesh(v, ids, t);
    m.min_vertex = mi;
    m.max_vertex = ma;
    return m;
}


// EOF