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


bool Box::TestBox(const Ray& ray) const {
    Point rmin = p_min;
    Point rmax = p_max;
    if (ray.direction.x < 0) std::swap(rmin.x, rmax.x);
    if (ray.direction.y < 0) std::swap(rmin.y, rmax.y);
    if (ray.direction.z < 0) std::swap(rmin.z, rmax.z);
    Vector invd = Vector(1 / ray.direction.x, 1 / ray.direction.y, 1 / ray.direction.z);
    Vector dmin = (rmin - ray.origin) * invd;
    Vector dmax = (rmax - ray.origin) * invd;

    float tmin = std::max(dmin.z, std::max(dmin.y, std::max(dmin.x, 0.f)));
    float tmax = std::min(dmax.z, std::min(dmax.y, std::min(dmax.x, ray.t)));
    return BBoxHit(tmin, tmax);
}


Hit Box::Intersection(const Ray& ray) const {
    // test intersection with your own box
    // if false return Hit()
    // 
    // if children are nullptr : loop on triangles and return
    // 
    // get recursively Hit1 from child box 1
    // get recursively Hit2 from child box 2
    // get closest intersection Hit
    return Hit();
}



// ------------------------ BVH ------------------------


BVH::BVH(const RT_Scene& scene) : triangles(scene.triangles) {
    root_box = new Box();
    root_box->start_id = 0;
    root_box->end_id = scene.triangles.size() - 1;

    t_ids.reserve(scene.triangles.size());

    for (int i = 0; i < scene.triangles.size(); i++) {
        t_ids.push_back(i);
    }

    // Build centroids
    for (int i = 0; i < scene.triangles.size(); i++) {
        centroids.push_back(triangles[i].Barycentre());
    }

    Partition(root_box);
}

BVH::~BVH() {
    delete root_box;
}



Hit BVH::Intersection(const Ray& ray) const {

    if (!root_box->Intersection(ray))

    return Hit();
}


void BVH::Partition(Box* root) {
    if (root->end_id - root->start_id < 5) return;

    // find your own bounds
    triangles[t_ids[root->start_id]].Bounds(root->p_min, root->p_max);
    for (int i = root->start_id; i < root->end_id + 1; i++) {
        Point temp_min;
        Point temp_max;
        triangles[t_ids[i]].Bounds(temp_min, temp_max);
        root->p_min = Min(root->p_min, temp_min);
        root->p_max = Max(root->p_max, temp_max);
    }

    // find largest axis
    int dim = MaxDimension(root->p_max - root->p_min);

    Box* box_1 = new Box();
    Box* box_2 = new Box();

    root->box_1 = box_1;
    root->box_2 = box_2;

    int mid_id = (root->start_id + root->end_id) / 2;

    std::nth_element(&t_ids[root->start_id], &t_ids[mid_id], &t_ids[root->end_id],
        [&](const unsigned int& a, const unsigned int& b) { return centroids[a][dim] < centroids[b][dim]; });
        
    root->box_1->start_id = root->start_id;
    root->box_1->end_id = mid_id;
    root->box_1->start_id = mid_id + 1;
    root->box_1->end_id = root->end_id;

    Partition(box_1);
    Partition(box_2);
}



//EOF