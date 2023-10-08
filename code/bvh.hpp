#ifndef __BVH_HPP__
#define __BVH_HPP__

#include "ray.hpp"
#include "rt_scene.hpp"


class Box {
public:
    Point p_min;
    Point p_max;
    
    unsigned int start_id;
    unsigned int end_id;

    Box* box_1;
    Box* box_2;

public:
    Box();
    //Box(const Point& _p_min, const Point& _p_max);
    ~Box();

    bool Intersection(const Ray& ray) const;

};


class BVH{
public:

    Box* root_box;
    std::vector<unsigned int> t_ids;
    const std::vector<Triangle>& triangles;

public:
    BVH(const RT_Scene& mesh);
    ~BVH();

    Hit Intersection(const Ray& ray) const;
};


#endif