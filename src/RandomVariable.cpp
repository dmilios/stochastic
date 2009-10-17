/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"

#include "utilities/exceptions.h"
#include "algorithms/PiecewiseUniform.h"
#include "algorithms/PiecewiseGaussian.h"
#include "distributions/EmpiricalDistribution.h"
#include "intermediateResults/MinOfDistributions.h"
#include "intermediateResults/MaxOfDistributions.h"
#include "distributions/DeltaDistribution.h"
#include "intermediateResults/InverseRV_Distribution.h"
#include <fstream>
#include <string>
#include <typeinfo>
#include <stdexcept>

namespace stochastic {

RandomVariableAlgorithm * RandomVariable::algorithm = new PiecewiseUniform(100);
int RandomVariable::monteCarloFlag = 0;
int RandomVariable::numberOfSamplesMC = 10000;

std::map <RandomVariable *, double> RandomVariable::samplesCollection;

/*
 * static methods
 */

void  RandomVariable::setAlgorithm(RandomVariableAlgorithm * alg)
{
	monteCarloFlag = 0;
	algorithm = alg;
}

void RandomVariable::setMonteCarlo(int number_of_samples)
{
	monteCarloFlag = 1;
	numberOfSamplesMC = number_of_samples;
}

/*
 *
 * Constructors
 *
 * */

RandomVariable::RandomVariable()
{
	this->distribution = 0;
	precededOperation = NONE;
	parrent1 = 0;
	parrent2 = 0;
}

RandomVariable::RandomVariable(Distribution * distribution)
{
	this->setDistribution(distribution);
	precededOperation = NONE;
	parrent1 = 0;
	parrent2 = 0;
}

RandomVariable::~RandomVariable()
{
}

/*
 *
 * methods
 *
 * */

void RandomVariable::setDistribution(Distribution * distribution)
{
	this->distribution = distribution;
}

Distribution * RandomVariable::getDistribution()
{
	return this->distribution;
}

void RandomVariable::pdfOutline(int accuracy, std::vector <double> & x,
		std::vector <double> & fx)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	x.clear();
	fx.clear();
	double x_curr;
	double start = this->distribution->getLeftMargin();
	double end = this->distribution->getRightMargin();
	double step = (end - start) / (double) accuracy;
	double margin = (end - start) / 10;
	for (x_curr = start - margin; x_curr < end + margin; x_curr = x_curr + step)
	{
		x.push_back(x_curr);
		fx.push_back(this->distribution->pdf(x_curr));
	}
	if (start == end) // delta distribution
	{
		x.push_back(start);
		fx.push_back(1); // actually infinity
	}
}

void RandomVariable::cdfOutline(int accuracy, std::vector <double> & x,
		std::vector <double> & fx)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	x.clear();
	fx.clear();
	double x_curr;
	double start = this->distribution->getLeftMargin();
	double end = this->distribution->getRightMargin();
	double step = (end - start) / (double) accuracy;
	double margin = (end - start) / 10;
	for (x_curr = start - margin; x_curr < end + margin; x_curr = x_curr + step)
	{
		x.push_back(x_curr);
		fx.push_back(this->distribution->cdf(x_curr));
	}
}

void RandomVariable::quantileOutline(int accuracy, std::vector <double> & x,
		std::vector <double> & fx)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	x.clear();
	fx.clear();
	double p_curr;
	double start = 0;
	double end = 1;
	double step = (end - start) / (double) accuracy;
	for (p_curr = start; p_curr < end; p_curr = p_curr + step)
	{
		x.push_back(p_curr);
		fx.push_back(this->distribution->quantile(p_curr));
	}
}

void RandomVariable::produceFileOfSamples(int n)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	std::string fileName(distribution->getName());
	fileName.append(".txt");

	std::ofstream output;
	std::vector <double> samples = distribution->sample(n);

	output.open(fileName.c_str());
	output << "# name: x \n";
	output << "# type: matrix \n";
	output << "# rows:" << (int) samples.size() << "\n";
	output << "# columns: 1 \n";
	unsigned int i;
	for (i = 0; i < samples.size(); i++)
		output << samples[i] << " \n";
	output.close();
}

/*
 *
 *
 *
 *
 *
 * --- Overload Binary Operators: '+', '-', '*', '/'
 *
 *
 *
 */

RandomVariable RandomVariable::operator +(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(SUM, this, & rightarg);

	return algorithm->calculateSum(this->distribution, rightarg.distribution);
}

RandomVariable RandomVariable::operator -(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(DIFFERENCE, this, & rightarg);

	return algorithm->calculateDifference(this->distribution, rightarg.distribution);
}

// Implementation of the negative sign for a RV
RandomVariable operator -(RandomVariable rv_arg)
{
	return rv_arg * (-1);
}

RandomVariable RandomVariable::operator *(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(PRODUCT, this, & rightarg);

	return algorithm->calculateProduct(this->distribution, rightarg.distribution);
}

RandomVariable RandomVariable::operator /(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(RATIO, this, & rightarg);

	return algorithm->calculateRatio(this->distribution, rightarg.distribution);
}

/*
 *
 * --- Define Binary Operators: min, max
 */

// The first argument is 'this' object
RandomVariable RandomVariable::min(RandomVariable & secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(MIN, this, & secondarg);

	return algorithm->calculateMin(this->distribution, secondarg.distribution);
}

// The first argument is 'this' object
RandomVariable RandomVariable::max(RandomVariable & secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return monteCarlo(MAX, this, & secondarg);

	return algorithm->calculateMax(this->distribution, secondarg.distribution);
}


/*
 *
 *
 *
 * Functions of ONE random variable
 *
 *
 * */

RandomVariable RandomVariable::operator +(double c_arg)
{
	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(SUM, this, delta);
	}
	return algorithm->calculateSum(this->distribution, c_arg);
}

RandomVariable operator +(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg + c_arg;
}

RandomVariable RandomVariable::operator -(double c_arg)
{
	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(DIFFERENCE, this, delta);
	}
	return algorithm->calculateDifference(this->distribution, c_arg);
}

RandomVariable operator -(double c_arg, RandomVariable & rv_arg)
{
	if (RandomVariable::monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return RandomVariable::monteCarlo(DIFFERENCE, delta, & rv_arg);
	}
	return rv_arg.algorithm->calculateDifference(c_arg, rv_arg.distribution);
}

RandomVariable RandomVariable::operator *(double c_arg)
{
	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(PRODUCT, this, delta);
	}

	if (!c_arg)
		return RandomVariable();
	return algorithm->calculateProduct(this->distribution, c_arg);
}

RandomVariable operator *(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg * c_arg;
}

RandomVariable RandomVariable::operator /(double c_arg)
{
	if (!c_arg)
		return RandomVariable();

	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(RATIO, this, delta);
	}
	return algorithm->calculateRatio(this->distribution, c_arg);
}

RandomVariable operator /(double c_arg, RandomVariable & rv_arg)
{
	if (RandomVariable::monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return RandomVariable::monteCarlo(RATIO, delta, & rv_arg);
	}

	if (!c_arg)
		return RandomVariable();
	return rv_arg.algorithm->calculateRatio(c_arg, rv_arg.distribution);
}

RandomVariable RandomVariable::min(double c_arg)
{
	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(MIN, this, delta);
	}
	return algorithm->calculateMin(this->distribution, c_arg);
}

RandomVariable RandomVariable::max(double c_arg)
{
	if (monteCarloFlag)
	{
		RandomVariable * delta = new RandomVariable(new DeltaDistribution(c_arg));
		return monteCarlo(MAX, this, delta);
	}
	return algorithm->calculateMax(this->distribution, c_arg);
}

/* ====================================================================
 *
 *
 *
 *
 * Implementation of MonteCarlo
 *
 *
 *
 * ====================================================================
 * */

RandomVariable RandomVariable::monteCarlo(OperationType op,
		RandomVariable * arg1, RandomVariable * arg2)
{
	std::vector<double> produced_data;
	int i;

	for (i = 0; i < numberOfSamplesMC; i++)
	{
		samplesCollection.clear();
		produced_data.push_back(recursiveSampling(op, arg1, arg2));
	}

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = op;
	result.parrent1 = arg1;
	result.parrent2 = arg2;
	return result;
}

double RandomVariable::recursiveSampling(OperationType op,
		RandomVariable * arg1, RandomVariable * arg2)
{
	double sample1;
	double sample2;
	try
	{
		sample1 = samplesCollection.at(arg1);
	}
	catch(std::out_of_range ex)
	{
		if (typeid(* arg1) == typeid(DeltaDistribution))
			sample1 = arg1->getDistribution()->nextSample();
		else if (!arg1->precededOperation)
			sample1 = arg1->getDistribution()->nextSample();
		else
			sample1 = recursiveSampling(arg1->precededOperation,
					arg1->parrent1, arg1->parrent2);
		samplesCollection[arg1] = sample1;
	}
	try
	{
		sample2 = samplesCollection.at(arg2);
	}
	catch(std::out_of_range ex)
	{
		if (typeid(* arg2) == typeid(DeltaDistribution))
			sample2 = arg2->getDistribution()->nextSample();
		else if (!arg2->precededOperation)
			sample2 = arg2->getDistribution()->nextSample();
		else
			sample2 = recursiveSampling(arg2->precededOperation,
					arg2->parrent1, arg2->parrent2);
		samplesCollection[arg2] = sample2;
	}

	switch(op)
	{
		case SUM:
			return sample1 + sample2;
			break;
		case DIFFERENCE:
			return sample1 - sample2;
			break;
		case PRODUCT:
			return sample1 * sample2;
			break;
		case RATIO:
			if (sample2 == 0)
				sample2 = 0.0001;
			return sample1 / sample2;
			break;
		case MIN:
			return std::min<double>(sample1, sample2);
			break;
		case MAX:
			return std::max<double>(sample1, sample2);
			break;
		default:
			break;
	}
	throw 0; // this should never happen
}

/*
 *
 *
 *
 * MINMAX alternative implementations
 *
 * so as to be more intuitive
 *
 *
 * */

// the very same implementation as in RandomVariable::min,
// but this is called in a more intuitive way
RandomVariable min(RandomVariable & firstarg, RandomVariable & secondarg)
{
	return firstarg.min(secondarg);
}

RandomVariable min(RandomVariable & rv_arg, double c_arg)
{
	return rv_arg.min(c_arg);
}

RandomVariable min(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg.min(c_arg);
}


// the very same implementation as in RandomVariable::max,
// but this is called in a more intuitive way
RandomVariable max(RandomVariable & firstarg, RandomVariable & secondarg)
{
	return firstarg.max(secondarg);
}

RandomVariable max(RandomVariable & rv_arg, double c_arg)
{
	return rv_arg.max(c_arg);
}

RandomVariable max(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg.max(c_arg);
}

} // namespace stochastic
