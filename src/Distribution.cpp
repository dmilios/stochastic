/*
 * Distribution.cpp
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Distribution.h"

#include <cmath>

namespace stochastic {

// Static Member: Random Generator
RandomGenerator Distribution::generator;

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

/**
 * @brief Protected member, implements rejection sampling
 * Arguments are used to define an envelope uniform distribution
 * Returns a sample of the wanted distribution,
 * according to its defined 'pdf()' method
 */
double Distribution::rejectionSampling(double highestProbability,
		double leftMargin, double rightMargin)
{
	double proposedSample;
	double uniformSample_0_1;
	double px;
	double proposalUniform = 1 / (rightMargin - leftMargin);
	double k = 1;
	if (proposalUniform < highestProbability)
		k = ceil(highestProbability / proposalUniform);
	do
	{
		proposedSample = generator.nextDouble(leftMargin, rightMargin);
		uniformSample_0_1 = generator.nextDouble();
		px = this->pdf(proposedSample);
	} while (uniformSample_0_1 >= px / (k * proposalUniform));
	return proposedSample;
}

} // namespace stochastic
