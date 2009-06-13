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
		throw InvalidParametersException();

	this->mean = mean;
	this->variance = variance;
}

Gaussian::~Gaussian()
{
}

double Gaussian::pdf(double x)
{
	return (1 / sqrt(2 * pi * variance) * exp(-pow(x - mean, 2)
			/ (2 * variance)));
}

double Gaussian::nextSample()
{
	double highestProbability = pdf(mean);
	double leftMargin = mean - 3 * sqrt(variance);
	double rightMargin = mean + 3 * sqrt(variance);

	return rejectionSampling(highestProbability, leftMargin, rightMargin);
}

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Gaussian Approximation Component
 */

ApproximationComponent * Gaussian::add(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::subtract(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::multiply(
		ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::divide(
		ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Gaussian Approximation Component
 */

ApproximationComponent * Gaussian::min(
		ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::max(
		ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(*this)
			!= typeid(*secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

} // namespace stochastic
