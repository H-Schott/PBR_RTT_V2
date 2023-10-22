#include "sampler.hpp"


Sampler::Sampler(unsigned int s) : seed(s) {
	n = 0;
}


unsigned int Sampler::RandInt() {
	unsigned int random = 0;

	// TODO

	n++;
	return random;
}


// UNIFORM SAMPLER ----------------------------

UniformSampler::UniformSampler(unsigned int s) : Sampler(s) {

}

double UniformSampler::operator()() {
	unsigned int randint = RandInt();
	double random = double(randint) / max_rand_int;

	return random;
}


// GAUSSIAN SAMPLER ----------------------------

GaussianSampler::GaussianSampler(unsigned int s) : Sampler(s) {
	u_sampler = UniformSampler(seed);
}


double GaussianSampler::operator()() {	
	double random = u_sampler();

	return random;
}




//EOF