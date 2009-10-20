/*
 * Cauchy.cpp
 *
 *  Created on: 14-Aug-2009
 *      Author: Dimitrios Milios
 */

#include "Cauchy.h"

#include "../utilities/exceptions.h"
#include "../utilities/mathFunctions.h"
#include <sstream>
#include <cmath>
// #include <boost/math/special_functions.hpp>

namespace stochastic {

Cauchy::Cauchy(double location, double gamma)
{
	if (gamma <= 0)
		throw InvalidParametersException("gamma <= 0 in a Cauchy");
	this->location = location;
	this->gamma = gamma;
}

Cauchy::~Cauchy()
{
}

const char * Cauchy::getName()
{
	std::stringstream loc_s;
	loc_s << location;
	std::stringstream gamma_s;
	gamma_s << gamma;
	std::string name = "Cauchy(";
	name.append(loc_s.str());
	name.append(",");
	name.append(gamma_s.str());
	name.append(")");
	return name.c_str();
}

double Cauchy::pdf(double x)
{
	return (1 / PI) * (gamma / (pow(x - location, 2) + gamma * gamma));
}

double Cauchy::cdf(double x)
{
	return (1 / PI) * atan((x - location) / gamma) + 0.5;
}

// TODO: improve margins
double Cauchy::getLeftMargin()
{
	return location - pow(5, gamma);
}

double Cauchy::getRightMargin()
{
	return location + pow(5, gamma);
}

double Cauchy::nextSample()
{
	return quantile(generator.nextDouble());
}

} // namespace stochastic
