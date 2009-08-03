/*
 * InverseRV_Distribution.cpp
 *
 *  Created on: 03-Aug-2009
 *      Author: Dimitrios Milios
 */

#include "InverseRV_Distribution.h"
#include <string>
#include <algorithm>

namespace stochastic {

InverseRV_Distribution::InverseRV_Distribution(Distribution * original)
{
	this->original = original;
	if (original->getLeftMargin() * original->getRightMargin() <= 0)
	{
		cache_leftMargin = original->getLeftMargin() / 0.1;
		cache_rightMargin = original->getRightMargin() / 0.1;
	}
	else
	{
		double lm = original->getLeftMargin();
		double rm = original->getRightMargin();
		// use of minmax to cover both negative and positive margins case
		cache_leftMargin = std::min<double>(1 / lm,	1 / rm);
		cache_rightMargin = std::max<double>(1 / lm, 1 / rm);
	}
}

InverseRV_Distribution::~InverseRV_Distribution()
{
}

const char * InverseRV_Distribution::getName()
{
	std::string name = "\"1/X\" : ";
	name.append(original->getName());
	return name.c_str();
}

double InverseRV_Distribution::pdf(double x)
{
	if (x < cache_leftMargin)
		return 0;
	if (x > cache_rightMargin)
		return 0;
	if (!x)
		return 0;

	return (1 / (x * x)) * original->pdf(1 / x);
}

double InverseRV_Distribution::cdf(double x)
{
	if (x < cache_leftMargin)
		return 0;
	if (x > cache_rightMargin)
		return 1;
	if (!x)
		return this->cdf(x - 0.00001);

	if (x > 0)
		return 1 - original->cdf(1 / x) + original->cdf(0);
	else
		return - original->cdf(1 / x) + original->cdf(0);
}

double InverseRV_Distribution::getLeftMargin()
{
	return cache_leftMargin;
}

double InverseRV_Distribution::getRightMargin()
{
	return cache_rightMargin;
}

double InverseRV_Distribution::nextSample()
{
	return quantile(generator.nextDouble());
}

} // end stochastic
