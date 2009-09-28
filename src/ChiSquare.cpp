/*
 * ChiSquare.cpp
 *
 *  Created on: 13-Aug-2009
 *      Author: Dimitrios Milios
 */

#include "ChiSquare.h"
#include "exceptions.h"
#include <sstream>
#include <cmath>
#include <boost/math/special_functions/gamma.hpp>

namespace stochastic {

ChiSquare::ChiSquare()
{
	k = 1;
}

ChiSquare::ChiSquare(int k)
{
	if (k <= 0)
		throw InvalidParametersException("k <= 0 in Chi_Square");
	this->k = k;
}

ChiSquare::~ChiSquare()
{
}

const char * ChiSquare::getName()
{
	std::stringstream k_s;
	k_s << k;
	std::string name = "$\\chi_{";
	name.append(k_s.str());
	name.append("}^2$");
	return name.c_str();
}

double ChiSquare::pdf(double x)
{
	if (x <= 0)
		return 0;
	double k_2 = (double) k / 2;

	// FIXME: something has gone terribly wrong in here (no matter for experiments)
	return (1 / (pow(2, k_2) * gamma(k_2))) * pow(x, k_2 - 1) * exp(-x / 2);
}

double ChiSquare::cdf(double x)
{
	if (x <= 0)
		return 0;
	return boost::math::gamma_p((double) k / 2, x / 2);
}

double ChiSquare::getLeftMargin()
{
	return 0;
}

double ChiSquare::getRightMargin()
{
	return k * 5;
}

double ChiSquare::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
