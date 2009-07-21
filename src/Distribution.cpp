/*
 * Distribution.cpp
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Distribution.h"

#include <cmath>
#include <limits>
#include "exceptions.h"

namespace stochastic {

// Static Member: Random Generator
RandomGenerator Distribution::generator;

Distribution::Distribution()
{
}

Distribution::~Distribution()
{
}

/* Compute the inverse CDF of 'p' for the current distribution
 * using Bisection method  */
double Distribution::quantile(double p)
{
	if (p > 1 || p < 0)
	{
		std::string message = "Input out of domain of quantile function";
		throw InvalidParametersException(message);
	}
	if (p < 1e-4)
		return this->getLeftMargin();
	if (p > 1 - 1e-4)
		return this->getRightMargin();

	double a = getLeftMargin();
	double b = getRightMargin();
	double x, difference = std::numeric_limits<double>::infinity();
	int tries = 0;
	do
	{
		x = (a + b) / 2;
		if ((cdf(a) - p) * (cdf(x) - p) >= 0)
			a = x;
		else if ((cdf(b) - p) * (cdf(b) - p) >= 0)
			b = x;
		if (difference > cdf(x) - p)
			difference = cdf(x) - p;
		difference = std::abs(difference);
	} while (difference > 1e-4 && tries++ < 100);
	return x;
}

std::vector<double> Distribution::sample(int numberOfSamples)
{
	int i;
	std::vector<double> samples;
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
