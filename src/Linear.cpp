/*
 * Linear.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Linear.h"

#include "exceptions.h"
#include <typeinfo>
#include <cmath>
#include <string>
#include <sstream>

namespace stochastic {

Linear::Linear(double alpha, double beta, double slope)
{
	if (alpha >= beta)
		throw InvalidParametersException();

	//FIXME: check for negative pdf: adapt slope or range

	this->alpha = alpha;
	this->beta = beta;
	this->slope = slope;
	this->c = (1 - (slope/2) * (pow(beta, 2) - pow(alpha, 2))) / (beta-alpha);
}

Linear::~Linear()
{
}

const char * Linear::getName()
{
	std::stringstream alpha_s;
	std::stringstream beta_s;
	std::stringstream slope_s;
	alpha_s << this->alpha;
	beta_s << this->beta;
	slope_s << this->slope;

	std::string name("lin_a");
	name.append(alpha_s.str());
	name.append("_b");
	name.append(beta_s.str());
	name.append("_sl");
	name.append(slope_s.str());
	return name.c_str();
}

double Linear::pdf(double x)
{
	if (x < alpha || x > beta)
		return 0;
	return slope * x + c;
}

double Linear::getLeftMargin()
{
	return this->alpha;
}

double Linear::getRightMargin()
{
	return this->beta;
}

double Linear::nextSample()
{
	if (slope <= 0) // decreasing
		return rejectionSampling(pdf(alpha), alpha, beta);
	else // increasing
		return rejectionSampling(pdf(beta), alpha, beta);
}

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Linear Approximation Component
 */

ApproximationComponent * Linear::add(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

ApproximationComponent * Linear::subtract(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

ApproximationComponent * Linear::multiply(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

ApproximationComponent * Linear::divide(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Linear Approximation Component
 */

ApproximationComponent * Linear::min(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

ApproximationComponent * Linear::max(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear(0, 1, 1);

	return result;
}

} // namespace stochastic
