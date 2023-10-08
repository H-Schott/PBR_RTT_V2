#ifndef __TERRAIN_HPP__
#define __TERRAIN_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "image.hpp"
#include "mesh.hpp"



class Terrain {
public:

	int width;
	int height;

	double cell_size;

	std::vector<double> heights;

	Terrain();
	Terrain(int w, int h);
	Terrain(std::string file_name);

	void Scale(double a);

	double operator()(int i, int j) const;
	double& operator()(int i, int j);
	Point GetPoint(int i, int j) const;

	Mesh GetMesh() const;
};

#endif