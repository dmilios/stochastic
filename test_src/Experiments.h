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

	static void computationsEvolution();
	static void computationsPU(std::vector <double> &, std::vector <double> &);
	static void computationsPG(std::vector <double> &, std::vector <double> &);
	static void computationsMC(std::vector <double> &, std::vector <double> &);

	static void dependencyMC();

	static void pgApproxExample();

	static void sumOfUniforms();
	static void minmaxTests();
	static void productTests();
	static void ratioTests();
};

#endif /* EXPERIMENTS_H_ */
