/*
 * MinOfGaussians.cpp
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "MinOfGaussians.h"

#include <algorithm>
#include <cmath>

namespace stochastic {

MinOfGaussians::MinOfGaussians(Gaussian arg1, Gaussian arg2)
{
	this->arg1 = arg1;
	this->arg2 = arg2;

	double m1 = arg1.getMean();
	double var1 = arg1.getVariance();
	double m2 = arg2.getMean();
	double var2 = arg2.getVariance();
	// heuristic solution, based on min and max intervals
	cache_leftMargin = std::min <double>(m1 - 4 * sqrt(var1), m2 - 4 * sqrt(var2));
	cache_rightMargin = std::min <double>(m1 + 4 * sqrt(var1), m2 + 4 * sqrt(var2));
}

MinOfGaussians::~MinOfGaussians()
{
}

const char * MinOfGaussians::getName()
{
	return "Minimum of Gaussians";
}

double MinOfGaussians::pdf(double x)
{
	return arg1.pdf(x) * (1 - arg2.cdf(x)) + arg2.pdf(x) * (1 - arg1.cdf(x));
}

double MinOfGaussians::cdf(double x)
{
	return arg1.cdf(x) + arg2.cdf(x) - arg1.cdf(x) * arg2.cdf(x);
}

double MinOfGaussians::getLeftMargin()
{
	return cache_leftMargin;
}

double MinOfGaussians::getRightMargin()
{
	return cache_rightMargin;
}

double MinOfGaussians::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
