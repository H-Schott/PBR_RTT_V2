#include "mesh.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Mesh::Mesh(const std::vector<Point>& points,
           const std::vector<unsigned int>& indices,
           const std::vector<Texture>& _textures) : textures(_textures) {
    
    int nb_triangles = indices.size() / 3;
    triangles.reserve(nb_triangles);

    for (int i = 0; i < nb_triangles; i++) {
        Point A = points[indices[3 * i]];
        Point B = points[indices[3 * i + 1]];
        Point C = points[indices[3 * i + 2]];

        triangles.push_back(Triangle(A, B, C));
    }
    
    std::cout << "Built a mesh with " << nb_triangles << " triangles." << std::endl;
}


Mesh::Mesh(const std::vector<Triangle>& t) : triangles(t) {
    normals.reserve(triangles.size() * 3);
    for (int i = 0; i < triangles.size(); i++) {
        normals.push_back(triangles[i].Normal());
        normals.push_back(triangles[i].Normal());
        normals.push_back(triangles[i].Normal());
    }
    // TODO update bounds
}

Mesh::Mesh(const std::vector<Triangle>& t, const std::vector<Vector>& n) : triangles(t), normals(n) {
    // TODO update bounds
}


Mesh::Mesh(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    AddAiNode(scene->mRootNode, scene);

    std::cout << "Built a mesh with " << triangles.size() << " triangles." << std::endl;
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
    std::vector<Point> points;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Point p;
        p.x = mesh->mVertices[i].x;
        p.y = mesh->mVertices[i].y;
        p.z = mesh->mVertices[i].z;
        // update min/max
        for (int j = 0; j < 3; j++) {
            if (p[j] > max_vertex[j]) max_vertex[j] = p[j];
            if (p[j] < min_vertex[j]) min_vertex[j] = p[j];
        }
        
        points.push_back(p);
        
        // Vector n;
        // n.x = mesh->mNormals[i].x;
        // n.y = mesh->mNormals[i].y;
        // n.z = mesh->mNormals[i].z;
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        triangles.push_back(Triangle(points[face.mIndices[0]],
                                     points[face.mIndices[1]],
                                     points[face.mIndices[2]]));
    }
}


void Mesh::Center() {
    Point centre = (max_vertex + min_vertex);
    centre *= 0.5;
    int nb_triangles = triangles.size();
    for (int i = 0; i < nb_triangles; i++) {
        triangles[i].a -= centre;
        triangles[i].b -= centre;
        triangles[i].c -= centre;
    }

    min_vertex -= centre;
    max_vertex -= centre;
}


void Mesh::Scale(double coeff) {
    int nb_triangles = triangles.size();
    for (int i = 0; i < nb_triangles; i++) {
        triangles[i].a *= coeff;
        triangles[i].b *= coeff;
        triangles[i].c *= coeff;
    }

    min_vertex *= coeff;
    max_vertex *= coeff;
}


Mesh Mesh::Sphere(int size) {

    Point white = Point(1, 1, 1);
    std::vector<Point> pts;

    // top and bottom vertices
    pts.push_back(Point(0., 0., -1));
    pts.push_back(Point(0., 0., 1));

    // min / max vertices
    Point mi{ 0, 0, 0 };
    Point ma{ 0, 0, 0 };

    // fill other vertices
    for (int i = 0; i < size; i++) {
        double xy_angle = 2 * M_PI / size * i;
        for (int j = 1; j < size; j++) {
            double z_angle = M_PI / size * j;
            Point point(cos(xy_angle) * sin(z_angle), sin(xy_angle) * sin(z_angle), cos(z_angle));
            pts.push_back(point);
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

    Mesh m = Mesh(pts, ids, t);
    m.min_vertex = mi;
    m.max_vertex = ma;
    return m;
}


// EOF