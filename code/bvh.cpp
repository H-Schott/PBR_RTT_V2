#include "bvh.hpp"


Box::Box() {
    p_min = Point();
    p_max = Point();

    start_id = 0;
    end_id = 0;

    box_1 = nullptr;
    box_2 = nullptr;
}


Box::~Box() {
    delete box_1;
    delete box_2;
}


bool Box::Intersection(const Ray& ray) const {
    return true;
}



// ------------------------ BVH ------------------------


BVH::BVH(const RT_Scene& scene) : triangles(scene.triangles) {
    root_box = nullptr;

    t_ids.reserve(scene.triangles.size());

    for (int i = 0; i < scene.triangles.size(); i++) {
        t_ids.push_back(i);
    }
}

BVH::~BVH() {
    delete root_box;
}



Hit BVH::Intersection(const Ray& ray) const {

    return Hit();
}



//EOF