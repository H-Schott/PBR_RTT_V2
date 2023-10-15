#include "image.hpp"

#include "stb_image.h"
#include "stb_image_write.h"


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

Image::Image(std::string file_name, bool bit16) {
	width = 0;
	height = 0;
	
	int w = 0;
	int h = 0;
	int channels = 0;

	if (bit16) {
		unsigned short* img = stbi_load_16(file_name.c_str(), &w, &h, &channels, 0);

		if (img == nullptr) {
			std::cerr << "Image::Image(std::string) : Image not found : " << file_name << std::endl;
			return;
		}

		std::cout << w << " " << h << " " << channels << std::endl;

		width = w;
		height = h;
		pixels.reserve(width * height);
		for (int i = 0; i < w * h; i++) {
			Color color;
			if (channels == 1) color = Color(img[channels * i]);
			else color = Color(img[channels * i], img[channels * i + 1], img[channels * i + 2]);
			pixels.push_back(color);
		}

		stbi_image_free(img);
	}
	else {
		unsigned char* img = stbi_load(file_name.c_str(), &w, &h, &channels, 0);

		if (img == nullptr) {
			std::cerr << "Image::Image(std::string) : Image not found : " << file_name << std::endl;
			return;
		}

		std::cout << w << " " << h << " " << channels << std::endl;

		width = w;
		height = h;
		pixels.reserve(width * height);
		for (int i = 0; i < w * h; i++) {
			Color color;
			if (channels == 1) color = Color(img[channels * i]);
			else color = Color(img[channels * i], img[channels * i + 1], img[channels * i + 2]);
			pixels.push_back(color);
		}

		stbi_image_free(img);
	}
	

}


void Image::Save(std::string file_name) const {
	unsigned char* img = new unsigned char[width * height * 3];

	for (int i = 0; i < width * height; i++) {
		img[3 * i] = pixels[i].r;
		img[3 * i + 1] = pixels[i].g;
		img[3 * i + 2] = pixels[i].b;
	}

	stbi_write_png(file_name.c_str(), width, height, 3, img, width * 3);

	delete[] img;
}

Image Image::GetGrayVersion() const {

	Image img(width, height);

	for (int i = 0; i < width * height; i++) {
		img.pixels[i] = pixels[i].ToGray();
	}

	return img;
}


// EOF