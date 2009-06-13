/*
 * Exponential.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: dimitrios
 */

#include "Exponential.h"

#include "exceptions.h"
#include <cmath>

namespace stochastic {

Exponential::Exponential()
{
	this->lambda = 1;
}

Exponential::Exponential(double lambda)
{
	if (lambda <= 0)
		throw InvalidParametersException();
	this->lambda = lambda;
}

Exponential::~Exponential()
{
}

double Exponential::pdf(double x)
{
	if (x < 0)
		return 0;
	return lambda * exp(-lambda * x);
}

// sample using inverse CDF
double Exponential::nextSample()
{
	return -(1 / lambda) * log(1 - generator.nextDouble());
}

} // namespace stochastic
