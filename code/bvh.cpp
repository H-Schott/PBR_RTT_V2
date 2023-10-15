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
    if (box_1 != nullptr) delete box_1;
    if (box_2 != nullptr) delete box_2;
}


bool Box::TestBox(const Ray& ray) const {
    float tmin = (p_min.x - ray.origin.x) / ray.direction.x;
    float tmax = (p_max.x - ray.origin.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (p_min.y - ray.origin.y) / ray.direction.y;
    float tymax = (p_max.y - ray.origin.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (p_min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (p_max.z - ray.origin.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}



// ------------------------ BVH ------------------------


BVH::BVH(const RT_Scene& scene) : RT_Scene(scene) {
    root_box = new Box();
    root_box->start_id = 0;
    root_box->end_id = triangles.size() - 1;

    t_ids.reserve(triangles.size());

    for (int i = 0; i < triangles.size(); i++) {
        t_ids.push_back(i);
    }

    // Build centroids
    for (int i = 0; i < triangles.size(); i++) {
        centroids.push_back(triangles[i].Barycentre());
    }

    Partition(root_box);
}

BVH::~BVH() {
    delete root_box;
}


Hit BVH::Intersection(Box* box, const Ray& ray) const {
    // test intersection with your own box
    // if false return Hit()
    if (!box->TestBox(ray)) return Hit();

    // if children are nullptr : loop on triangles and return
    if (box->box_1 == nullptr) {
        Hit real_hit = Hit(ray.t_max, -1, Vector());
        for (int i = box->start_id; i <= box->end_id; i++) {
            Hit temp_hit = IntersectionTriangle(t_ids[i], ray);
            if (temp_hit && temp_hit.t < real_hit.t) real_hit = temp_hit;
        }
        return real_hit;
    }

    // get recursively Hit1 from child box 1
    Hit hit1 = Intersection(box->box_1, ray);
    // get recursively Hit2 from child box 2
    Hit hit2 = Intersection(box->box_2, ray);

    // get closest intersection Hit
    if (!hit2) return hit1;
    else if (!hit1) return hit2;
    else if (hit1.t <= hit2.t) return hit1;
    return hit2;
}


Hit BVH::Intersection(const Ray& ray) const {
    return Intersection(root_box, ray);
}


void BVH::Partition(Box* root) {

    // find your own bounds
    triangles[t_ids[root->start_id]].Bounds(root->p_min, root->p_max);
    for (int i = root->start_id; i < root->end_id + 1; i++) {
        Point temp_min;
        Point temp_max;
        triangles[t_ids[i]].Bounds(temp_min, temp_max);
        root->p_min = Min(root->p_min, temp_min);
        root->p_max = Max(root->p_max, temp_max);
    }

    if (root->end_id - root->start_id < 5) return;

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
    root->box_2->start_id = mid_id + 1;
    root->box_2->end_id = root->end_id;

    Partition(box_1);
    Partition(box_2);
}



//EOF