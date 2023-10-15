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

    bool TestBox(const Ray& ray) const;
    //Box* Find(const Ray& ray) const;

};


class BVH : public RT_Scene {
public:

    Box* root_box;
    std::vector<unsigned int> t_ids;
    std::vector<Point> centroids;
    //const std::vector<Triangle>& triangles;

public:
    BVH(const RT_Scene& mesh);
    ~BVH();

    Hit Intersection(Box* box, const Ray& ray) const;
    Hit Intersection(const Ray& ray) const override;

private:
    void Partition(Box* root);
};

inline std::ostream& operator<<(std::ostream& os, const Box* box) {
    if (box == nullptr) {
        std::cout << "NULLPTR" << std::endl;
        return os;
    }

    os << "Box(" << box->p_min << ", " << box->p_max << ", " << box->start_id << ", " << box->end_id << ")" << std::endl;
    os << box->box_1;
    os << box->box_2;
    return os;
}


#endif