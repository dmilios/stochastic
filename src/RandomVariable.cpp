/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"

#include "exceptions.h"
#include "PiecewiseUniform.h"
#include <fstream>
#include <string>
#include <typeinfo>

namespace stochastic {

PiecewiseBase * RandomVariable::approximator = new PiecewiseUniform;

// static method
void RandomVariable::setApproximatorType(PiecewiseBase * type)
{
	RandomVariable::approximator = type;
}

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
 * --- Overload Binary Operators: '+', '-', '*', '/'
 */

RandomVariable RandomVariable::operator +(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* rightarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(rightarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) rightarg.distribution;

	Distribution * raw = leftDistribution->sum(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable RandomVariable::operator -(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* rightarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(rightarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) rightarg.distribution;

	Distribution * raw = leftDistribution->difference(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

// Implementation of the negative sign for a RV
RandomVariable operator -(RandomVariable rv_arg)
{
	return rv_arg * (-1);
}

RandomVariable RandomVariable::operator *(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* rightarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(rightarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) rightarg.distribution;

	Distribution * raw = leftDistribution->product(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable RandomVariable::operator /(RandomVariable rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* rightarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(rightarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) rightarg.distribution;

	Distribution * raw = leftDistribution->ratio(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
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

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* secondarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(secondarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) secondarg.distribution;

	Distribution * raw = leftDistribution->min(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

// The first argument is 'this' object
RandomVariable RandomVariable::max(RandomVariable secondarg)
{
	if (!distribution || !secondarg.distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseBase * leftDistribution;
	PiecewiseBase * rightDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;
	if (typeid(* secondarg.distribution) != typeid(* approximator))
		rightDistribution = approximator->fit(secondarg.distribution);
	else
		rightDistribution = (PiecewiseBase *) secondarg.distribution;

	Distribution * raw = leftDistribution->max(rightDistribution);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}


/*
 *
 *
 * Functions of ONE random variable
 *
 * */

RandomVariable RandomVariable::operator +(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	Distribution * raw = leftDistribution->sum(c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable operator +(double c_arg, RandomVariable rv_arg)
{
	return rv_arg + c_arg;
}

RandomVariable RandomVariable::operator -(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	// just use the sum with negative sign
	Distribution * raw = leftDistribution->sum(-c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable operator -(double c_arg, RandomVariable rv_arg)
{
	PiecewiseBase * distr_arg;
	if (typeid(* rv_arg.distribution) != typeid(* rv_arg.approximator))
		distr_arg = rv_arg.approximator->fit(rv_arg.distribution);
	else
		distr_arg = (PiecewiseBase *) rv_arg.distribution;

	/* a change of sign for a RV would require:
	   1. multiplication with '-1'
	   2. sum with the 'c_arg'
	   So, more efficient to implement
		   the difference from constant directly */
	Distribution * raw = distr_arg->differenceFrom(c_arg);
	PiecewiseBase * result = rv_arg.approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable RandomVariable::operator *(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	Distribution * raw = leftDistribution->product(c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable operator *(double c_arg, RandomVariable rv_arg)
{
	return rv_arg * c_arg;
}

RandomVariable RandomVariable::operator /(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	// just multiply with the inverse
	Distribution * raw = leftDistribution->product(1 / c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable operator /(double c_arg, RandomVariable rv_arg)
{
	PiecewiseBase * distr_arg;
	if (typeid(* rv_arg.distribution) != typeid(* rv_arg.approximator))
		distr_arg = rv_arg.approximator->fit(rv_arg.distribution);
	else
		distr_arg = (PiecewiseBase *) rv_arg.distribution;

	/*
	 * Need to implement this, so as to define the inverse
	 * of a random variable
	 * */
	Distribution * raw = distr_arg->denominatorOf(c_arg);
	PiecewiseBase * result = rv_arg.approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable RandomVariable::min(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	Distribution * raw = leftDistribution->min(c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
}

RandomVariable RandomVariable::max(double c_arg)
{
	PiecewiseBase * leftDistribution;
	if (typeid(* this->distribution) != typeid(* approximator))
		leftDistribution = approximator->fit(this->distribution);
	else
		leftDistribution = (PiecewiseBase *) this->distribution;

	Distribution * raw = leftDistribution->max(c_arg);
	PiecewiseBase * result = approximator->fit(raw);
	return RandomVariable(result);
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

RandomVariable min(RandomVariable rv_arg, double c_arg)
{
	return rv_arg.min(c_arg);
}

RandomVariable max(RandomVariable rv_arg, double c_arg)
{
	return rv_arg.max(c_arg);
}

RandomVariable min(double c_arg, RandomVariable rv_arg)
{
	return rv_arg.min(c_arg);
}

RandomVariable max(double c_arg, RandomVariable rv_arg)
{
	return rv_arg.max(c_arg);
}

} // namespace stochastic
