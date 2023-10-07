#include "camera.hpp"

Camera::Camera() : center(Point()), direction(Vector()) {

}

Camera::Camera(Point c, Vector d, double s) : center(c), direction(d), size(s) {

}


std::vector<Ray> Camera::GetRays(int width, int height) const {
	std::vector<Ray> rays;
	rays.reserve(width * height);

	Vector local_x = Cross(direction, Vector::Z());
	Vector local_y = Cross(local_x, direction);

	double size_x = size;
	double size_y = size * height / width;

	Point top_left = center + (size_x / 2 - 0.5 * size_x / width) * local_x + (size_y / 2 - 0.5 * size_y / height) * local_y;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = size_x / width * i;
			double y = size_y / height * j;
			Point origin = top_left - x * local_x - y * local_y;
			rays.push_back(Ray(origin, direction));
		}
	}

	return rays;
}




//EOF