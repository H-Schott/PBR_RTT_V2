#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <vector>

#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"

class Camera {
public:

	Point center;
    Vector direction;

	double size = 5.;

	Camera();
	Camera(Point c, Vector d, double s);

	std::vector<Ray> GetRays(int width, int height) const;
};

#endif