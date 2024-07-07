#ifndef __RT_TRACER_HPP__
#define __RT_TRACER_HPP__

#include "rt_scene.hpp"

struct tracer_ao {
    bool use = false;
    int nb_samples = 64;
};

class RT_Tracer {
public:
    tracer_ao ao;
public:
    RT_Tracer();
    RT_Tracer(const RT_Scene& mesh);
    ~RT_Tracer() {};


};


#endif