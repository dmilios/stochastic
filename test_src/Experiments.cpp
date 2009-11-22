/*
 * Experiments.cpp
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "Experiments.h"

#include "Gnuplot.h"
#include <cmath>
#include <ctime>
#include <algorithm>

void current()
{
	RandomVariable::setAlgorithm(new PiecewiseGaussian(100));

	Gnuplot::setAccuracy(1000);
	Gnuplot plot;

	RandomVariable r1 = new Uniform(2, 3.5);
	RandomVariable r2 = new Uniform(1, 4.5);
	RandomVariable r3 = new SumOfUniforms(2, 3.5, 1, 4.5);

	RandomVariable::setAlgorithm(new MonteCarloAlgorithm(1000));
	RandomVariable r4 = r1 + r2;

	//	plot.addRV(r1);
	//	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

	//	std::cout << Experiments::kolmogorovDistance(r1.getDistribution(), r2.getDistribution()) << "\n";

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void comparePUwithMC()
{
	RandomVariable::setAlgorithm(new PiecewiseUniform(100));
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian(2, 2);
	RandomVariable r2 = new Gaussian(2, 2);

	timer = clock();
	RandomVariable r3 = r1 + r2;

	std::cout << "PU time: " << clock() - timer << "\n";

	RandomVariable::setAlgorithm(new MonteCarloAlgorithm(10000));
	timer = clock();
	RandomVariable r4 = r1 + r2;
	std::cout << "MC time: " << clock() - timer << "\n\n";

	Distribution * original = new Gaussian(4, 4);
	std::cout << "Kolmogorov Distance between PU and MC: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), r4.getDistribution());
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), original);
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between original and MC: ";
	std::cout << kolmogorovDistance(original, r4.getDistribution());
	std::cout << std::endl << std::endl;

	plot.addRV(r1);
	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void comparePGwithMC()
{
	RandomVariable::setAlgorithm(new PiecewiseGaussian(100));
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian(2, 2);
	RandomVariable r2 = new Gaussian(2, 2);

	timer = clock();
	RandomVariable r3 = r1 + r2;
	std::cout << "PG time: " << clock() - timer << "\n";

	RandomVariable::setAlgorithm(new MonteCarloAlgorithm(1000));
	timer = clock();
	RandomVariable r4 = r1 + r2;
	std::cout << "MC time: " << clock() - timer << "\n\n";

	Distribution * original = new Gaussian(4, 4);
	std::cout << "Kolmogorov Distance between PG and MC: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), r4.getDistribution());
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between PG and original: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), original);
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between original and MC: ";
	std::cout << kolmogorovDistance(original, r4.getDistribution());
	std::cout << std::endl << std::endl;

	plot.addRV(r1);
	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void compareApproximations()
{
	Gnuplot::setAccuracy(100);
	Gnuplot plot;
	long int timer;

	std::vector<MixtureComponent *> c;
	std::vector<double> w;
	c.push_back(new Gaussian(-2, 1));
	w.push_back(1);
	c.push_back(new Gaussian(4, 1.5));
	w.push_back(1);
	c.push_back(new Gaussian(24, 2));
	w.push_back(1);
	MixtureModel mm(c, w); // to test MM

	InverseRV_Distribution inv(new Gaussian); // to test long tailed


	RandomVariable rv = new Gaussian;
	RandomVariable pu = (new PiecewiseUniform(10))->approximate(
			rv.getDistribution());
	RandomVariable pg = (new PiecewiseGaussian(10))->approximate(
			rv.getDistribution());

	RandomVariable a(new Gaussian), b(new Gaussian);
	timer = clock();
	RandomVariable::setAlgorithm(new PiecewiseUniform(100));
	a + b;
	std::cout << "PU sum time (ms): " << 1000 * (double) (clock() - timer)
			/ CLOCKS_PER_SEC << "\n";

	timer = clock();
	RandomVariable::setAlgorithm(new PiecewiseGaussian(100));
	a + b;
	std::cout << "PG sum time (ms): " << 1000 * (double) (clock() - timer)
			/ CLOCKS_PER_SEC << "\n\n";

	std::cout << "KL Divergence between PU and original: ";
	std::cout << KL_Divergence(rv.getDistribution(), pu.getDistribution());
	std::cout << std::endl;
	std::cout << "KL Divergence between PG and original: ";
	std::cout << KL_Divergence(rv.getDistribution(), pg.getDistribution());
	std::cout << std::endl << std::endl;

	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(rv.getDistribution(), pu.getDistribution());
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between PG and original: ";
	std::cout << kolmogorovDistance(rv.getDistribution(), pg.getDistribution());
	std::cout << std::endl << std::endl;

	std::cout << "CDF Distance between PU and original: ";
	std::cout << manhattanDistanceCDF(rv.getDistribution(),
			pu.getDistribution());
	std::cout << std::endl;
	std::cout << "CDF Distance between PG and original: ";
	std::cout << manhattanDistanceCDF(rv.getDistribution(),
			pg.getDistribution());
	std::cout << std::endl << std::endl;

	plot.addRV(rv);
	plot.addRV(pu);
	plot.addRV(pg);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void computationsEvolution(int n)
{
	Gnuplot plot;
	std::vector<double> iteration_numbers;
	std::vector<double> errors;

	RandomVariable::setAlgorithm(new PU_DivideAndConquer(100));
	computations(n, iteration_numbers, errors);
	plot.addCurve(OTHER, "KL_Divergence Evolution for PU DivideAndConquer",
			iteration_numbers, errors);

	std::cout << std::endl << "--------------------------------" << std::endl;

	RandomVariable::setAlgorithm(new PiecewiseUniform(100));
	computations(n, iteration_numbers, errors);
	plot.addCurve(OTHER, "KL_Divergence Evolution for PU Old",
			iteration_numbers, errors);

	plot.plotBuffered(OTHER);
}

// conduct a series of computations with known results
void computations(int n, std::vector<double> & counters,
		std::vector<double> & errors)
{
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	Gaussian * original = (Gaussian *) rv.getDistribution();

	RandomGenerator random;
	int i;
	for (i = 0; i < n; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv = rv + (*new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "Time: " << clock() - timer << "\n";
		std::cout << i + 1 << ": ";
		std::cout << "PDF Distance from original: ";
		errors.push_back(manhattanDistancePDF(rv.getDistribution(), original));
		counters.push_back(i + 1);
		std::cout << errors[i + 1];
		std::cout << std::endl << std::endl;
	}
}

void dependencyMC()
{
	RandomVariable::setAlgorithm(new MonteCarloAlgorithm(500));

	Gnuplot::setAccuracy(100);
	Gnuplot plot;

	RandomVariable a = new Gaussian();
	RandomVariable b = new Gaussian();
	RandomVariable c, d;

	c = 9 * a;
	a = a + a + a;
	d = a + a + a;

	b = c;

	plot.addRV(b);
	plot.addRV(d);
	plot.plotBuffered(PDF);
}

void testApproximation(RandomVariable original,
		ApproximationAlgorithm &algorithm)
{
	Gnuplot::setAccuracy(100);
	Gnuplot plot;

	RandomVariable approximated;
	approximated = algorithm.approximate(original.getDistribution());

	std::cout << "\tPDF Distance: \t";
	std::cout << manhattanDistancePDF(original.getDistribution(),
			approximated.getDistribution());
	std::cout << std::endl;

	std::cout << "\tKolmogorov Distance: \t";
	std::cout << kolmogorovDistance(original.getDistribution(),
			approximated.getDistribution());
	std::cout << std::endl;

	std::cout << "\tCDF Distance: \t\t";
	std::cout << manhattanDistanceCDF(original.getDistribution(),
			approximated.getDistribution());
	std::cout << std::endl << std::endl;

	plot.addRV(original);
	plot.addRV(approximated);
	plot.plotBuffered(PDF);
}

void sumOfUniforms()
{
	RandomVariable::setAlgorithm(new PiecewiseUniform(100));

	Gnuplot::setAccuracy(1000);
	Gnuplot plot;

	RandomVariable r1, r2, r3;

	std::cout << "\nNon-overlapping uniforms\n";
	r1 = new Uniform(-12, -7);
	r2 = new Uniform(3, 6);
	r3 = r1 + r2;
	plot.addRV(r3);
	plot.plotBuffered(PDF);

	std::cout << "\nOverlapping uniforms\n";
	r1 = new Uniform(2, 4);
	r2 = new Uniform(3, 6);
	r3 = r1 + r2;
	plot.addRV(r3);
	plot.plotBuffered(PDF);

	std::cout << "\nOne  contains the other\n";
	r1 = new Uniform(2, 9);
	r2 = new Uniform(3, 6);
	r3 = r1 + r2;
	plot.addRV(r3);
	plot.plotBuffered(PDF);

	std::cout << "\nEqual uniforms\n";
	r1 = new Uniform(3, 6);
	r2 = new Uniform(3, 6);
	r3 = r1 + r2;
	plot.addRV(r3);
	plot.plotBuffered(PDF);
}

void minmaxTests()
{
	RandomVariable::setAlgorithm(new PiecewiseGaussian(100));
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Gaussian(0, 1);
	RandomVariable r2 = new Uniform(-2, 1);
	RandomVariable r3 = new MinOfDistributions(r1.getDistribution(),
			r2.getDistribution());

	RandomVariable r4 = min(r1, r2);

	//	plot.addRV(r1);
	//	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

