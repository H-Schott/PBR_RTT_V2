#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <vector>
#include <iostream>

#include "color.hpp"

class Image {
public:

	int width;
	int height;

	std::vector<Color> pixels;

	Image();
	Image(int w, int h);
	Image(int w, int h, Color c);
	Image(int w, int h, const std::vector<Color>& c);
	Image(std::string file_name);
};

#endif