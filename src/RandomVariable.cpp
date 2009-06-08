/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"
#include "UndefinedDistributionException.h"

namespace stochastic {

RandomVariable::RandomVariable()
{
	this->distribution = 0;
}

RandomVariable::RandomVariable(Distribution * distribution)
{
	this->setDistribution(distribution);
}

RandomVariable::~RandomVariable()
{
}

void RandomVariable::setDistribution(Distribution * distribution)
{
	this->distribution = distribution;
}

/*
 *
 * --- Overload Binary Operators: '+', '-', '*', '/'
 */

RandomVariable RandomVariable::operator +(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

RandomVariable RandomVariable::operator -(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
			throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

RandomVariable RandomVariable::operator *(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
			throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

RandomVariable RandomVariable::operator /(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
			throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

/*
 *
 * --- Define Binary Operators: min, max
 */

// The first argument is 'this' object
RandomVariable RandomVariable::min(RandomVariable secondarg)
{
	if (!distribution || !secondarg.distribution)
			throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

// The first argument is 'this' object
RandomVariable RandomVariable::max(RandomVariable secondarg)
{
	if (!distribution || !secondarg.distribution)
			throw stochastic::UndefinedDistributionException();

	// TODO fill code
	return RandomVariable();
}

// the very same implementation as in RandomVariable::min,
// but this is called in a more intuitive way
RandomVariable min(RandomVariable firstarg, RandomVariable secondarg)
{
	return firstarg.min(secondarg);
}

// the very same implementation as in RandomVariable::max,
// but this is called in a more intuitive way
RandomVariable max(RandomVariable firstarg, RandomVariable secondarg)
{
	return firstarg.max(secondarg);
}

} // namespace stochastic
