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

#include "Gnuplot.h"
#include <cstdio>
#include <iostream>
#include <cmath>

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
	using namespace stochastic;
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

//	Gaussian g, g1(1);
//	Uniform u(-4, 4);
//	Exponential e;
//	EmpiricalDistribution emp("pLin.txt");

//	std::vector <MixtureComponent *> c;
//	std::vector <double> w;
//	c.push_back(new Gaussian(9, 1));
//	w.push_back(1);
//	c.push_back(new Gaussian(4, 2));
//	w.push_back(1);
//	MixtureModel m(c, w);

	RandomVariable r1 = new Gaussian(5, 0.5);
	RandomVariable r2 = new Gaussian(-5, 0.5);
	RandomVariable r3 = r1 + r2;

	RandomVariable r4;

	r4 = MonteCarloOperations::sum(r1, r2);
//	r4 = new PiecewiseUniform(r4.getDistribution());

	plot.addRV(r1);
	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

//	std::cout << r3.getDistribution()->kolmogorovDistance(r4.getDistribution()) << "\n";

	std::cout << "Time: " << clock() << "\n";
	plot.plotCurves();

	return printArguments(argc, argv);
}
