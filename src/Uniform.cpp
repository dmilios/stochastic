/*
 * Uniform.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Uniform.h"

#include "exceptions.h"
#include <typeinfo>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

namespace stochastic {

Uniform::Uniform()
{
	this->alpha = 0;
	this->beta = 1;
}

Uniform::Uniform(double alpha, double beta)
{
	if (alpha >= beta)
		throw InvalidParametersException();

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

	std::string name("uni_a");
	name.append(alpha_s.str());
	name.append("_b");
	name.append(beta_s.str());
	return name.c_str();
}

double Uniform::pdf(double x)
{
	/**
	 * NOTE: pdf is defined for 'a <= x < b'
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

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Uniform Approximation Component
 */

MixtureComponent * Uniform::sum(PiecewiseComponent * rightarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncompatibleComponentsException();

	double a = this->alpha + rightarg->getLeftMargin();
	double b = this->beta + rightarg->getRightMargin();
	result = new Uniform(a, b);
	return result;
}

MixtureComponent * Uniform::difference(PiecewiseComponent * rightarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncompatibleComponentsException();

	double a = this->alpha - rightarg->getRightMargin();
	double b = this->beta - rightarg->getLeftMargin();
	result = new Uniform(a, b);
	return result;
}

MixtureComponent * Uniform::product(PiecewiseComponent * rightarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<double> margins;
	margins.push_back(alpha * rightarg->getLeftMargin());
	margins.push_back(alpha * rightarg->getRightMargin());
	margins.push_back(beta * rightarg->getLeftMargin());
	margins.push_back(beta * rightarg->getRightMargin());
	std::vector<double>::iterator a = std::min_element(
									margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
									margins.begin(), margins.end());
	result = new Uniform(* a, * b);
	return result;
}

MixtureComponent * Uniform::ratio(PiecewiseComponent * rightarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<double> margins;
	margins.push_back(alpha / rightarg->getLeftMargin());
	margins.push_back(alpha / rightarg->getRightMargin());
	margins.push_back(beta / rightarg->getLeftMargin());
	margins.push_back(beta / rightarg->getRightMargin());
	std::vector<double>::iterator a = std::min_element(
									margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
									margins.begin(), margins.end());
	result = new Uniform(* a, * b);
	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Uniform Approximation Component
 */

MixtureComponent * Uniform::min(PiecewiseComponent * secondarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncompatibleComponentsException();
	result = new Uniform;

	return result;
}

MixtureComponent * Uniform::max(PiecewiseComponent * secondarg)
{
	PiecewiseComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncompatibleComponentsException();
	result = new Uniform;

	return result;
}

} // namespace stochastic
