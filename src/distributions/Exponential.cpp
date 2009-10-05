/*
 * Exponential.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: dimitrios
 */

#include "Exponential.h"

#include "../utilities/exceptions.h"
#include <cmath>
#include <string>
#include <sstream>

namespace stochastic {

Exponential::Exponential()
{
	this->lambda = 1;
}

Exponential::Exponential(double lambda)
{
	if (lambda <= 0)
	{
		std::stringstream lambda_s;
		lambda_s << lambda;
		std::string message = "lambda = ";
		message.append(lambda_s.str());
		message.append(" : lambda <= 0 in a Exponential");
		throw InvalidParametersException(message);
	}
	this->lambda = lambda;
}

Exponential::~Exponential()
{
}

const char * Exponential::getName()
{
	std::stringstream lambda_s;
	lambda_s << this->lambda;
	std::string name("Exp(");
	name.append(lambda_s.str());
	name.append(")");
	return name.c_str();
}

double Exponential::pdf(double x)
{
	if (x < 0)
		return 0;
	return lambda * exp(-lambda * x);
}

double Exponential::cdf(double x)
{
	if (x < 0)
		return 0;
	return 1.0 - exp(-lambda * x);
}

double Exponential::getLeftMargin()
{
	return 0;
}

double Exponential::getRightMargin()
{
	return (1 / lambda) * 5;
}


// sample using inverse CDF
double Exponential::nextSample()
{
	return -(1 / lambda) * log(1 - generator.nextDouble());
}

} // namespace stochastic
