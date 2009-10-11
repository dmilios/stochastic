/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseBase.h"

#include "../utilities/exceptions.h"

#include <iostream>
#include <vector>
#include <typeinfo>

#include "../intermediateResults/InverseRV_Distribution.h"

namespace stochastic {

// Static Method: sets the wanted number of components
void PiecewiseBase::setFixedNumberOfComponents(int n)
{
	numberOfComponents = n;
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
	double step = support / (double) numberOfComponents;
	int i;
	double x = start;

	// check for support so as to revise the step
	int flag_inSupport = 0;
	for (i = 0; i < numberOfComponents; i++)
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

Distribution * PiecewiseBase::calculateSum(Distribution * arg1, Distribution * arg2)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	unsigned int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;

	for (i = 0; i < ((MixtureModel *)arg1)->getComponents().size(); i++)
		for (j = 0; j < ((MixtureModel *) arg2)->getComponents().size(); j++)
		{
			left = ((MixtureModel *)arg1)->getComponents()[i];
			right = ((MixtureModel *)arg2)->getComponents()[j];
			currentResult = sumOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(((MixtureModel *)arg1)->getWeights()[i] * ((MixtureModel *)arg2)->getWeights()[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * PiecewiseBase::calculateDifference(Distribution * arg1, Distribution * arg2)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
		for (j = 0; j < numberOfComponents; j++)
		{
			left = ((MixtureModel *)arg1)->getComponents()[i];
			right = ((MixtureModel *)arg2)->getComponents()[j];
			currentResult = differenceOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(((MixtureModel *)arg1)->getWeights()[i] * ((MixtureModel *)arg2)->getWeights()[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * PiecewiseBase::calculateProduct(Distribution * arg1, Distribution * arg2)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
		for (j = 0; j < numberOfComponents; j++)
		{
			left = ((MixtureModel *)arg1)->getComponents()[i];
			right = ((MixtureModel *)arg2)->getComponents()[j];
			currentResult = productOfComponents(left, right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(((MixtureModel *)arg1)->getWeights()[i] * ((MixtureModel *)arg2)->getWeights()[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * PiecewiseBase::calculateRatio(Distribution * arg1, Distribution * arg2)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	MixtureComponent * left;
	MixtureComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
		for (j = 0; j < numberOfComponents; j++)
		{
			left = ((MixtureModel *)arg1)->getComponents()[i];
			right = ((MixtureModel *)arg2)->getComponents()[j];
			currentResult = ratioOfComponents(left, right);

			// discard null results
			if (currentResult)
			{
				resultComponents.push_back(currentResult);
				resultWeights.push_back(((MixtureModel *)arg1)->getWeights()[i] * ((MixtureModel *)arg2)->getWeights()[j]);
			}
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * PiecewiseBase::calculateMin(Distribution * arg1, Distribution * arg2)
{
	return 0;
}

Distribution * PiecewiseBase::calculateMax(Distribution * arg1, Distribution * arg2)
{
	return 0;
}

/*
 *
 *
 * Functions of ONE random variable
 *
 * */

Distribution * PiecewiseBase::calculateSum(Distribution * d_arg, double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
	{
		distr_arg = ((MixtureModel *)d_arg)->getComponents()[i];
		currentResult = sumOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, ((MixtureModel *)d_arg)->getWeights());
}

Distribution * PiecewiseBase::calculateDifference(Distribution * d_arg, double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
	{
		distr_arg = ((MixtureModel *)d_arg)->getComponents()[i];
		currentResult = differenceOfComponents(c_arg, distr_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, ((MixtureModel *)d_arg)->getWeights());
}

Distribution * PiecewiseBase::calculateDifference(double c_arg, Distribution * d_arg)
{
	return 0;
}

Distribution * PiecewiseBase::calculateProduct(Distribution * d_arg, double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
	{
		distr_arg = ((MixtureModel *)d_arg)->getComponents()[i];
		currentResult = productOfComponents(distr_arg, c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, ((MixtureModel *)d_arg)->getWeights());
}

// deprecated: needed for comparison
Distribution * PiecewiseBase::calculateRatio(Distribution * d_arg, double c_arg)
{
	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i;
	MixtureComponent * distr_arg;
	MixtureComponent * currentResult;
	for (i = 0; i < numberOfComponents; i++)
	{
		distr_arg = ((MixtureModel *)d_arg)->getComponents()[i];
		currentResult = ratioOfComponents(c_arg, distr_arg);
		// discard null results
		if (currentResult)
		{
			resultComponents.push_back(currentResult);
			resultWeights.push_back(((MixtureModel *)d_arg)->getWeights()[i]);
		}
	}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * PiecewiseBase::calculateRatio(double c_arg, Distribution * d_arg)
{
	return 0;
}

Distribution * PiecewiseBase::calculateMin(Distribution * d_arg, double c_arg)
{
	return 0;
}

Distribution * PiecewiseBase::calculateMax(Distribution * d_arg, double c_arg)
{
	return 0;
}

} // namespace stochastic
