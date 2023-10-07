#include "terrain.hpp"

#include "stb_image.h"
#include "stb_image_write.h"


Terrain::Terrain() {
	width = 0;
	height = 0;
}

Terrain::Terrain(int w, int h) : width(w), height(h) {
	heights.resize(w * h, 0.);
}

Terrain::Terrain(std::string file_name) {
	width = 0;
	height = 0;
	
	int w = 0;
	int h = 0;
	int channels = 0;
	unsigned char* img = stbi_load(file_name.c_str(), &w, &h, &channels, 0);

	if (img == nullptr) {
		std::cerr << "Terrain::Terrain(std::string) : Image not found : " << file_name << std::endl;
		return;
	}

	std::cout << w << " " << h << " " << channels << std::endl;

	width = w;
	height = h;
	heights.reserve(width * height);
	for (int i = 0; i < w * h; i++) {
		double h = img[channels * i] / 255.;
		heights.push_back(h);
	}

	stbi_image_free(img);
}


double Terrain::operator()(int i, int j) const {
	return heights[i * height + j];
}

double& Terrain::operator()(int i, int j) {
	return heights[i * height + j];
}


Mesh Terrain::GetMesh() const {

	std::vector<Triangle> triangles;
	triangles.reserve(2 * (width - 1) * (height - 1));

	for (int i = 0; i < width - 1; i++) {
		for (int j = 0; j < height - 1; j++) {

		}
	}

	return Mesh(triangles);
}

// EOF