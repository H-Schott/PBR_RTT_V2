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

	std::vector<double> heights;

	Terrain();
	Terrain(int w, int h);
	Terrain(std::string file_name);

	double operator()(int i, int j) const;
	double& operator()(int i, int j);

	Mesh GetMesh() const;
};

#endif