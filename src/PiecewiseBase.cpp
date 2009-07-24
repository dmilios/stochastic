/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseBase.h"

#include "exceptions.h"

#include <iostream>
#include <vector>
#include <typeinfo>

namespace stochastic {

int PiecewiseBase::fixedNumberOfComponents = 10;

// Static Method: sets the wanted number of components
void PiecewiseBase::setFixedNumberOfComponents(int n)
{
	fixedNumberOfComponents = n;
}

/*
 * returns two vectors that define the intervals
 * containing the support of input distribution
 * and the support itself
 *
 * It will be needed for the approximations
 */
double PiecewiseBase::retrieveSupport(Distribution * distribution,
		std::vector<double> & supportInterval_lmargins,
		std::vector<double> & supportInterval_rmargins)
{
	double weight;
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double support = end - start;
	double step = support / (double) fixedNumberOfComponents;
	int i;
	double x = start;

	// check for support so as to revise the step
	int flag_inSupport = 0;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->pdf(x);
		if (weight)
		{
			if (!flag_inSupport)
			{
				flag_inSupport = 1;
				supportInterval_lmargins.push_back(x);
			}
		}
		else
		{
			if (flag_inSupport)
			{
				flag_inSupport = 0;
				supportInterval_rmargins.push_back(x);
			}
			support -= step;
		}
		x += step;
	}
	if (supportInterval_lmargins.size() > supportInterval_rmargins.size())
		supportInterval_rmargins.push_back(distribution->getRightMargin());
	return support;
}

MixtureModel * PiecewiseBase::sum(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	unsigned int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < this->components.size(); i++)
		for (j = 0; j < arg->components.size(); j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = sumOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::difference(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = differenceOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::product(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = productOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::ratio(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = ratioOfComponents(left, right);

			// discard null results
			if (currentResult)
			{
				resultComponents.push_back(currentResult);
				resultWeights.push_back(this->weights[i] * arg->weights[j]);
			}
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel *PiecewiseBase::min(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = minOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::max(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = this->components[i];
			right = arg->components[j];
			currentResult = maxOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}


/*
 *
 *
 * Functions of ONE random variable
 *
 * */

MixtureModel * PiecewiseBase::sum(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = sumOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, this->weights);
}

MixtureModel * PiecewiseBase::differenceFrom(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = differenceOfComponents(c_arg, distr_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, this->weights);
}

MixtureModel * PiecewiseBase::product(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = productOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, this->weights);
}

MixtureModel * PiecewiseBase::denominatorOf(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = ratioOfComponents(c_arg, distr_arg);
		// discard null results
		if (currentResult)
		{
			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i]);
		}
	}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::min(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = minOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, this->weights);
}

MixtureModel * PiecewiseBase::max(double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		distr_arg = this->components[i];
		currentResult = maxOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, this->weights);
}

} // namespace stochastic
