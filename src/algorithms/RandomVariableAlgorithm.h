/*
 * RandomVariableAlgorithm.h
 *
 *  Created on: 29-Sep-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLEALGORITHM_H_
#define RANDOMVARIABLEALGORITHM_H_

#include "../distributions/Distribution.h"

namespace stochastic
{

class RandomVariableAlgorithm
{
public:
	virtual ~RandomVariableAlgorithm()
	{
	}

	virtual Distribution * calculateSum(Distribution *, Distribution *) = 0;
	virtual Distribution
			* calculateDifference(Distribution *, Distribution *) = 0;
	virtual Distribution * calculateProduct(Distribution *, Distribution *) = 0;
	virtual Distribution * calculateRatio(Distribution *, Distribution *) = 0;

	virtual Distribution * calculateMin(Distribution *, Distribution *) = 0;
	virtual Distribution * calculateMax(Distribution *, Distribution *) = 0;

	virtual Distribution * calculateSum(Distribution *, double) = 0;
	virtual Distribution * calculateDifference(Distribution *, double) = 0;
	virtual Distribution * calculateDifference(double, Distribution *) = 0;
	virtual Distribution * calculateProduct(Distribution *, double) = 0;
	virtual Distribution * calculateRatio(Distribution *, double) = 0;
	virtual Distribution * calculateRatio(double, Distribution *) = 0;

	virtual Distribution * calculateMin(Distribution *, double) = 0;
	virtual Distribution * calculateMax(Distribution *, double) = 0;
};

} // namespace stochastic

#endif /* RANDOMVARIABLEALGORITHM_H_ */
