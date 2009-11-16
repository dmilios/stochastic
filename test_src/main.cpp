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
		std::cout << argv[i]<< "\n" ;
	return 0;
}

int main(int argc, char *argv[])
{
	RandomVariable rv = new Gaussian;

	PU_DivideAndConquer a1(100);
	std::cout << "PU_DivideAndConquer\n";
	testApproximation(rv, a1);

	std::cout << "PiecewiseUniform\n";
	PiecewiseUniform a2(100);
	testApproximation(rv, a2);

	return printArguments(argc, argv);
}
