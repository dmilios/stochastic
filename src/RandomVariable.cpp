/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"

#include "utilities/exceptions.h"
#include "utilities/RandomGenerator.h"
#include "algorithms/PiecewiseUniform.h"
#include "algorithms/PiecewiseGaussian.h"
#include "distributions/EmpiricalDistribution.h"
#include "intermediateResults/MinOfDistributions.h"
#include "intermediateResults/MaxOfDistributions.h"
#include "distributions/DeltaDistribution.h"
#include "intermediateResults/InverseRV_Distribution.h"
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <stdexcept>
#include <ctime>

namespace stochastic
{

GraphRV RandomVariable::graph;
RandomVariableAlgorithm * RandomVariable::algorithm = new PiecewiseUniform(100);

/*
 * static method
 */

void RandomVariable::setAlgorithm(RandomVariableAlgorithm * alg)
{
	algorithm = alg;
	algorithm->setRandomVariableGraph(&graph);
}

/*
 *
 * Constructors
 *
 * */

RandomVariable::RandomVariable()
{
	this->distribution = 0;
}

RandomVariable::RandomVariable(Distribution * distribution)
{
	static RandomGenerator gen;

	this->distribution = distribution;
	std::stringstream idStream;
	idStream << gen.nextDouble() + clock();
	this->randomVariableID = idStream.str();
	graph.addRandomVariable(*this, idStream.str());
}

RandomVariable& RandomVariable::operator=(RandomVariable rv)
{
	if (this != &rv)
	{
		this->distribution = rv.distribution;
		this->randomVariableID = rv.randomVariableID;
	}
	return *this;
}

RandomVariable::~RandomVariable()
{
}

/*
 *
 * methods
 *
 * */

std::string RandomVariable::getRandomVariableID() const
{
	return this->randomVariableID;
}

Distribution * RandomVariable::getDistribution() const
{
	return this->distribution;
}

void RandomVariable::pdfOutline(int accuracy, std::vector<double> & x,
		std::vector<double> & fx)
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

void RandomVariable::cdfOutline(int accuracy, std::vector<double> & x,
		std::vector<double> & fx)
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

void RandomVariable::quantileOutline(int accuracy, std::vector<double> & x,
		std::vector<double> & fx)
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
	std::vector<double> samples = distribution->sample(n);

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

	RandomVariable result = algorithm->calculateSum(*this, rightarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, rightarg);
	graph.setOperationTypeFor(result, SUM);
	return result;
}

RandomVariable RandomVariable::operator -(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	RandomVariable result = algorithm->calculateDifference(*this, rightarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, rightarg);
	graph.setOperationTypeFor(result, DIFFERENCE);
	return result;
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

	RandomVariable result = algorithm->calculateProduct(*this, rightarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, rightarg);
	graph.setOperationTypeFor(result, PRODUCT);
	return result;
}

RandomVariable RandomVariable::operator /(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	RandomVariable result = algorithm->calculateRatio(*this, rightarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, rightarg);
	graph.setOperationTypeFor(result, RATIO);
	return result;
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

	RandomVariable result = algorithm->calculateMin(*this, secondarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, secondarg);
	graph.setOperationTypeFor(result, MIN);
	return result;
}

// The first argument is 'this' object
RandomVariable RandomVariable::max(RandomVariable & secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	RandomVariable result = algorithm->calculateMax(*this, secondarg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, secondarg);
	graph.setOperationTypeFor(result, MAX);
	return result;
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
	RandomVariable result = algorithm->calculateSum(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, SUM);
	return result;
}

RandomVariable operator +(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg + c_arg;
}

RandomVariable RandomVariable::operator -(double c_arg)
{
	RandomVariable result = algorithm->calculateDifference(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, DIFFERENCE);
	return result;
}

RandomVariable operator -(double c_arg, RandomVariable & rv_arg)
{
	RandomVariable result =
			rv_arg.algorithm->calculateDifference(c_arg, rv_arg);
	RandomVariable::graph.setParent1For(result, new DeltaDistribution(c_arg));
	RandomVariable::graph.setParent2For(result, rv_arg);
	RandomVariable::graph.setOperationTypeFor(result, DIFFERENCE);
	return result;
}

RandomVariable RandomVariable::operator *(double c_arg)
{
	if (!c_arg)
		return RandomVariable();
	RandomVariable result = algorithm->calculateProduct(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, PRODUCT);
	return result;
}

RandomVariable operator *(double c_arg, RandomVariable & rv_arg)
{
	return rv_arg * c_arg;
}

RandomVariable RandomVariable::operator /(double c_arg)
{
	if (!c_arg)
		return RandomVariable();

	RandomVariable result = algorithm->calculateRatio(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, RATIO);
	return result;
}

RandomVariable operator /(double c_arg, RandomVariable & rv_arg)
{
	if (!c_arg)
		return RandomVariable();
	RandomVariable result = rv_arg.algorithm->calculateRatio(c_arg, rv_arg);
	RandomVariable::graph.setParent1For(result, new DeltaDistribution(c_arg));
	RandomVariable::graph.setParent2For(result, rv_arg);
	RandomVariable::graph.setOperationTypeFor(result, RATIO);
	return result;
}

RandomVariable RandomVariable::min(double c_arg)
{
	RandomVariable result = algorithm->calculateMin(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, MIN);
	return result;
}

RandomVariable RandomVariable::max(double c_arg)
{
	RandomVariable result = algorithm->calculateMax(*this, c_arg);
	graph.setParent1For(result, *this);
	graph.setParent2For(result, new DeltaDistribution(c_arg));
	graph.setOperationTypeFor(result, MAX);
	return result;
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
