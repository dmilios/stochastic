/*
 * MonteCarloAlgorithm.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef MONTECARLOALGORITHM_H_
#define MONTECARLOALGORITHM_H_

#include "RandomVariableAlgorithm.h"
#include <map>

using namespace std;

namespace stochastic
{

class MonteCarloAlgorithm: public RandomVariableAlgorithm
{
private:
	int numberOfSamples;
	double recursiveSampling(OperationType, RandomVariable &, RandomVariable &,
			map<string, double> &);

	int discardSamplesFlag;

public:
	MonteCarloAlgorithm(int);
	MonteCarloAlgorithm(int, int);
	virtual ~MonteCarloAlgorithm();

	string getName();

	RandomVariable calculateSum(RandomVariable &, RandomVariable &);
	RandomVariable calculateDifference(RandomVariable &, RandomVariable &);
	RandomVariable calculateProduct(RandomVariable &, RandomVariable &);
	RandomVariable calculateRatio(RandomVariable &, RandomVariable &);

	RandomVariable calculateMin(RandomVariable &, RandomVariable &);
	RandomVariable calculateMax(RandomVariable &, RandomVariable &);

	RandomVariable calculateSum(RandomVariable &, double);
	RandomVariable calculateDifference(RandomVariable &, double);
	RandomVariable calculateDifference(double, RandomVariable &);
	RandomVariable calculateProduct(RandomVariable &, double);
	RandomVariable calculateRatio(RandomVariable &, double);
	RandomVariable calculateRatio(double, RandomVariable &);

	RandomVariable calculateMin(RandomVariable &, double);
	RandomVariable calculateMax(RandomVariable &, double);
};

} // namespace stochastic

#endif /* MONTECARLOALGORITHM_H_ */
