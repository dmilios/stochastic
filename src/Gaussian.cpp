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

const double Gaussian::pi = 3.14159265;

Gaussian::Gaussian()
{
	mean = 0;
	variance = 1;
}

Gaussian::Gaussian(double mean)
{
	this->mean = mean;
	variance = 1;
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
	return (1 / sqrt(2 * pi * variance) * exp(-pow(x - mean, 2)
			/ (2 * variance)));
}

double Gaussian::cdf(double x)
{
	return 0.5 * (1 + erf((x - mean) / sqrt(2 * variance)));

	//NOTE: Abromowitz and Stegun approximation for Gaussian CDF
	const double b1 =  0.319381530;
	const double b2 = -0.356563782;
	const double b3 =  1.781477937;
	const double b4 = -1.821255978;
	const double b5 =  1.330274429;
	const double p  =  0.2316419;
	const double c  =  0.39894228;

	if(x >= 0.0) {
		double t = 1.0 / ( 1.0 + p * x );
		return (1.0 - c * exp( -x * x / 2.0 ) * t *
				( t *( t * ( t * ( t * b5 + b4 ) + b3 ) + b2 ) + b1 ));
	}
	else {
		double t = 1.0 / ( 1.0 - p * x );
		return ( c * exp( -x * x / 2.0 ) * t *
				( t *( t * ( t * ( t * b5 + b4 ) + b3 ) + b2 ) + b1 ));
	}
}

double Gaussian::getLeftMargin()
{
	return mean - 4 * sqrt(variance);
}

double Gaussian::getRightMargin()
{
	return mean + 4 * sqrt(variance);
}

double Gaussian::nextSample()
{
	return rejectionSampling(pdf(mean), getLeftMargin(), getRightMargin());
}

} // namespace stochastic
