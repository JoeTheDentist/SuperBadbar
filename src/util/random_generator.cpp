/**
 * 	@file random_generator.cpp
 * 	@brief Implementation de la classe Random_generator
 *
 * 	@author Guillaume Bérard & Benoit Morel
 * 	@date mai 2011
 *
 */

#include "random_generator.h"

#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

#define DEUX_PI ( 2.0 * 3.141592653589793238462643383279502884197169399375 )

void Random_generator::init() 
{
	srand(time(NULL));
}

int Random_generator::irand(int min, int max)
{
	if (min < 0) {
		return irand(0, max - min) + min;
	}
	return (rand() % (max + min + 1)) + min;
}

float Random_generator::frand(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

double Random_generator::drand(double min, double max)
{
	return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

double Random_generator::rnorm(double mu, double sigma) 
{
	// code taken from wikipedia
	double randNumUni = ((double) rand())/((double) RAND_MAX);
	double randNumBi = ((double) rand())/((double) RAND_MAX);
	double randNumNorm = sqrt(-2.0*log(randNumUni))*cos(DEUX_PI*randNumBi);
	return (mu + sigma * randNumNorm);
}
