/*
 * MaxOfGaussians.cpp
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "MaxOfGaussians.h"

namespace stochastic {

MaxOfGaussians::MaxOfGaussians(Gaussian arg1, Gaussian arg2)
{
	this->arg1 = arg1;
	this->arg2 = arg2;

	double m1 = arg1.getMean();
	double var1 = arg1.getVariance();
	double m2 = arg2.getMean();
	double var2 = arg2.getVariance();
	// heuristic solution, based on min and max intervals
	cache_leftMargin = std::max <double>(m1 - 4 * sqrt(var1), m2 - 4 * sqrt(var2));
	cache_rightMargin = std::max <double>(m1 + 4 * sqrt(var1), m2 + 4 * sqrt(var2));
}

MaxOfGaussians::~MaxOfGaussians()
{
}

const char * MaxOfGaussians::getName()
{
	return "Maximum of Gaussians";
}

double MaxOfGaussians::pdf(double x)
{
	return arg1.pdf(x) * arg2.cdf(x) + arg2.pdf(x) * arg1.cdf(x);
}

double MaxOfGaussians::cdf(double x)
{
	return arg1.cdf(x) * arg2.cdf(x);
}

double MaxOfGaussians::getLeftMargin()
{
	return cache_leftMargin;
}

double MaxOfGaussians::getRightMargin()
{
	return cache_rightMargin;
}

double MaxOfGaussians::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
