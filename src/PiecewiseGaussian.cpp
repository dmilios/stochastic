/*
 * PiecewiseGaussian.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseGaussian.h"

#include <algorithm>
#include <limits>
#include <cmath>
#include "exceptions.h"

namespace stochastic {

PiecewiseGaussian::PiecewiseGaussian()
{
}


PiecewiseGaussian::PiecewiseGaussian(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseGaussian temp = * (PiecewiseGaussian *)fit(distribution);
	this->weights = temp.weights;
	this->components = temp.components;
	this->cumulativeWeights = temp.cumulativeWeights;
}

PiecewiseGaussian::~PiecewiseGaussian()
{
}

const char * PiecewiseGaussian::getName()
{
	return "pNorm";
}

PiecewiseBase * PiecewiseGaussian::fit(Distribution * distribution)
{
	PiecewiseGaussian * result = new PiecewiseGaussian;

	PiecewiseComponent * component;
	double weight;
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double support = end - start;
	double step = support / (double) fixedNumberOfComponents;
	int i;
	double stadardDeviation = support / (8 * fixedNumberOfComponents);
	double range = 4 * stadardDeviation;
	double x = start + range;


	// check for support so as to revise the step
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + range) - distribution->cdf(x - range);
		if (weight == 0)
			support -= step;
		x += step;
	}
	// revise the step
	step = support / (double) fixedNumberOfComponents;
	stadardDeviation = support / (8 * fixedNumberOfComponents);
	range = 4 * stadardDeviation;
	x = start + range;


	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + range) - distribution->cdf(x - range);
		if (weight)
		{
			double var = pow(range, 2);
			component = new Gaussian(x, var);
			result->components.push_back(component);
			result->weights.push_back(weight);
		}
		x += step;
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
}

} // namespace stochastic
