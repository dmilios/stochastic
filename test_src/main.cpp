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

	Gnuplot plot;

	Gaussian g;
	Uniform u;
	Linear l(0, 1, 1);
	Exponential e;

	std::vector <MixtureComponent *> c;
	std::vector <double> w;
	c.push_back(new Exponential(15));
	w.push_back(1);
	c.push_back(new Exponential());
	w.push_back(3);
	MixtureModel m(c, w);

	PiecewiseUniform pu = new Gaussian;
	PiecewiseLinear pl = new Gaussian;

	RandomVariable r1 = new Gaussian;
	RandomVariable r2 = &pu;
	RandomVariable r3 = &pl;

	int accuracy = 1000;
	std::vector <double> vx;
	std::vector <double> vy;

	r1.pdfOutline(accuracy, vx, vy);
	plot.addCurve("a", vx, vy);
	r2.pdfOutline(accuracy, vx, vy);
	plot.addCurve("a", vx, vy);
	r3.pdfOutline(accuracy, vx, vy);
	plot.addCurve("a", vx, vy);

	plot.plotCurves();

	//r1.produceFileOfSamples(10000);

	return printArguments(argc, argv);
}
