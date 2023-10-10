#ifndef __RT_SCENE_HPP__
#define __RT_SCENE_HPP__

#include "hit.hpp"
#include "mesh.hpp"
#include "ray.hpp"

class RT_Scene : public Mesh {
public:

public:
    RT_Scene();
    RT_Scene(const Mesh& mesh);
    RT_Scene(const std::string& file_name);
    ~RT_Scene() {};

    Hit IntersectionTriangle(int t_id, const Ray& ray) const;
    virtual Hit Intersection(const Ray& ray) const;
};


#endif