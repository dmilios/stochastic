/*
 * Gaussian.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Gaussian.h"

#include "IncomparableInnerRepresentationException.h"
#include <typeinfo>

namespace stochastic {

Gaussian::Gaussian()
{
}

Gaussian::~Gaussian()
{
}

//FIXME: change void to 'array of samples'
void Gaussian::sample(int numberOfSamples)
{
}

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Gaussian Approximation Component
 */

ApproximationComponent * Gaussian::add(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::subtract(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::multiply(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::divide(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Gaussian Approximation Component
 */

ApproximationComponent * Gaussian::min(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

ApproximationComponent * Gaussian::max(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Gaussian;

	return result;
}

} // namespace stochastic
