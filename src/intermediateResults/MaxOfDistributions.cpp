/*
 * MaxOfDistributions.cpp
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "MaxOfDistributions.h"

namespace stochastic {

MaxOfDistributions::MaxOfDistributions(Distribution * arg1, Distribution * arg2)
{
	this->arg1 = arg1;
	this->arg2 = arg2;

	// heuristic solution, based on min and max intervals
	cache_leftMargin = std::max <double>(arg1->getLeftMargin(),
			arg2->getLeftMargin());
	cache_rightMargin = std::max <double>(arg1->getRightMargin(),
			arg2->getRightMargin());
}

MaxOfDistributions::~MaxOfDistributions()
{
}

const char * MaxOfDistributions::getName()
{
	return "Maximum of Distributions";
}

double MaxOfDistributions::pdf(double x)
{
	return arg1->pdf(x) * arg2->cdf(x) + arg2->pdf(x) * arg1->cdf(x);
}

double MaxOfDistributions::cdf(double x)
{
	return arg1->cdf(x) * arg2->cdf(x);
}

double MaxOfDistributions::getLeftMargin()
{
	return cache_leftMargin;
}

double MaxOfDistributions::getRightMargin()
{
	return cache_rightMargin;
}

double MaxOfDistributions::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
