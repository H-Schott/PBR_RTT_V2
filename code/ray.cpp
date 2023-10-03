#include "ray.hpp"

Ray::Ray() : origin(Point()), direction(Vector()) {

}

Ray::Ray(Point o, Vector d) : origin(o), direction(d) {

}

Point Ray::operator()(double t) const {
    return origin + t * direction;
}



//EOF