/*
 * MinOfDistributions.cpp
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "MinOfDistributions.h"

#include <algorithm>
#include <cmath>

namespace stochastic {

MinOfDistributions::MinOfDistributions(Distribution * arg1, Distribution * arg2)
{
	this->arg1 = arg1;
	this->arg2 = arg2;

	// heuristic solution, based on min and max intervals
	cache_leftMargin = std::min <double>(arg1->getLeftMargin(),
			arg2->getLeftMargin());
	cache_rightMargin = std::min <double>(arg1->getRightMargin(),
			arg2->getRightMargin());
}

MinOfDistributions::~MinOfDistributions()
{
}

const char * MinOfDistributions::getName()
{
	return "Minimum of Distributions";
}

double MinOfDistributions::pdf(double x)
{
	return arg1->pdf(x) * (1 - arg2->cdf(x)) + arg2->pdf(x) * (1 - arg1->cdf(x));
}

double MinOfDistributions::cdf(double x)
{
	return arg1->cdf(x) + arg2->cdf(x) - arg1->cdf(x) * arg2->cdf(x);
}

double MinOfDistributions::getLeftMargin()
{
	return cache_leftMargin;
}

double MinOfDistributions::getRightMargin()
{
	return cache_rightMargin;
}

double MinOfDistributions::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
