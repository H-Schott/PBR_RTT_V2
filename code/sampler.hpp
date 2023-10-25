#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include <vector>

#include "point.hpp"
#include "vector.hpp"

class Sampler {
public:

	unsigned int seed = 0;
	unsigned int last = 0;

	// congruential linear generator
	// X(n+1) = (aX(n) + c) mod m
	unsigned int clg_a = 1103515245;
	unsigned int clg_c = 12345;
	unsigned int clg_max = 1 << 31;

	Sampler(unsigned int s = 0);

	unsigned int RandInt();

	virtual double operator()() = 0;

};


class UniformSampler : public Sampler {
public:

	UniformSampler(unsigned int s = 0);

	virtual double operator()() override;
};


class NormalSampler : public Sampler {
public:

	UniformSampler u_sampler;

	NormalSampler(unsigned int s = 0);

	virtual double operator()() override;
};

#endif