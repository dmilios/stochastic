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
	PiecewiseBase::setFixedNumberOfComponents(100);

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
	std::cout << "PG time: " << clock() - timer << "\n";

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
	Gnuplot::setAccuracy(100);
	Gnuplot plot;
	long int timer;

	std::vector <MixtureComponent *> c;
	std::vector <double> w;
	c.push_back(new Gaussian(-2, 1));
	w.push_back(1);
	c.push_back(new Gaussian(4, 1.5));
	w.push_back(1);
	c.push_back(new Gaussian(24, 2));
	w.push_back(1);
	MixtureModel mm(c, w); // to test MM

	InverseRV_Distribution inv(new Gaussian); // to test long tailed


	RandomVariable rv = new Gaussian;
	RandomVariable pu = new PiecewiseUniform(rv.getDistribution());
	RandomVariable pg = new PiecewiseGaussian(rv.getDistribution());


	RandomVariable a(new Gaussian), b(new Gaussian);
	timer = clock();
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	a + b;
	std::cout << "PU sum time (ms): " << 1000 * (double) (clock() - timer)
			/ CLOCKS_PER_SEC << "\n";

	timer = clock();
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
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
	std::cout << manhattanDistanceCDF(rv.getDistribution(), pu.getDistribution());
	std::cout << std::endl;
	std::cout << "CDF Distance between PG and original: ";
	std::cout << manhattanDistanceCDF(rv.getDistribution(), pg.getDistribution());
	std::cout << std::endl << std::endl;

	plot.addRV(rv);
	plot.addRV(pu);
	plot.addRV(pg);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::computationsEvolution()
{
	Gnuplot plot;
	std::vector <double> iteration_numbers;
	std::vector <double> errors;

	PiecewiseBase::setFixedNumberOfComponents(200);


	Experiments::computationsPU(iteration_numbers, errors);
	plot.addCurve(OTHER, "KL_Divergence Evolution for PU New",
			iteration_numbers, errors);

	std::cout << std::endl << "--------------------------------" << std::endl;

//	Experiments::computationsPG(iteration_numbers, errors);
//	plot.addCurve(OTHER, "KL_Divergence Evolution for PG", iteration_numbers,
//			errors);

	std::cout << std::endl << "--------------------------------" << std::endl;

	PiecewiseUniform::useold = 1;
	Experiments::computationsPU(iteration_numbers, errors);
	plot.addCurve(OTHER, "KL_Divergence Evolution for PU Old",
			iteration_numbers, errors);

	plot.plotBuffered(OTHER);
}

// conduct a series of computations with known results
// to see how PU approximation is affected
void Experiments::computationsPU(std::vector<double> & counters, std::vector<
		double> & errors)
{
	RandomVariable::setApproximatorType(new PiecewiseUniform);
	Gnuplot::setAccuracy(1000);
//	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	PiecewiseUniform pu(new Gaussian);

	Gaussian * original = (Gaussian *) rv.getDistribution();
	std::cout << "\n0: KL_Divergence between PU and original: ";
	errors.push_back(KL_Divergence(&pu, original));
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
		std::cout << "KL_Divergence between PU and original: ";
		errors.push_back(KL_Divergence(rv.getDistribution(), original));
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
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	RandomVariable rv = new Gaussian;
	PiecewiseGaussian pg(new Gaussian);

	Gaussian * original = (Gaussian *) rv.getDistribution();
	std::cout << "\n0: KL_Divergence between PG and original: ";
	errors.push_back(KL_Divergence(&pg, original));
	counters.push_back(0);
	std::cout << errors[0];
	std::cout << std::endl << std::endl;

	RandomGenerator random;
	int i;
	for (i = 0; i < 10; i++)
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
		std::cout << "KL_Divergence between PG and original: ";
		errors.push_back(KL_Divergence(rv.getDistribution(), original));
		counters.push_back(i + 1);
		std::cout << errors[i + 1];
		std::cout << std::endl << std::endl;
	}
//	plot.addRV(*new RandomVariable(original)); // plot the last only
//	plot.addRV(rv);
//	plot.plotBuffered(PDF);
//	plot.plotBuffered(CDF);
}

// conduct a series of computations with known results
// to see how MC is affected
void Experiments::computationsMC(std::vector<double> & counters, std::vector<
		double> & errors)
{
	RandomVariable::setNumberOfSamplesMC(1000);
	RandomVariable::setMonteCarloFlag(1);

	Gnuplot::setAccuracy(1000);
	Gnuplot plot;
	long int timer;
	counters.clear();
	errors.clear();

	int N = 50;
	RandomVariable rv[N];
	rv[0] = new Gaussian;
	Gaussian * original = new Gaussian;

	std::cout << std::endl;
	RandomGenerator random;
	int i;
	for (i = 1; i < N; i++)
	{
		double curr_mean = original->getMean();
		double curr_var = original->getVariance();

		double mean_added = random.nextDouble(-10, 10);
		double var_added = random.nextDouble(0.001, 5);
		original = new Gaussian(curr_mean + mean_added, curr_var + var_added);

		timer = clock();
		rv[i] = rv[i - 1] + (*new RandomVariable(new Gaussian(mean_added, var_added)));
		std::cout << "PU time: " << clock() - timer << "\n";
		std::cout << i << ": ";
		std::cout << "Kolmogorov Distance between MC and original: ";
		errors.push_back(kolmogorovDistance(rv[i].getDistribution(), original));
		counters.push_back(i);
		std::cout << errors[i];
		std::cout << std::endl << std::endl;
	}
	plot.addRV(*new RandomVariable(original)); // plot the last only
	plot.addRV(rv[N - 1]);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::dependencyMC()
{
	RandomVariable::setMonteCarloFlag(1);
	RandomVariable::setNumberOfSamplesMC(1000);
	Gnuplot::setAccuracy(1000);
	Gnuplot plot;

	RandomVariable a = new Gaussian, b = new Gaussian;
	RandomVariable c, d;

	c = a + a;
//	a = new Uniform(7, 14);
	d = c + b;

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

void Experiments::minmaxTests()
{
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;

	RandomVariable r1 = new Gaussian(0, 1);
	RandomVariable r2 = new Uniform(-2, 1);
	RandomVariable r3 = new MinOfDistributions(r1.getDistribution(),
			r2.getDistribution());

	RandomVariable::setMonteCarloFlag(0);
	RandomVariable r4 = min(r1, r2);

//	plot.addRV(r1);
//	plot.addRV(r2);
	plot.addRV(r3);
	plot.addRV(r4);

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::testProduct()
{
	RandomVariable::setNumberOfSamplesMC(10000);
	PiecewiseBase::setFixedNumberOfComponents(100);
	Gnuplot::setAccuracy(1000);

	Gnuplot plot;
	long int timer;

	RandomVariable r1 = new Gaussian(6, 0.3);
	RandomVariable r2 = new Gaussian(-5, 1);


	RandomVariable::setApproximatorType(new PiecewiseUniform);
	timer = clock();
	RandomVariable r3 = r1 + r2;
	std::cout << "PU time: " << clock() - timer << "\n\n";

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	timer = clock();
	RandomVariable r4 = r1 + r2;
	std::cout << "PG time: " << clock() - timer << "\n\n";

	RandomVariable::setMonteCarloFlag(1);
	timer = clock();
	RandomVariable r5 = r1 + r2;
	std::cout << "MC time: " << clock() - timer << "\n\n";


	std::cout << "Kolmogorov Distance between PU and MC: ";
	std::cout << kolmogorovDistance(r3.getDistribution(), r5.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PG and MC: ";
	std::cout << kolmogorovDistance(r4.getDistribution(), r5.getDistribution());
	std::cout << std::endl;

	plot.addRV(r3);
	plot.addRV(r4);

	std::cout << "Time: " << clock() << "\n";
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);

	/*
	double m1 = 0;
	double v1 = 1;
	double m2 = 0;
	double v2 = 1;
	RandomVariable r4 = new Gaussian(m2/m1 + v1*m2/(m1*m1*m1),
							v1*m2*m2 / (m1*m1*m1*m1) + v2 / (m1*m1));
	*/
}

/*
 *
 *
 *
 *
 * Distance metrics
 *
 *
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

/* @brief Computes KL-Div(P||Q) */
double Experiments::KL_Divergence(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 100000;
	int i;
	double sum = 0;
	double x;
	for (i = 0; i < accuracy; i++)
	{
		x = arg1->nextSample();
		double tmp = log(arg1->pdf(x) / arg2->pdf(x));
		if (tmp != INFINITY)
			sum += tmp;
	}
	return sum / accuracy;
}

double Experiments::hellingerDistance(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 100;
	int i;
	double x;

	double result = 0;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;

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

void Experiments::testDistances()
{
	using namespace std;

	Gaussian a;
	Gaussian b(1);

	cout << hellingerDistance(&a, &b) << endl;
}





/*
 *
 *
 *
 *  THESIS EXPERIMENTS
 *
 * */

void Experiments::thesis_3_4_1()
{
	PiecewiseBase::setFixedNumberOfComponents(10);
	Gnuplot::setAccuracy(100);
	Gnuplot plot;

	RandomVariable rv_original = new Gaussian;
	RandomVariable rv_puniform = new PiecewiseUniform(new Gaussian);

	plot.addRV(rv_original);
	plot.addRV(rv_puniform);

	plot.setTexFile(
			"/home/dimitrios/Documents/academic/MSc/thesis/tex/fig_approx_puni");
	plot.plotBuffered(PDF);
}

void Experiments::thesis_3_4_2()
{
	PiecewiseBase::setFixedNumberOfComponents(10);
	Gnuplot::setAccuracy(100);
	Gnuplot plot;

	RandomVariable rv_original = new Uniform;
	RandomVariable rv_puniform = new PiecewiseGaussian(new Uniform);

	plot.addRV(rv_original);
	plot.addRV(rv_puniform);

	plot.setTexFile(
			"/home/dimitrios/Documents/academic/MSc/thesis/tex/fig_approx_pnorm");
	plot.plotBuffered(PDF);
}

void Experiments::thesis_4_2_1()
{
	Gnuplot::setAccuracy(100);
	Gnuplot plot;
	long int timer;


	RandomVariable rv_original = new Gaussian;
	RandomVariable rv_puniform;
	RandomVariable rv_pgaussian;

	vector<double> componentNumber;
	componentNumber.push_back(10);
	componentNumber.push_back(15);
	componentNumber.push_back(20);
	componentNumber.push_back(30);
	componentNumber.push_back(40);
	componentNumber.push_back(50);
	componentNumber.push_back(60);
	componentNumber.push_back(70);
	componentNumber.push_back(80);
	componentNumber.push_back(90);
	componentNumber.push_back(100);
	componentNumber.push_back(110);
	componentNumber.push_back(120);
	componentNumber.push_back(150);


	vector <double> times_pu;
	vector <double> kl_div_pu;
	vector <double> times_pg;
	vector <double> kl_div_pg;

	unsigned int i;
	for (i = 0; i < componentNumber.size(); i++)
	{
		PiecewiseBase::setFixedNumberOfComponents(componentNumber[i]);
		std::cout << "--------------------------------------------\n";
		std::cout << "\nNumber of Components: " << componentNumber[i];
		std::cout << "\n";


		// Approximate both ways
		rv_puniform = new PiecewiseUniform(rv_original.getDistribution());
		rv_pgaussian = new PiecewiseGaussian(rv_original.getDistribution());


		// ----- Perform a computation
		RandomVariable a(new Gaussian), b(new Gaussian);
		timer = clock();
		RandomVariable::setApproximatorType(new PiecewiseUniform);
		a + b;
		timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
		std::cout << "PU sum time (ms): " << timer << "\n";

		times_pu.push_back(timer); // store the timers to plot them later

		timer = clock();
		RandomVariable::setApproximatorType(new PiecewiseGaussian);
		a + b;
		timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
		std::cout << "PG sum time (ms): " << timer << "\n\n";

		times_pg.push_back(timer); // store the timers to plot them later



		std::cout << "KL Divergence between PU and original: ";
		std::cout << KL_Divergence(rv_original.getDistribution(),
				rv_puniform.getDistribution());
		std::cout << std::endl;
		kl_div_pu.push_back(KL_Divergence(rv_original.getDistribution(),
				rv_puniform.getDistribution()));

		std::cout << "KL Divergence between PG and original: ";
		std::cout << KL_Divergence(rv_original.getDistribution(),
				rv_pgaussian.getDistribution());
		std::cout << std::endl << std::endl;
		kl_div_pg.push_back(KL_Divergence(rv_original.getDistribution(),
				rv_pgaussian.getDistribution()));
	}

	plot.addCurve(OTHER, "Time (ms) for Piecewise Uniform",
				componentNumber, times_pu);
	plot.addCurve(OTHER, "Time (ms) for Piecewise Gaussian",
				componentNumber, times_pg);

	plot.setTexFile("/home/dimitrios/Documents/academic/MSc/thesis/tex/fig_acc");
	plot.plotBuffered(OTHER);
	plot.clearBuffer();

	plot.addCurve(OTHER, "KL Divergence for Piecewise Uniform",
			componentNumber, kl_div_pu);
	plot.addCurve(OTHER, "KL Divergence for Piecewise Gaussian",
			componentNumber, kl_div_pg);

	plot.setTexFile("/home/dimitrios/Documents/academic/MSc/thesis/tex/fig_eff");
	plot.plotBuffered(OTHER);
}

void Experiments::thesis_4_2_2__1()
{
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setNumberOfSamplesMC(2000);
	Gnuplot::setAccuracy(100);

	Gnuplot plot;
	long int timer;

	RandomVariable rv_initial = new Gaussian(-4, 2);
	RandomVariable rv_result = new Gaussian(6, 0.5);
	RandomVariable rv_pu;
	RandomVariable rv_pg;
	RandomVariable rv_mc;

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	timer = clock();
	rv_pu = -rv_initial / 2 + 4;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PU time (ms): " << timer << "\n\n";

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	timer = clock();
	rv_pg = -rv_initial / 2 + 4;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PG time (ms): " << timer << "\n\n";

	RandomVariable::setMonteCarloFlag(1);
	timer = clock();
	rv_mc = -rv_initial / 2 + 4;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "MC time (ms): " << timer << "\n\n";


	std::cout << "KL Divergence between PU and original: ";
	std::cout << KL_Divergence(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "KL Divergence between PG and original: ";
	std::cout << KL_Divergence(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;
	//-----------------------------------
	std::cout << "Kolmogorov Distance between MC and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PG and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;
	//-----------------------------------
	std::cout << "CDF Distance between MC and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PU and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PG and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;



	plot.addRV(rv_result);
	plot.addRV(rv_pu);
	plot.addRV(rv_pg);
	plot.addRV(rv_mc);
	plot.plotBuffered(PDF);
	plot.plotBuffered(CDF);
}

void Experiments::thesis_4_2_2__2()
{
	PiecewiseBase::setFixedNumberOfComponents(100);
	Gnuplot::setAccuracy(50);

	Gnuplot plot;
	long int timer;

	RandomVariable rv_initial = new Gaussian(4, 1);
	RandomVariable rv_result;
	RandomVariable rv_pu;
	RandomVariable rv_pg;
	RandomVariable rv_mc;


	RandomVariable::setMonteCarloFlag(1);
	RandomVariable::setNumberOfSamplesMC(100000);
	rv_result = max(rv_initial, 3);



	// reset and go
	RandomVariable::setNumberOfSamplesMC(2000);
	RandomVariable::setMonteCarloFlag(0);

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	timer = clock();
	rv_pu = max(rv_initial, 3);
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PU time (ms): " << timer << "\n\n";

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	timer = clock();
	rv_pg = max(rv_initial, 3);
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PG time (ms): " << timer << "\n\n";

	RandomVariable::setMonteCarloFlag(1);
	timer = clock();
	rv_mc = max(rv_initial, 3);
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "MC time (ms): " << timer << "\n\n";


	//-----------------------------------
	std::cout << "Kolmogorov Distance between MC and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PU and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PG and original: ";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;
	//-----------------------------------
	std::cout << "CDF Distance between MC and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PU and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PG and original: ";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;



	plot.addRV(rv_result);
	plot.addRV(rv_pu);
	plot.addRV(rv_pg);
//	plot.addRV(rv_mc);

	plot.setTexFile("/home/dimitrios/Documents/academic/MSc/thesis/tex/fig_ex_max1");
	plot.plotBuffered(PDF);
}

void Experiments::thesis_4_2_3()
{
	PiecewiseBase::setFixedNumberOfComponents(100);
	RandomVariable::setNumberOfSamplesMC(8000);
	Gnuplot::setAccuracy(100);

	Gnuplot plot;
	long int timer;

	RandomVariable rv_1 = new Gaussian(2, 1);
	RandomVariable rv_2 = new Gaussian(3, 2);
	RandomVariable rv_result = new Gaussian(5, 3);

	RandomVariable rv_pu_old;
	RandomVariable rv_pu;
	RandomVariable rv_pg;
	RandomVariable rv_mc;

	RandomVariable::setApproximatorType(new PiecewiseUniform);
	PiecewiseUniform::useold = 1;
	timer = clock();
	rv_pu_old = rv_1 + rv_2;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PU time (ms): " << timer << "\n\n";

	PiecewiseUniform::useold = 0;
	timer = clock();
	rv_pu = rv_1 + rv_2;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PU time (ms): " << timer << "\n\n";

	RandomVariable::setApproximatorType(new PiecewiseGaussian);
	timer = clock();
	rv_pg = rv_1 + rv_2;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "PG time (ms): " << timer << "\n\n";

	RandomVariable::setMonteCarloFlag(1);
	timer = clock();
	rv_mc = rv_1 + rv_2;
	timer = 1000 * (double) (clock() - timer) / CLOCKS_PER_SEC;
	std::cout << "MC time (ms): " << timer << "\n\n";


	std::cout << "KL Divergence between OLD PU and original: \t\t";
	std::cout << KL_Divergence(rv_result.getDistribution(),
			rv_pu_old.getDistribution());
	std::cout << std::endl;

	std::cout << "KL Divergence between PU and original: \t\t\t";
	std::cout << KL_Divergence(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "KL Divergence between PG and original: \t\t\t";
	std::cout << KL_Divergence(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl << std::endl;
	//-----------------------------------
	std::cout << "Kolmogorov Distance between MC and original: \t\t";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between OLD PU and original: \t";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pu_old.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PU and original: \t\t";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "Kolmogorov Distance between PG and original: \t\t";
	std::cout << kolmogorovDistance(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl << std::endl;
	//-----------------------------------
	std::cout << "CDF Distance between MC and original: \t\t\t";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_mc.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between OLD PU and original: \t\t";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pu_old.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PU and original: \t\t\t";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pu.getDistribution());
	std::cout << std::endl;

	std::cout << "CDF Distance between PG and original: \t\t\t";
	std::cout << manhattanDistanceCDF(rv_result.getDistribution(),
			rv_pg.getDistribution());
	std::cout << std::endl;



	plot.addRV(rv_result);
	plot.addRV(rv_pu_old);
	plot.addRV(rv_pu);
	plot.addRV(rv_pg);
	plot.addRV(rv_mc);
	plot.plotBuffered(PDF);
}
