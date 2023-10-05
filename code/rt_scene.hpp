#ifndef __RT_SCENE_HPP__
#define __RT_SCENE_HPP__

#include "mesh.hpp"
#include "ray.hpp"

class RT_Scene : public Mesh {
public:
    double t_max = 100000.;
public:
    RT_Scene();
    RT_Scene(const Mesh& mesh);
    ~RT_Scene() {};

    bool IntersectionTriangle(int t_id, const Ray& ray) const;
};


#endif