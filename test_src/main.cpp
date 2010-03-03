// =============================================================

/* 'stochastic' is a library
 * for performing operations between random variables
 *
 * main() is used for test purposes
 *
 *
 *      Author: Dimitrios Milios
 */

// =============================================================


// load "stochastic" library
#include "../src/stochastic.h"

#include "Experiments.h"
#include "Gnuplot.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>

int printArguments(int argc, char *argv[])
{
	int i;
	std::cout << "The arguments were:\n";
	for (i = 0; i < argc; i++)
		std::cout << argv[i] << "\n";
	return 0;
}

int main(int argc, char *argv[])
{
	testApproximation(new Gaussian, new PG_EM(100, 1000));
	return 0;

	Gnuplot plot;
	plot.addErrorEvolution(50, new PiecewiseGaussian(100));
	plot.addErrorEvolution(50, new PG_EM(100, 100));
	plot.plotBuffered(EVOLUTION);

	return printArguments(argc, argv);
}
