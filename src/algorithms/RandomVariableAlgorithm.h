/*
 * RandomVariableAlgorithm.h
 *
 *  Created on: 29-Sep-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLEALGORITHM_H_
#define RANDOMVARIABLEALGORITHM_H_

#include "../RandomVariable.h"

namespace stochastic {

class RandomVariable;

class RandomVariableAlgorithm
{
public:
	virtual ~RandomVariableAlgorithm()
	{
	}

	virtual RandomVariable calculateSum(RandomVariable &, RandomVariable &) = 0;
	virtual RandomVariable calculateDifference(RandomVariable &,
			RandomVariable &) = 0;
	virtual RandomVariable
			calculateProduct(RandomVariable &, RandomVariable &) = 0;
	virtual RandomVariable
			calculateRatio(RandomVariable &, RandomVariable &) = 0;

	virtual RandomVariable calculateMin(RandomVariable &, RandomVariable &) = 0;
	virtual RandomVariable calculateMax(RandomVariable &, RandomVariable &) = 0;

	virtual RandomVariable calculateSum(RandomVariable &, double) = 0;
	virtual RandomVariable calculateDifference(RandomVariable &, double) = 0;
	virtual RandomVariable calculateDifference(double, RandomVariable &) = 0;
	virtual RandomVariable calculateProduct(RandomVariable &, double) = 0;
	virtual RandomVariable calculateRatio(RandomVariable &, double) = 0;
	virtual RandomVariable calculateRatio(double, RandomVariable &) = 0;

	virtual RandomVariable calculateMin(RandomVariable &, double) = 0;
	virtual RandomVariable calculateMax(RandomVariable &, double) = 0;
};

} // namespace stochastic

#endif /* RANDOMVARIABLEALGORITHM_H_ */
