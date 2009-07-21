/*
 * Experiments.h
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#include "../src/stochastic.h"

using namespace stochastic;

class Experiments
{
private:
	static double kolmogorovDistance(Distribution *, Distribution *);
	static double KL_Divergence(Distribution *, Distribution *);
	static double hellingerDistance(Distribution *, Distribution *);

public:
	static void current();
	static void comparePUwithMC();
	static void computationsPU();

	static void sumOfUniforms();
	static void minmaxOfUniforms();
	static void minmaxOfGaussians();
};

#endif /* EXPERIMENTS_H_ */
