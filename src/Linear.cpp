/*
 * Linear.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Linear.h"

#include "IncomparableInnerRepresentationException.h"
#include <typeinfo>

namespace stochastic {

Linear::Linear()
{
}

Linear::~Linear()
{
}

double Linear::nextSample()
{
	return 0;
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
	result = new Linear;

	return result;
}

ApproximationComponent * Linear::subtract(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear;

	return result;
}

ApproximationComponent * Linear::multiply(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear;

	return result;
}

ApproximationComponent * Linear::divide(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* rightarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear;

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
	result = new Linear;

	return result;
}

ApproximationComponent * Linear::max(ApproximationComponent * secondarg)
{
	ApproximationComponent * result;
	if (typeid(* this) != typeid(* secondarg))
		throw stochastic::IncomparableInnerRepresentationException();
	result = new Linear;

	return result;
}

} // namespace stochastic
