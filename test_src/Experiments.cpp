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
	RandomVariable::setNumberOfSamplesMC(1000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseGaussian);

	Gnuplot::setAccuracy(1000);
	Gnuplot plot;



	RandomVariable r1 = new Uniform(2, 3.5);
	RandomVariable r2 = new Uniform(1, 4.5);
	RandomVariable r3 = new SumOfUniforms(2, 3.5, 1, 4.5);

	RandomVariable::setMonteCarloFlag(1);
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

void Experiments::pgApproxExample()
{
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	//	Gaussian g, g1(1);
	//	Uniform u(-4, 4);
	//	Exponential e;
	//	EmpiricalDistribution emp("pLin.txt");

	std::vector <MixtureComponent *> c;
	std::vector <double> w;

	int i;
	double a = 0;
	double b = 1;

	int n = 100;
	double step = (b - a) / n;
	double mi = a;
	double var = step * step;

	for (i = 0; i < n; i++)
	{
		c.push_back(new Gaussian(mi, var));
		w.push_back(1);
		mi += step;
	}
	MixtureModel m(c, w);

	RandomVariable r1 = &m;
//	RandomVariable r2 = new PiecewiseGaussian(new Exponential);
	//	RandomVariable r3 = 100 / r1;

	RandomVariable r4;
	//r4 = MonteCarloOperations::min(1, r1);

	plot.addRV(r1);
//	plot.addRV(r2);
	//	plot.addRV(r3);
	//plot.addRV(r4);


	//	std::cout << Experiments::kolmogorovDistance(r1.getDistribution(), r2.getDistribution()) << "\n";

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::comparePUwithMC()
{
	RandomVariable::setNumberOfSamplesMC(10000);
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

	RandomVariable::setMonteCarloFlag(1);
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

void Experiments::ratio()
{
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian;
	RandomVariable r2 = new Gaussian;

	timer = clock();
	RandomVariable r3 = r1 / r2;
	std::cout << "PU time: " << clock() - timer << "\n";

	RandomVariable::setMonteCarloFlag(1);
	timer = clock();
	RandomVariable r4 = r1 / r2;
	std::cout << "MC time: " << clock() - timer << "\n\n";

	Distribution * original = new Gaussian(4, 4); //  needed cauchy here
	std::cout << "Kolmogorov Distance between PU and MC: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), r4.getDistribution());
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), original);
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between original and MC: ";
	std::cout << kolmogorovDistance(original, r4.getDistribution());
	std::cout << std::endl << std::endl;

//	plot.addRV(r1);
//	plot.addRV(r2);
	plot.addRV(r3);
//	plot.addRV(r4);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::comparePGwithMC()
{
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian(2, 2);
	RandomVariable r2 = new Gaussian(2, 2);

	timer = clock();
	RandomVariable r3 = r1 + r2;
	std::cout << "PU time: " << clock() - timer << "\n";

	RandomVariable::setMonteCarloFlag(1);
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

void Experiments::compareApproximations()
{
	PiecewiseBase::setFixedNumberOfComponents(100);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;

	std::vector <MixtureComponent *> c;
	std::vector <double> w;
	c.push_back(new Gaussian(-2, 1));
	w.push_back(1);
	c.push_back(new Gaussian(24, 1));
	w.push_back(1);
	MixtureModel mm(c, w); // to test MM

	RandomVariable rv = new Gaussian;

	timer = clock();
	RandomVariable pu = new PiecewiseUniform(rv.getDistribution());
	std::cout << "PU time: " << clock() - timer << "\n";

	timer = clock();
	RandomVariable pg = new PiecewiseGaussian(rv.getDistribution());
	std::cout << "PG time: " << clock() - timer << "\n";

	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(rv.getDistribution(), pu.getDistribution());
	std::cout << std::endl;
	std::cout << "Kolmogorov Distance between PG and original: ";
	std::cout << kolmogorovDistance(rv.getDistribution(), pg.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PU and original: ";
	std::cout << euclideanDistanceCDF(rv.getDistribution(), pu.getDistribution());
	std::cout << std::endl;
	std::cout << "CDF Distance between PG and original: ";
	std::cout << euclideanDistanceCDF(rv.getDistribution(), pg.getDistribution());
	std::cout << std::endl;

	plot.addRV(rv);
	plot.addRV(pu);
	plot.addRV(pg);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::plotComputationsEvolution()
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
}

// conduct a series of computations with known results
// to see how PU approximation is affected
void Experiments::computationsPU(std::vector<double> & counters, std::vector<
		double> & errors)
{
	PiecewiseBase::setFixedNumberOfComponents(100);

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);
//	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	PiecewiseUniform pu(new Gaussian);

	Gaussian * original = (Gaussian *) rv.getDistribution();
	std::cout << "\n0: Kolmogorov Distance between PU and original: ";
	errors.push_back(kolmogorovDistance(&pu, original));
	counters.push_back(0);
	std::cout << errors[0];
	std::cout << std::endl << std::endl;

	RandomGenerator random;
	int i;
	for (i = 0; i < 100; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv = rv + (*new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "PU time: " << clock() - timer << "\n";
		std::cout << i + 1 << ": ";
		std::cout << "Kolmogorov Distance between PU and original: ";
		errors.push_back(kolmogorovDistance(rv.getDistribution(), original));
		counters.push_back(i + 1);
		std::cout << errors[i + 1];
		std::cout << std::endl << std::endl;
	}
//	plot.addRV(*new RandomVariable(original)); // plot the last only
//	plot.addRV(rv);
//	plot.plotBuffered(PDF);
}

// conduct a series of computations with known results
// to see how PG approximation is affected
void Experiments::computationsPG(std::vector<double> & counters, std::vector<
		double> & errors)
{
	PiecewiseBase::setFixedNumberOfComponents(100);

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	PiecewiseGaussian pg(new Gaussian);

	Gaussian * original = (Gaussian *) rv.getDistribution();
	std::cout << "\n0: Kolmogorov Distance between PG and original: ";
	errors.push_back(kolmogorovDistance(&pg, original));
	counters.push_back(0);
	std::cout << errors[0];
	std::cout << std::endl << std::endl;

	RandomGenerator random;
	int i;
	for (i = 0; i < 1; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv = rv + (*new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "PG time: " << clock() - timer << "\n";
		std::cout << i + 1 << ": ";
		std::cout << "Kolmogorov Distance between PG and original: ";
		errors.push_back(kolmogorovDistance(rv.getDistribution(), original));
		counters.push_back(i + 1);
		std::cout << errors[i + 1];
		std::cout << std::endl << std::endl;
	}
	plot.addRV(*new RandomVariable(original)); // plot the last only
	plot.addRV(rv);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

// conduct a series of computations with known results
// to see how MC is affected
void Experiments::computationsMC(std::vector<double> & counters, std::vector<
		double> & errors)
{
	RandomVariable::setNumberOfSamplesMC(10000);
	RandomVariable::setMonteCarloFlag(1);

	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	Gaussian * original = new Gaussian;

	std::cout << std::endl;
	RandomGenerator random;
	int i;
	for (i = 0; i < 3; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv = rv + (*new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "PU time: " << clock() - timer << "\n";
		std::cout << i + 1 << ": ";
		std::cout << "Kolmogorov Distance between MC and original: ";
		errors.push_back(kolmogorovDistance(rv.getDistribution(), original));
		counters.push_back(i + 1);
		std::cout << errors[i + 1];
		std::cout << std::endl << std::endl;
	}
	plot.addRV(*new RandomVariable(original)); // plot the last only
	plot.addRV(rv);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::depedencyMC()
{
	RandomVariable::setMonteCarloFlag(1);
	RandomVariable::setNumberOfSamplesMC(1000);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;

	RandomVariable a = new Gaussian, b = new Gaussian;
	RandomVariable c, d;

	c = a + a;
	d = 2 * a;

	plot.addRV(c);
	plot.addRV(d);
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
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(1);
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Uniform(2, 4);
	RandomVariable r2 = new Uniform(3, 6);
	RandomVariable r3 = min(r1, r2);

	RandomVariable::setMonteCarloFlag(1);
	RandomVariable r4 = min(r1, r2);

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
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Gaussian(-2, 4);
	RandomVariable r2 = new Gaussian(3, 6);
	RandomVariable r3 = new MaxOfGaussians(Gaussian(-2, 4), Gaussian(3, 6));

	RandomVariable::setMonteCarloFlag(1);
	RandomVariable r4 = max(r1, r2);

//	plot.addRV(r1);
//	plot.addRV(r2);
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

	fx_a = pow(sqrt(arg1->pdf(x)) - sqrt(arg2->pdf(x)), 2);
	for (i = 0; i < accuracy; i++)
	{
		fx_b = pow(sqrt(arg1->pdf(x + step)) - sqrt(arg2->pdf(x + step)), 2);
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return (result / 2);
}

double Experiments::euclideanDistancePDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	double diff = arg1->pdf(x) - arg2->pdf(x);
	fx_a = diff * diff;
	for (i = 0; i < accuracy; i++)
	{
		diff = arg1->pdf(x + step) - arg2->pdf(x + step);
		fx_b = diff * diff;
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return sqrt(result);
}

double Experiments::manhattanDistancePDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	fx_a = std::abs(arg1->pdf(x) - arg2->pdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(arg1->pdf(x + step) - arg2->pdf(x + step));
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return result;
}


double Experiments::euclideanDistanceCDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	double diff = arg1->cdf(x) - arg2->cdf(x);
	fx_a = diff * diff;
	for (i = 0; i < accuracy; i++)
	{
		diff = arg1->cdf(x + step) - arg2->cdf(x + step);
		fx_b = diff * diff;
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return sqrt(result);
}

double Experiments::manhattanDistanceCDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	fx_a = std::abs(arg1->cdf(x) - arg2->cdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(arg1->cdf(x + step) - arg2->cdf(x + step));
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return result;
}
