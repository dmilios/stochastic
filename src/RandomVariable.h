/*
 * RandomVariable.h
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLE_H_
#define RANDOMVARIABLE_H_

#include "distributions/Distribution.h"
#include "algorithms/RandomVariableAlgorithm.h"
#include "graph/GraphRV.h"
#include "graph/OperationType.h"

#include <vector>
#include <map>

namespace stochastic
{

class RandomVariableAlgorithm;
class GraphRV;

class RandomVariable
{
private:
	Distribution * distribution;
	std::string randomVariableID;

	static GraphRV graph;
	static RandomVariableAlgorithm * algorithm;

public:
	RandomVariable();
	RandomVariable(Distribution *);
	RandomVariable& operator=(RandomVariable);
	virtual ~RandomVariable();

	static void setAlgorithm(RandomVariableAlgorithm *);

	Distribution * getDistribution() const;
	std::string getRandomVariableID() const;

	void pdfOutline(int, std::vector<double> &, std::vector<double> &);
	void cdfOutline(int, std::vector<double> &, std::vector<double> &);
	void quantileOutline(int, std::vector<double> &, std::vector<double> &);
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
