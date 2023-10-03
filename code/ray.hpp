#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "point.hpp"
#include "vector.hpp"

class Ray {
public:

	Point origin;
    Vector direction;

	Ray();
	Ray(Point o, Vector d);

    Point operator()(double t) const;
};

#endif