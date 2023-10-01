#include "image.hpp"

Image::Image() {
	width = 0;
	height = 0;
}

Image::Image(int w, int h) : width(w), height(h) {
	pixels.resize(w * h);
}

Image::Image(int w, int h, Color c) : width(w), height(h) {
	pixels.reserve(w * h);
	for (int i = 0; i < w * h; i++) {
		pixels.push_back(c);
	}
}

Image::Image(int w, int h, const std::vector<Color>& c) : width(w), height(h) {
	pixels.reserve(w * h);

	if (c.size() != w * h) {
		std::cerr << "Image::Image(int, int, const std::vector<Color>&) : Color vector has wrong size." << std::endl;
		width = 0;
		height = 0;
		return;
	}

	pixels = c;
}

Image::Image(std::string file_name) {
	width = 0;
	height = 0;
	// TODO
}


// EOF