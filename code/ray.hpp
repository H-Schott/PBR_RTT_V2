#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "point.hpp"
#include "vector.hpp"

class Ray {
public:

	Point origin;
    Vector direction;

    double t_max = 100000.;

	Ray();
	Ray(Point o, Vector d);

    Point operator()(double t) const;
};

inline std::ostream& operator<<(std::ostream& os, const Ray ray) {
    os << "Ray(" << ray.origin << ", " << ray.direction << ")";
    return os;
}

#endif