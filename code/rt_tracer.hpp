#ifndef __RT_TRACER_HPP__
#define __RT_TRACER_HPP__

#include "rt_scene.hpp"


struct tracer_diff {
    bool use = true;
};

struct tracer_spec {
    bool use = false;
    double exp = 50.;
};

struct tracer_ao {
    bool use = false;
    int nb_samples = 64;
};

class RT_Tracer {
public:
    tracer_ao ao;
    tracer_diff diff;
    tracer_spec spec;

    const RT_Scene& scene;
public:
    RT_Tracer(const RT_Scene& _scene) : scene(_scene) {};
    ~RT_Tracer() {};

    float Diff();
    float Spec();
    float Ao();

    float Trace(const Ray& ray);
};


#endif