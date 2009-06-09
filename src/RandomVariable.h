/*
 * RandomVariable.h
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLE_H_
#define RANDOMVARIABLE_H_

#include "Distribution.h"

namespace stochastic {

class RandomVariable
{
private:
	Distribution * distribution;

public:
	RandomVariable();
	RandomVariable(Distribution *);
	virtual ~RandomVariable();

	void setDistribution(Distribution *);

	RandomVariable operator +(RandomVariable);
	RandomVariable operator -(RandomVariable);
	RandomVariable operator *(RandomVariable);
	RandomVariable operator /(RandomVariable);

	RandomVariable min(RandomVariable);
	RandomVariable max(RandomVariable);
};

/*
 * the very same implementation
 * as in RandomVariable::min and RandomVariable::max,
 * but these are called in a more intuitive way
 */
RandomVariable min(RandomVariable, RandomVariable);
RandomVariable max(RandomVariable, RandomVariable);

} // namespace stochastic

#endif /* RANDOMVARIABLE_H_ */
