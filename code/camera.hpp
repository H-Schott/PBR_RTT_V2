#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "point.hpp"
#include "vector.hpp"

class Camera {
public:

	Point center;
    Vector direction;

	double fov = 90.;

	Camera();
	Camera(Point c, Vector d, double fov);
};

#endif