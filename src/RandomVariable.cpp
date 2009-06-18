/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"

#include "exceptions.h"
#include <fstream>
#include <string>

namespace stochastic {

RandomVariable::RandomVariable()
{
	this->distribution = 0;
}

RandomVariable::RandomVariable(Distribution * distribution)
{
	this->setDistribution(distribution);
}

RandomVariable::~RandomVariable()
{
}

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
 * --- Overload Binary Operators: '+', '-', '*', '/'
 */

RandomVariable RandomVariable::operator +(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

RandomVariable RandomVariable::operator -(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

RandomVariable RandomVariable::operator *(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

RandomVariable RandomVariable::operator /(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

/*
 *
 * --- Define Binary Operators: min, max
 */

// The first argument is 'this' object
RandomVariable RandomVariable::min(RandomVariable secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

// The first argument is 'this' object
RandomVariable RandomVariable::max(RandomVariable secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	return RandomVariable();
}

// the very same implementation as in RandomVariable::min,
// but this is called in a more intuitive way
RandomVariable min(RandomVariable firstarg, RandomVariable secondarg)
{
	return firstarg.min(secondarg);
}

// the very same implementation as in RandomVariable::max,
// but this is called in a more intuitive way
RandomVariable max(RandomVariable firstarg, RandomVariable secondarg)
{
	return firstarg.max(secondarg);
}

} // namespace stochastic
