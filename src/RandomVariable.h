/*
 * RandomVariable.h
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLE_H_
#define RANDOMVARIABLE_H_

#include "Distribution.h"
#include "PiecewiseBase.h"

#include <vector>
#include <map>

namespace stochastic {

enum OperationType
{
	NONE,
	SUM,
	DIFFERENCE,
	PRODUCT,
	RATIO
};

class RandomVariable
{
private:
	static int monteCarloFlag;
	static int numberOfSamplesMC;
	static PiecewiseBase * approximator;

	static std::map <RandomVariable *, double> samplesCollection;

	Distribution * distribution;

	OperationType precededOperation;
	RandomVariable * parrent1;
	RandomVariable * parrent2;

	static RandomVariable recursive(OperationType, RandomVariable *,
			RandomVariable *);
	static double recursiveSample(OperationType, RandomVariable *,
			RandomVariable *);

	// Definitions of MonteCarlo versions of operators
	static RandomVariable MC_sum(RandomVariable *, RandomVariable *);
	static RandomVariable MC_difference(RandomVariable, RandomVariable);
	static RandomVariable MC_product(RandomVariable, RandomVariable);
	static RandomVariable MC_ratio(RandomVariable, RandomVariable);
	static RandomVariable MC_min(RandomVariable, RandomVariable);
	static RandomVariable MC_max(RandomVariable, RandomVariable);
	static RandomVariable MC_sum(double, RandomVariable);
	static RandomVariable MC_difference(double, RandomVariable);
	static RandomVariable MC_product(double, RandomVariable);
	static RandomVariable MC_ratio(double, RandomVariable);
	static RandomVariable MC_min(double, RandomVariable);
	static RandomVariable MC_max(double, RandomVariable);

public:
	RandomVariable();
	RandomVariable(Distribution *);
	virtual ~RandomVariable();

	static void setNumberOfSamplesMC(int);
	static void setMonteCarloFlag(int);
	static void setApproximatorType(PiecewiseBase *);

	Distribution * getDistribution();
	void setDistribution(Distribution *);
	void pdfOutline(int, std::vector <double> &, std::vector <double> &);
	void cdfOutline(int, std::vector <double> &, std::vector <double> &);
	void quantileOutline(int, std::vector <double> &, std::vector <double> &);
	void produceFileOfSamples(int);

	RandomVariable operator +(RandomVariable &);
	RandomVariable operator -(RandomVariable);
	RandomVariable operator *(RandomVariable);
	RandomVariable operator /(RandomVariable);
	RandomVariable min(RandomVariable);
	RandomVariable max(RandomVariable);

	// the negative sign
	friend RandomVariable operator -(RandomVariable);

	// also overload operators for functions of ONE random variable
	RandomVariable operator +(double);
	RandomVariable operator -(double);
	RandomVariable operator *(double);
	RandomVariable operator /(double);
	RandomVariable min(double);
	RandomVariable max(double);

	// overload the same operator for the doubles
	friend RandomVariable operator +(double, RandomVariable);
	friend RandomVariable operator -(double, RandomVariable);
	friend RandomVariable operator *(double, RandomVariable);
	friend RandomVariable operator /(double, RandomVariable);
};

/*
 * the very same implementation
 * as in RandomVariable::min and RandomVariable::max,
 * but these are called in a more intuitive way
 */
RandomVariable min(RandomVariable, RandomVariable);
RandomVariable max(RandomVariable, RandomVariable);

RandomVariable min(RandomVariable, double);
RandomVariable max(RandomVariable, double);
RandomVariable min(double, RandomVariable);
RandomVariable max(double, RandomVariable);

} // namespace stochastic

#endif /* RANDOMVARIABLE_H_ */
