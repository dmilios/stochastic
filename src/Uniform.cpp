/*
 * Uniform.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Uniform.h"

#include "IncomparableInnerRepresentationException.h"
#include <typeinfo>

namespace stochastic {

Uniform::Uniform()
{
}

Uniform::~Uniform()
{
}

//FIXME: change void to 'array of samples'
void Uniform::sample(int numberOfSamples)
{
}

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Uniform Approximation Component
 */

ApproximationComponent * Uniform::add(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

ApproximationComponent * Uniform::subtract(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

ApproximationComponent * Uniform::multiply(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

ApproximationComponent * Uniform::divide(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

/*
 *
 * --- Implement Binary Operators: min, max
 * --- for Uniform Approximation Component
 */

ApproximationComponent * Uniform::min(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

ApproximationComponent * Uniform::max(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Uniform;

	return result;
}

} // namespace stochastic
