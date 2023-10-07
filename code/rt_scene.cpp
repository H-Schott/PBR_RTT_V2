#include "rt_scene.hpp"


RT_Scene::RT_Scene() : Mesh() {

}

RT_Scene::RT_Scene(const Mesh& mesh) : Mesh(mesh) {

}

RT_Scene::RT_Scene(const std::string& file_name) : Mesh(file_name) {

}


bool RT_Scene::IntersectionTriangle(int t_id, const Ray& ray) const {

    Triangle tri = triangles[t_id];
    Vector e1 = tri.Edge(0);
    Vector e2 = -tri.Edge(2);
    Vector a = Vector(tri.a);

    Vector pvec = Cross(ray.direction, e2);
    float det = Dot(e1, pvec);
    float inv_det = 1.f / det;
    Vector tvec = ray.origin - a;
    
    float u = Dot(tvec, pvec) * inv_det;
    if(u < 0 || u > 1) return false;
    
    Vector qvec = Cross(tvec, e1);
    float v = Dot(ray.direction, qvec) * inv_det;
    if(v < 0 || u + v > 1) return false;

    float t= Dot(e2, qvec) * inv_det;
    if(t < 0 || t > t_max) return false;

    // return Hit(t, u, v, id);
    return true;
}

bool RT_Scene::Intersection(const Ray& ray) const {
    for (int i = 0; i < triangles.size(); i++) {
        if (IntersectionTriangle(i, ray)) return true;
    }
    return false;
}



//EOF