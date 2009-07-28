/*
 * RandomVariable.cpp
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "RandomVariable.h"

#include "exceptions.h"
#include "PiecewiseUniform.h"
#include "EmpiricalDistribution.h"
#include <fstream>
#include <string>
#include <typeinfo>
#include <stdexcept>

namespace stochastic {

PiecewiseBase * RandomVariable::approximator = new PiecewiseUniform;
int RandomVariable::monteCarloFlag = 0;
int RandomVariable::numberOfSamplesMC = 10000;

std::map <RandomVariable *, double> RandomVariable::samplesCollection;

/*
 * static methods
 */
void RandomVariable::setApproximatorType(PiecewiseBase * type)
{
	RandomVariable::approximator = type;
}

// static method: 0 -> not use MC, otherwise -> use MC
void RandomVariable::setMonteCarloFlag(int flag)
{
	monteCarloFlag = flag;
}

void RandomVariable::setNumberOfSamplesMC(int n)
{
	numberOfSamplesMC = n;
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
}

RandomVariable::RandomVariable(Distribution * distribution)
{
	this->setDistribution(distribution);
	precededOperation = NONE;
}

RandomVariable::~RandomVariable()
{
}

/*
 * methods
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
 * --- Overload Binary Operators: '+', '-', '*', '/'
 *
 */

RandomVariable RandomVariable::operator +(RandomVariable & rightarg)
{
	if (!distribution || !rightarg.distribution)
		throw stochastic::UndefinedDistributionException();

	if (monteCarloFlag)
		return MC_sum(this, & rightarg);

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

	if (monteCarloFlag)
		return MC_difference(* this, rightarg);

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

	if (monteCarloFlag)
		return MC_product(* this, rightarg);

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

	if (monteCarloFlag)
		return MC_ratio(* this, rightarg);

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

	if (monteCarloFlag)
		return MC_min(* this, secondarg);

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

	if (monteCarloFlag)
		return MC_max(* this, secondarg);

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
	if (monteCarloFlag)
		return MC_sum(c_arg, * this);

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
	if (monteCarloFlag)
		return MC_sum(-c_arg, * this);

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
	if (RandomVariable::monteCarloFlag)
		return RandomVariable::MC_difference(c_arg, rv_arg);

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
	if (monteCarloFlag)
		return MC_product(c_arg, * this);

	if (!c_arg)
		return RandomVariable();

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
	if (!c_arg)
		return RandomVariable();

	if (monteCarloFlag)
		return MC_product(1 / c_arg, * this);

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
	if (RandomVariable::monteCarloFlag)
		return RandomVariable::MC_ratio(c_arg, rv_arg);

	if (!c_arg)
		return RandomVariable();

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
	if (monteCarloFlag)
		return MC_min(c_arg, * this);

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
	if (monteCarloFlag)
		return MC_max(c_arg, * this);

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



/* ====================================================================
 *
 *
 *
 * Implementation of MonteCarlo
 *
 *
 * ====================================================================
 * */

RandomVariable RandomVariable::recursive(OperationType op,
		RandomVariable * arg1, RandomVariable * arg2)
{
	std::vector<double> produced_data;
	int i;

	for (i = 0; i < numberOfSamplesMC; i++)
	{
		samplesCollection.clear();
		produced_data.push_back(recursiveSample(op, arg1, arg2));
	}

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = op;
	result.parrent1 = arg1;
	result.parrent2 = arg2;
	return result;
}

double RandomVariable::recursiveSample(OperationType op,
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
		if (!arg1->precededOperation)
			sample1 = arg1->getDistribution()->nextSample();
		else
			sample1 = recursiveSample(arg1->precededOperation,
					arg1->parrent1, arg1->parrent2);
		samplesCollection[arg1] = sample1;
	}
	try
	{
		sample2 = samplesCollection.at(arg2);
	}
	catch(std::out_of_range ex)
	{
		if (!arg2->precededOperation)
			sample2 = arg2->getDistribution()->nextSample();
		else
			sample2 = recursiveSample(arg2->precededOperation,
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
		default:
			break;
	}
	throw 0; // this should never happen
}

/*
 *
 * --- Standard Binary Operations: '+', '-', '*', '/'
 */

RandomVariable RandomVariable::MC_sum(RandomVariable * arg1,
		RandomVariable * arg2)
{
	return recursive(SUM, arg1, arg2);

	std::vector<double> s1 = arg1->getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2->getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(s1[i] + s2[i]);

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = SUM;
	result.parrent1 = arg1;
	result.parrent2 = arg2;
	return result;
}

RandomVariable RandomVariable::MC_difference(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(s1[i] - s2[i]);

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = DIFFERENCE;
	result.parrent1 = & arg1;
	result.parrent2 = & arg2;
	return result;
}

RandomVariable RandomVariable::MC_product(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(s1[i] * s2[i]);

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = PRODUCT;
	result.parrent1 = & arg1;
	result.parrent2 = & arg2;
	return result;
}

RandomVariable RandomVariable::MC_ratio(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
	{
		if (!s2[i])
			s2[i] = 0.0000001;
		produced_data.push_back(s1[i] / s2[i]);
	}

	RandomVariable result = new EmpiricalDistribution(produced_data);
	result.precededOperation = RATIO;
	result.parrent1 = & arg1;
	result.parrent2 = & arg2;
	return result;
}

/*
 *
 * --- Binary Operations: min, max
 */

RandomVariable RandomVariable::MC_min(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(std::min<double>(s1[i], s2[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_max(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamplesMC);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(std::max<double>(s1[i], s2[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

/*
 *
 *
 *
 * Functions of ONE random variable
 *
 *
 * */

RandomVariable RandomVariable::MC_sum(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(c_arg + s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_difference(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(c_arg - s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_product(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(c_arg * s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_ratio(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
	{
		if (!s[i])
			s[i] = 0.0000001;
		produced_data.push_back(c_arg / s[i]);
	}
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_min(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(std::min<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable RandomVariable::MC_max(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamplesMC);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamplesMC; i++)
		produced_data.push_back(std::max<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

} // namespace stochastic
