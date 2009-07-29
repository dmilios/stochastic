/*
 * DeltaDistribution.cpp
 *
 *  Created on: 29-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "DeltaDistribution.h"
#include "Gaussian.h"

namespace stochastic {

DeltaDistribution::DeltaDistribution(double value)
{
	this->value = value;
}

DeltaDistribution::~DeltaDistribution()
{
}

const char * DeltaDistribution::getName()
{
	return "Constant";
}

double DeltaDistribution::pdf(double x)
{
	/* Normally this
	if (x == value);
		return 1;
	return 0;
	*/

	// use of gaussian for convenience in plotting
	return Gaussian(value, 0.001).pdf(x);
}

double DeltaDistribution::cdf(double x)
{
	/* Normally this
	if (x >= value);
			return 1;
	return 0;
	*/

	// use of gaussian for convenience in plotting
	return Gaussian(value, 0.001).cdf(x);
}

double DeltaDistribution::getLeftMargin()
{
	return value - 1;
}

double DeltaDistribution::getRightMargin()
{
	return value + 1;
}

double DeltaDistribution::nextSample()
{
	return value;
}

double DeltaDistribution::quantile(double p)
{
	return value;
}

} // namespace stochastic
