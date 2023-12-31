#include "terrain.hpp"

#include "stb_image.h"
#include "stb_image_write.h"


Terrain::Terrain() {
	width = 0;
	height = 0;
	cell_size = 0.;
}

Terrain::Terrain(int w, int h) : width(w), height(h) {

	cell_size = 2. / std::max(width, height);

	heights.resize(w * h, 0.);
}

Terrain::Terrain(std::string file_name) {
	width = 0;
	height = 0;
	cell_size = 0;
	
	int w = 0;
	int h = 0;
	int channels = 0;
	unsigned short* img = stbi_load_16(file_name.c_str(), &w, &h, &channels, 0);

	if (img == nullptr) {
		std::cerr << "Terrain::Terrain(std::string) : Image not found : " << file_name << std::endl;
		return;
	}

	std::cout << w << " " << h << " " << channels << std::endl;

	width = w;
	height = h;
	heights.reserve(width * height);
	for (int i = 0; i < w * h; i++) {
		double h = img[channels * i] / double(USHRT_MAX);
		heights.push_back(h);
	}

	cell_size = 2. / std::max(width, height);

	stbi_image_free(img);
}


void Terrain::Scale(double a) {
	for (int i = 0; i < heights.size(); i++) {
		heights[i] *= a;
	}
}


double Terrain::operator()(int i, int j) const {
	return heights[i * height + j];
}

double& Terrain::operator()(int i, int j) {
	return heights[i * height + j];
}

Point Terrain::GetPoint(int i, int j) const {
	// stay inside
	i = std::max(0, i);
	i = std::min(width - 1, i);
	j = std::max(0, j);
	j = std::min(height - 1, j);

	return Point(-1., -1., 0.) + Point(i * cell_size, j * cell_size, (*this)(i, j));
}


Vector Terrain::GetNormal(int i, int j) const {
	Vector x_comp = GetPoint(i + 1, j) - GetPoint(i - 1, j);
	Vector y_comp = GetPoint(i, j + 1) - GetPoint(i, j - 1);
	Vector normal = Cross(x_comp, y_comp);
	return Normalize(normal);
}


Mesh Terrain::GetMesh() const {

	std::vector<Triangle> triangles;
	triangles.reserve(2 * (width - 1) * (height - 1));
	std::vector<Vector> normals;
	normals.reserve(3 * 2 * (width - 1) * (height - 1));

	for (int i = 0; i < width - 1; i++) {
		for (int j = 0; j < height - 1; j++) {
			Point a = GetPoint(i, j);
			Point b = GetPoint(i + 1, j);
			Point c = GetPoint(i, j + 1);
			Point d = GetPoint(i + 1, j + 1);
			// triangle 1
			triangles.push_back(Triangle(a, b, c));
			normals.push_back(GetNormal(i, j));
			normals.push_back(GetNormal(i + 1, j));
			normals.push_back(GetNormal(i, j + 1));
			// triangle 2
			triangles.push_back(Triangle(b, d, c));
			normals.push_back(GetNormal(i + 1, j));
			normals.push_back(GetNormal(i + 1, j + 1));
			normals.push_back(GetNormal(i, j + 1));
		}
	}

	return Mesh(triangles, normals);
}

// EOF