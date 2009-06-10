/*
 * Distribution.h
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

#include <vector>

namespace stochastic {

class Distribution
{
private:
	static int seedInitialized;

protected:
	/**
	 * 'nextUniform_0_1()' samples from a uniform(0,1) distribution.
	 * All derived classes inherit this generator,
	 * so as to sample from more complex distributions.
	 * */
	static double nextUniform_0_1();

public:
	Distribution();
	virtual ~Distribution();

	virtual double nextSample() = 0;
	std::vector <double> sample(int);
};

} // namespace stochastic

#endif /* DISTRIBUTION_H_ */
