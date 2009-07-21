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


	static RandomVariable sum(double, RandomVariable);
	static RandomVariable difference(double, RandomVariable);
	static RandomVariable product(double, RandomVariable);
	static RandomVariable ratio(double, RandomVariable);
	static RandomVariable min(double, RandomVariable);
	static RandomVariable max(double, RandomVariable);
	static RandomVariable sum(RandomVariable, double);
	static RandomVariable difference(RandomVariable, double);
	static RandomVariable product(RandomVariable, double);
	static RandomVariable ratio(RandomVariable, double);
	static RandomVariable min(RandomVariable, double);
	static RandomVariable max(RandomVariable, double);


};

} // namespace stochastic

#endif /* MONTECARLOOPERATIONS_H_ */
