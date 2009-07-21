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

namespace stochastic {

class RandomVariable
{
private:
	Distribution * distribution;
	static PiecewiseBase * approximator;

public:
	RandomVariable();
	RandomVariable(Distribution *);
	virtual ~RandomVariable();

	static void setApproximatorType(PiecewiseBase *);

	Distribution * getDistribution();
	void setDistribution(Distribution *);
	void pdfOutline(int, std::vector <double> &, std::vector <double> &);
	void cdfOutline(int, std::vector <double> &, std::vector <double> &);
	void quantileOutline(int, std::vector <double> &, std::vector <double> &);
	void produceFileOfSamples(int);

	RandomVariable operator +(RandomVariable);
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
