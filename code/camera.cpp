#include "camera.hpp"

Camera::Camera() : center(Point()), direction(Vector()) {

}

Camera::Camera(Point c, Vector d, double f) : center(c), direction(d), fov(f) {

}




//EOF