#include "rt_scene.hpp"


RT_Scene::RT_Scene() : Mesh() {

}

RT_Scene::RT_Scene(const Mesh& mesh) : Mesh(mesh) {

}

RT_Scene::RT_Scene(const std::string& file_name) : Mesh(file_name) {

}


Hit RT_Scene::IntersectionTriangle(int t_id, const Ray& ray) const {

    Triangle tri = triangles[t_id];
    Vector e1 = tri.Edge(0);
    Vector e2 = -tri.Edge(2);
    Vector a = Vector(tri.a);

    Vector pvec = Cross(ray.direction, e2);
    float det = Dot(e1, pvec);
    float inv_det = 1.f / det;
    Vector tvec = ray.origin - a;
    
    float u = Dot(tvec, pvec) * inv_det;
    if(u < 0 || u > 1) return Hit();
    
    Vector qvec = Cross(tvec, e1);
    float v = Dot(ray.direction, qvec) * inv_det;
    if(v < 0 || u + v > 1) return Hit();

    float t = Dot(e2, qvec) * inv_det;
    if(t < 0 || t > t_max) return Hit();

    return Hit(t, t_id, Vector(u, v, 1 - u - v));
}

Hit RT_Scene::Intersection(const Ray& ray) const {

    Hit real_hit = Hit(t_max, -1, Vector());

    for (int i = 0; i < triangles.size(); i++) {
        Hit temp_hit = IntersectionTriangle(i, ray);
        if (temp_hit && temp_hit.t < real_hit.t) real_hit = temp_hit;
    }

    return real_hit;
}



//EOF