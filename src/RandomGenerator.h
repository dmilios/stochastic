/*
 * RandomGenerator.h
 *
 *  Created on: 13-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include <ctime> //for time()
#include <cstdlib> // for rand(), srand()
#include <string>

namespace stochastic {

class RandomGenerator
{
public:
	RandomGenerator()
	{
		srand(time(0));
	}
	virtual ~RandomGenerator()
	{
	}

	/**
	 * returns a uniformly distributed double
	 * in the range [0,1]
	 */
	double nextDouble()
	{
		return  (double)rand() / (double)RAND_MAX;
	}

	/**
	 * returns a uniformly distributed double
	 * in the range [a,b]
	 */
	double nextDouble(double a, double b)
	{
		return this->nextDouble() * (b - a) + a;
	}

	/**
	 * returns a uniformly distributed integer
	 * in the range [0,max]
	 */
	int nextInt(int max)
	{
		int value = ((double) rand() / RAND_MAX) * (max + 1);
		if (value > max)
			value = 0;
		return value;
	}

	/**
	 * returns a uniformly distributed integer
	 * in the range [0,1]
	 */
	int nextBoolean()
	{
		return nextInt(1);
	}
};

}

#endif /* RANDOMGENERATOR_H_ */
