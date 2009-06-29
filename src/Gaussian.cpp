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
		throw InvalidParametersException();

	this->mean = mean;
	this->variance = variance;
}

Gaussian::~Gaussian()
{
}

const char * Gaussian::getName()
{
	std::stringstream mean_s;
	std::stringstream var_s;
	mean_s << this->mean;
	var_s << this->variance;

	std::string name("norm_m");
	name.append(mean_s.str());
	name.append("_var");
	name.append(var_s.str());
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

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Gaussian Approximation Component
 */

MixtureComponent * Gaussian::sum(PiecewiseComponent * rightarg)
{
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncompatibleComponentsException();

	Gaussian * arg = (Gaussian *) rightarg;
	return new Gaussian(mean + arg->mean, variance + arg->variance);
}

MixtureComponent * Gaussian::difference(PiecewiseComponent * rightarg)
{
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncompatibleComponentsException();

	Gaussian * arg = (Gaussian *) rightarg;
	return new Gaussian(mean - arg->mean, variance + arg->variance);
}

MixtureComponent * Gaussian::product(PiecewiseComponent * rightarg)
{
	MixtureComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<double> margins;
	margins.push_back(getLeftMargin() * rightarg->getLeftMargin());
	margins.push_back(getLeftMargin() * rightarg->getRightMargin());
	margins.push_back(getRightMargin() * rightarg->getLeftMargin());
	margins.push_back(getRightMargin() * rightarg->getRightMargin());
	std::vector<double>::iterator a = std::min_element(
			margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
			margins.begin(), margins.end());
	double var = pow((* b - * a) / 8, 2);
	double m = (* a + * b) / 2;
	result = new Gaussian(m, var);
	return result;
}

MixtureComponent * Gaussian::ratio(PiecewiseComponent * rightarg)
{
	MixtureComponent * result;
	if (typeid(*this) != typeid(*rightarg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<double> margins;
	margins.push_back(getLeftMargin() / rightarg->getLeftMargin());
	margins.push_back(getLeftMargin() / rightarg->getRightMargin());
	margins.push_back(getRightMargin() / rightarg->getLeftMargin());
	margins.push_back(getRightMargin() / rightarg->getRightMargin());
	std::vector<double>::iterator a = std::min_element(
			margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
			margins.begin(), margins.end());
	double var = pow((* b - * a) / 8, 2);
	double m = (* a + * b) / 2;
	result = new Gaussian(m, var);
	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Gaussian Approximation Component
 */

MixtureComponent * Gaussian::min(PiecewiseComponent * secondarg)
{
	MixtureComponent * result;
	if (typeid(*this) != typeid(*secondarg))
		throw stochastic::IncompatibleComponentsException();

	double a = std::min<double>(getLeftMargin(), secondarg->getLeftMargin());
	double b = std::min<double>(getRightMargin(), secondarg->getRightMargin());
	double var = pow((b - a) / 8, 2);
	double m = (a + b) / 2;
	result = new Gaussian(m, var);
	return result;
}

MixtureComponent * Gaussian::max(PiecewiseComponent * secondarg)
{
	MixtureComponent * result;
	if (typeid(*this)
			!= typeid(*secondarg))
		throw stochastic::IncompatibleComponentsException();

	double a = std::max<double>(getLeftMargin(), secondarg->getLeftMargin());
	double b = std::max<double>(getRightMargin(), secondarg->getRightMargin());
	double var = pow((b - a) / 8, 2);
	double m = (a + b) / 2;
	result = new Gaussian(m, var);
	return result;
}

} // namespace stochastic
