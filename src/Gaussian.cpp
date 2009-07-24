/*
 * Gaussian.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Gaussian.h"

#include "exceptions.h"
#include <typeinfo>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

namespace stochastic {

Gaussian::Gaussian()
{
	mean = 0;
	variance = 1;

	cache_varX2 = variance * 2;
	cache_one_over_sqrt_var2PI = 1 / sqrt(PI * cache_varX2);
	cache_leftMargin = mean - 4 * sqrt(variance);
	cache_rightMargin = mean + 4 * sqrt(variance);
}

Gaussian::Gaussian(double mean)
{
	this->mean = mean;
	variance = 1;

	cache_varX2 = variance * 2;
	cache_one_over_sqrt_var2PI = 1 / sqrt(PI * cache_varX2);
	cache_leftMargin = mean - 4 * sqrt(variance);
	cache_rightMargin = mean + 4 * sqrt(variance);
}

Gaussian::Gaussian(double mean, double variance)
{
	if (variance <= 0)
	{
		std::stringstream var_s;
		var_s << variance;
		std::string message = "variance = ";
		message.append(var_s.str());
		message.append(" : variance <= 0 in a Gaussian");
		throw InvalidParametersException(message);
	}

	this->mean = mean;
	this->variance = variance;

	cache_varX2 = variance * 2;
	cache_one_over_sqrt_var2PI = 1 / sqrt(PI * cache_varX2);
	cache_leftMargin = mean - 4 * sqrt(variance);
	cache_rightMargin = mean + 4 * sqrt(variance);
}

Gaussian::~Gaussian()
{
}

double Gaussian::getMean()
{
	return mean;
}

double Gaussian::getVariance()
{
	return variance;
}

const char * Gaussian::getName()
{
	std::stringstream mean_s;
	std::stringstream var_s;
	mean_s << this->mean;
	var_s << this->variance;

	std::string name("N(");
	name.append(mean_s.str());
	name.append(",");
	name.append(var_s.str());
	name.append(")");
	return name.c_str();
}

double Gaussian::pdf(double x)
{
	if (x < cache_leftMargin)
		return 0;
	if (x > cache_rightMargin)
		return 0;

	double x_mean = x - mean;
	return cache_one_over_sqrt_var2PI * exp(-x_mean * x_mean
			/ cache_varX2);
}

double Gaussian::cdf(double x)
{
	if (x <= cache_leftMargin)
		return 0;
	if (x >= cache_rightMargin)
		return 1;

	return 0.5 * (1 + erf((x - mean) / sqrt(2 * variance)));
}

double Gaussian::getLeftMargin()
{
	return cache_leftMargin;
}

double Gaussian::getRightMargin()
{
	return cache_rightMargin;
}

double Gaussian::nextSample()
{
	return rejectionSampling(pdf(mean), getLeftMargin(), getRightMargin());
}

} // namespace stochastic
