#ifndef __HIT_HPP__
#define __HIT_HPP__

#include "point.hpp"
#include "vector.hpp"

class Hit {
public:

	double t;
    int triangle_id;
    Vector bary;

	Hit();
	Hit(double _t, int triangle_id, Vector d);

    operator bool() const;

};

inline std::ostream& operator<<(std::ostream& os, const Hit hit) {
    os << "Hit(" << hit.t << ", " << hit.triangle_id << ", " << hit.bary << ")";
    return os;
}

#endif