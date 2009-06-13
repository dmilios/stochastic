/*
 * Distribution.h
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

#include <vector>
#include "RandomGenerator.h"

namespace stochastic {

class Distribution
{
protected:
	static RandomGenerator generator;

	double rejectionSampling(double, double, double);

public:
	Distribution();
	virtual ~Distribution();

	//virtual std::vector <double> pdfOutline(int) = 0;
	virtual double pdf(double) = 0;
	virtual double nextSample() = 0;
	std::vector <double> sample(int);
};

} // namespace stochastic

#endif /* DISTRIBUTION_H_ */
