#include "sampler.hpp"


Sampler::Sampler(unsigned int s) : seed(s), last(s) {

}


unsigned int Sampler::RandInt() {
	// + 1 to avoid zero
	unsigned int random = (clg_a * last + clg_c) % clg_max + 1;
	last = random;

	return random;
}


// UNIFORM SAMPLER ----------------------------

UniformSampler::UniformSampler(unsigned int s) : Sampler(s) {

}

double UniformSampler::operator()() {
	unsigned int randint = RandInt();
	double random = double(randint) / (clg_max + 1);

	return random;
}


// NORMAL SAMPLER ----------------------------

NormalSampler::NormalSampler(unsigned int s) : Sampler(s) {
	u_sampler = UniformSampler(seed);
}


double NormalSampler::operator()() {	
	double r1 = u_sampler();
	double r2 = u_sampler();
	double random = std::sqrt(-2 * std::log(r1)) * std::cos(2 * M_PI * r2);
	
	return random;
}




//EOF