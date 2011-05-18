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

void Random_generator::init() 
{
	srand(time(NULL));
}

float Random_generator::frand(float min, float max)
{
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

int Random_generator::irand(int min, int max)
{
	return (rand() % (max + min + 1)) + min;
}
