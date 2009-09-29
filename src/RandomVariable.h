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
	RATIO,
	MIN,
	MAX
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

	static RandomVariable monteCarlo(OperationType, RandomVariable *,
			RandomVariable *);
	static double recursiveSampling(OperationType, RandomVariable *,
			RandomVariable *);

public:
	RandomVariable();
	RandomVariable(Distribution *);
	virtual ~RandomVariable();

	static void setMonteCarlo(int number_of_samples);
	static void setPiecewiseUniform(int number_of_components);
	static void setPiecewiseGaussian(int number_of_components);


	Distribution * getDistribution();
	void setDistribution(Distribution *);
	void pdfOutline(int, std::vector <double> &, std::vector <double> &);
	void cdfOutline(int, std::vector <double> &, std::vector <double> &);
	void quantileOutline(int, std::vector <double> &, std::vector <double> &);
	void produceFileOfSamples(int);

	RandomVariable operator +(RandomVariable &);
	RandomVariable operator -(RandomVariable &);
	RandomVariable operator *(RandomVariable &);
	RandomVariable operator /(RandomVariable &);
	RandomVariable min(RandomVariable &);
	RandomVariable max(RandomVariable &);

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
	friend RandomVariable operator +(double, RandomVariable &);
	friend RandomVariable operator -(double, RandomVariable &);
	friend RandomVariable operator *(double, RandomVariable &);
	friend RandomVariable operator /(double, RandomVariable &);
};

/*
 * the very same implementation
 * as in RandomVariable::min and RandomVariable::max,
 * but these are called in a more intuitive way
 */
RandomVariable min(RandomVariable &, RandomVariable &);
RandomVariable max(RandomVariable &, RandomVariable &);

RandomVariable min(RandomVariable &, double);
RandomVariable max(RandomVariable &, double);
RandomVariable min(double, RandomVariable &);
RandomVariable max(double, RandomVariable &);

} // namespace stochastic

#endif /* RANDOMVARIABLE_H_ */
