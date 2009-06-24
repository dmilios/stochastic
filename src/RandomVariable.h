/*
 * RandomVariable.h
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMVARIABLE_H_
#define RANDOMVARIABLE_H_

#include "Distribution.h"

#include <vector>

namespace stochastic {

class RandomVariable
{
private:
	Distribution * distribution;

public:
	RandomVariable();
	RandomVariable(Distribution *);
	virtual ~RandomVariable();

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
};

/*
 * the very same implementation
 * as in RandomVariable::min and RandomVariable::max,
 * but these are called in a more intuitive way
 */
RandomVariable min(RandomVariable, RandomVariable);
RandomVariable max(RandomVariable, RandomVariable);

} // namespace stochastic

#endif /* RANDOMVARIABLE_H_ */
