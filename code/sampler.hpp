#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include <vector>

#include "point.hpp"
#include "vector.hpp"

class Sampler {
public:

	unsigned int seed = 0;
	unsigned int n = 0;
	unsigned int max_rand_int = UINT_MAX;

	Sampler(unsigned int s = 0);

	unsigned int RandInt();

	virtual double operator()() = 0;

};


class UniformSampler : public Sampler {
public:

	UniformSampler(unsigned int s = 0);

	virtual double operator()() override;
};


class GaussianSampler : public Sampler {
public:

	UniformSampler u_sampler;

	GaussianSampler(unsigned int s = 0);

	virtual double operator()() override;
};

#endif