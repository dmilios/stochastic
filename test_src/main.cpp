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
	std::cout << "\nThe arguments were:\n";
	for (i = 0; i < argc; i++)
		std::cout << argv[i]<< "\n" ;
	return 0;
}

int main(int argc, char *argv[])
{
	Gnuplot plot;
	std::vector <double> iteration_numbers;
	std::vector <double> errors;

	Experiments::computationsPU(iteration_numbers, errors);
	plot.addCurve(OTHER, "Kolmogorov Distance Evolution for New", iteration_numbers, errors);

	PiecewiseUniform::useold = 1;
	Experiments::computationsPU(iteration_numbers, errors);
	plot.addCurve(OTHER, "Kolmogorov Distance Evolution for Old", iteration_numbers, errors);

	plot.plotBuffered(OTHER);

	return printArguments(argc, argv);
}
