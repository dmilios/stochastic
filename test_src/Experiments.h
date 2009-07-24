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
	static double euclideanDistancePDF(Distribution *, Distribution *);
	static double manhattanDistancePDF(Distribution *, Distribution *);
	static double euclideanDistanceCDF(Distribution *, Distribution *);
	static double manhattanDistanceCDF(Distribution *, Distribution *);

public:
	static void current();
	static void comparePUwithMC();
	static void comparePGwithMC();
	static void compareApproximations();

	static void computationsPU();
	static void computationsPG();
	static void computationsMC();

	static void depedencyMC();

	static void sumOfUniforms();
	static void minmaxOfUniforms();
	static void minmaxOfGaussians();
	static void ratio();
};

#endif /* EXPERIMENTS_H_ */
