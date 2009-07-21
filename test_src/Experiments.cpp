/*
 * Experiments.cpp
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "Experiments.h"

#include "Gnuplot.h"
#include <cmath>
#include <algorithm>

void Experiments::current()
{
	MonteCarloOperations::setNumberOfSamples(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	//	Gaussian g, g1(1);
	//	Uniform u(-4, 4);
	//	Exponential e;
	//	EmpiricalDistribution emp("pLin.txt");

	//	std::vector <MixtureComponent *> c;
	//	std::vector <double> w;
	//	c.push_back(new Gaussian(0, 1));
	//	w.push_back(1);
	//	c.push_back(new Gaussian(4, 2));
	//	w.push_back(1);
	//	MixtureModel m(c, w);

	RandomVariable r1 = new Gaussian;
	RandomVariable r2 = new Gaussian;
	//	RandomVariable r3 = 100 / r1;

	RandomVariable r4;
	r4 = MonteCarloOperations::min(1, r1);

	plot.addRV(r1);
	//	plot.addRV(r2);
	//	plot.addRV(r3);
	plot.addRV(r4);


	//	std::cout << Experiments::kolmogorovDistance(r1.getDistribution(), r2.getDistribution()) << "\n";

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::comparePUwithMC()
{
	MonteCarloOperations::setNumberOfSamples(10000);
	PiecewiseBase::setFixedNumberOfComponents(50);

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian(2, 2);
	RandomVariable r2 = new Gaussian(2, 2);

	timer = clock();
	RandomVariable r3 = r1 + r2;
	std::cout << "PU time: " << clock() - timer << "\n";

	timer = clock();
	RandomVariable r4 = MonteCarloOperations::sum(r1, r2);
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

// conduct a series of computations with known results
// to see how PU approximation is affected
void Experiments::computationsPU()
{
	PiecewiseBase::setFixedNumberOfComponents(100);

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable rv = new Gaussian;
	PiecewiseUniform pu(new Gaussian);

	Gaussian * original = (Gaussian *)rv.getDistribution();
	std::cout << "\n0: Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(& pu, original);
	std::cout << std::endl << std::endl;

	RandomGenerator random;
	int i;
	for(i = 0; i < 100; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv = rv + (* new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "PU time: " << clock() - timer << "\n";
		std::cout << i + 1 << ": ";
		std::cout << "Kolmogorov Distance between PU and original: ";
		std::cout << kolmogorovDistance(rv.getDistribution(), original);
		std::cout << std::endl << std::endl;
	}
	plot.addRV(* new RandomVariable(original)); // plot the last only
	plot.addRV(rv);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::sumOfUniforms()
{
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseUniform);

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

void Experiments::minmaxOfUniforms()
{
	MonteCarloOperations::setNumberOfSamples(10000);
	PiecewiseBase::setFixedNumberOfComponents(1);
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Uniform(2, 4);
	RandomVariable r2 = new Uniform(3, 6);
	RandomVariable r3 = min(r1, r2);
	RandomVariable r4 = MonteCarloOperations::min(r1, r2);

	plot.addRV(r1);
	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::minmaxOfGaussians()
{
	MonteCarloOperations::setNumberOfSamples(10000);
	PiecewiseBase::setFixedNumberOfComponents(1);
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Gaussian(2, 4);
	RandomVariable r2 = new Gaussian(3, 6);
	RandomVariable r3 = min(r1, r2);
	RandomVariable r4 = MonteCarloOperations::min(r1, r2);

	plot.addRV(r1);
	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

/*
 *
 *
 * Distance metrics
 *
 * */

double Experiments::kolmogorovDistance(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 1000;
	double supremum = 0;
	double start = std::min(arg1->getLeftMargin(), arg2->getLeftMargin());
	double end = std::max(arg1->getRightMargin(), arg2->getRightMargin());
	double step = (end - start) / (double) accuracy;
	double x = start;
	double distance;
	int i;
	for (i = 0; i < accuracy; i++)
	{
		distance = std::abs(arg1->cdf(x) - arg2->cdf(x));
		if (supremum < distance)
			supremum = distance;
		x += step;
	}
	return supremum;
}

/* @brief Computes KL-Div(P||Q), where P==this, Q==arg
 * Integral is computed by constructing interpolating linear functions */
double Experiments::KL_Divergence(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 100;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;
	double px = arg1->pdf(x);
	double qx = arg2->pdf(x);

	fx_a = px * log(px / qx);
	for (i = 0; i < accuracy; i++)
	{
		px = arg1->pdf(x + step);
		qx = arg2->pdf(x + step);
		if (!px || !qx) // any pdf is zero
		{
			x = x + step;
			continue;
		}
		fx_b = px * log(px / qx);
		result += step * (fx_a + fx_b) / 2;

		fx_a = fx_b;
		x = x + step;
	}
	return result;
}

double Experiments::hellingerDistance(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 100;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;

	fx_a = pow(sqrt(arg1->pdf(x)) - sqrt(arg1->pdf(x)), 2);
	for (i = 0; i < accuracy; i++)
	{
		fx_b = pow(sqrt(arg1->pdf(x + step)) - sqrt(arg1->pdf(x + step)), 2);
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return sqrt(result / 2);
}
