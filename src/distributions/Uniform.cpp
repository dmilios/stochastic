/*
 * Uniform.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Uniform.h"

#include "../utilities/exceptions.h"
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

namespace stochastic {

Uniform::Uniform()
{
	this->alpha = 0;
	this->beta = 1;
}

Uniform::Uniform(double alpha, double beta)
{
	if (alpha >= beta)
	{
		std::stringstream alpha_s;
		std::stringstream beta_s;
		alpha_s << alpha;
		beta_s << beta;
		std::string message = "alpha = ";
		message.append(alpha_s.str());
		message.append(", beta = ");
		message.append(beta_s.str());
		message.append(" : alpha >= beta in a Uniform");
		throw InvalidParametersException(message);
	}

	this->alpha = alpha;
	this->beta = beta;
}

Uniform::~Uniform()
{
}

const char * Uniform::getName()
{
	std::stringstream alpha_s;
	std::stringstream beta_s;
	alpha_s << this->alpha;
	beta_s << this->beta;

	std::string name("U(");
	name.append(alpha_s.str());
	name.append(",");
	name.append(beta_s.str());
	name.append(")");
	return name.c_str();
}

double Uniform::pdf(double x)
{
	/**
	 * pdf is defined for 'a <= x < b'
	 * instead of 'a <= x <= b', for convenience
	 */
	if (x < alpha || x >= beta)
		return 0;
	return 1 / (beta - alpha);
}

double Uniform::cdf(double x)
{
	if (x < alpha)
		return 0;
	if (x > beta)
		return 1;
	return (x - alpha) / (beta - alpha);
}

double Uniform::getLeftMargin()
{
	return this->alpha;
}

double Uniform::getRightMargin()
{
	return this->beta;
}

double Uniform::nextSample()
{
	return generator.nextDouble(alpha, beta);
}

} // namespace stochastic
