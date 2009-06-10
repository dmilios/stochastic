/*
 * Distribution.cpp
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Distribution.h"

#include <ctime> //for time()
#include <cstdlib> // for rand(), srand()

namespace stochastic {


// ---------------------------------------------------------
// Static Members
//
int Distribution::seedInitialized = 0;

double Distribution::nextUniform_0_1()
{
	if (!seedInitialized)
	{
		srand(time(0));
		seedInitialized = 1;
	}
	return (double)rand() / (double)RAND_MAX;
}
// ---------------------------------------------------------


Distribution::Distribution()
{
}

Distribution::~Distribution()
{
}

std::vector <double> Distribution::sample(int numberOfSamples)
{
	int i;
	std::vector <double> samples;
	for (i = 0; i < numberOfSamples; i++)
		samples.push_back(nextSample());
	return samples;
}

} // namespace stochastic
