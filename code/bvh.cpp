#include "bvh.hpp"

#include <algorithm>


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

    // Build
}

BVH::~BVH() {
    delete root_box;
}



Hit BVH::Intersection(const Ray& ray) const {

    return Hit();
}


void BVH::Partition(Box* root) {
    if (root->end_id - root->start_id < 5) return;

    // find largest axis
    // TODO
    int dim = 0;

    Box* box_1 = new Box();
    Box* box_2 = new Box();

    root->box_1 = box_1;
    root->box_2 = box_2;

    int mid_id = (root->start_id + root->end_id) / 2;

    /*std::nth_element(&t_ids[root->start_id], &t_ids[mid_id], &t_ids[root->end_id],
        [dim](const unsigned int& a, const unsigned int& b) { return triangles[a].centroid[dim] < b.centroid[dim]; });
        */

    Partition(box_1);
    Partition(box_2);
}



//EOF