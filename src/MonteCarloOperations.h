/*
 * MonteCarloOperations.h
 *
 *  Created on: 24-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef MONTECARLOOPERATIONS_H_
#define MONTECARLOOPERATIONS_H_

#include "RandomVariable.h"

namespace stochastic {

class MonteCarloOperations
{
private:
	static int numberOfSamples;

public:
    static void setNumberOfSamples(int);

	static RandomVariable sum(RandomVariable, RandomVariable);
	static RandomVariable difference(RandomVariable, RandomVariable);
	static RandomVariable product(RandomVariable, RandomVariable);
	static RandomVariable ratio(RandomVariable, RandomVariable);

	static RandomVariable min(RandomVariable, RandomVariable);
	static RandomVariable max(RandomVariable, RandomVariable);
};

} // namespace stochastic

#endif /* MONTECARLOOPERATIONS_H_ */
