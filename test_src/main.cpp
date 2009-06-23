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
	ApproximatedDistribution::setFixedNumberOfComponents(10);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	Gaussian g, g1(1);
	Uniform u(-4, 4);
	Exponential e;

	std::vector <MixtureComponent *> c;
	std::vector <double> w;
	c.push_back(new Gaussian(15));
	w.push_back(1);
	c.push_back(new Gaussian());
	w.push_back(3);
	MixtureModel m(c, w);

	PiecewiseUniform pu = &m;
	PiecewiseGaussian pg("exp_l1.txt");

	RandomVariable r1 = &pg;
	RandomVariable r2 = &e;

//	r2.produceFileOfSamples(1000);

	plot.addRV(r1);
	//plot.addRV(r2);

	//std::cout << e.hellingerDistance(new Exponential(2)) << "\n";
	plot.plotCurves();

	return printArguments(argc, argv);
}
