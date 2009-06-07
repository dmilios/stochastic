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

class RandomVariable {
private:
	Distribution * distribution;

public:
	RandomVariable();
	virtual ~RandomVariable();
};

} // namespace stochastic

#endif /* RANDOMVARIABLE_H_ */
