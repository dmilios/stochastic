/*
 * PiecewiseUniform.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseUniform.h"

namespace stochastic {

PiecewiseUniform::PiecewiseUniform()
{
}

PiecewiseUniform::PiecewiseUniform(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseUniform temp = * (PiecewiseUniform *)fit(distribution);
	this->weights = temp.weights;
	this->components = temp.components;
	this->cumulativeWeights = temp.cumulativeWeights;
}

PiecewiseUniform::~PiecewiseUniform()
{
}

const char * PiecewiseUniform::getName()
{
	return "pUni";
}

PiecewiseBase * PiecewiseUniform::fit(Distribution * distribution)
{
	PiecewiseUniform * result = new PiecewiseUniform;

	PiecewiseComponent * component;
	double weight;
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double support = end - start;
	double step = support / (double) fixedNumberOfComponents;
	int i;
	double x = start;

	// check for support so as to revise the step
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		if (weight == 0)
			support -= step;
		x += step;
	}
	// revise the step
	step = support / (double) fixedNumberOfComponents;
	x = start;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		if (weight)
		{
			component = new Uniform(x, x + step);
			result->components.push_back(component);
			result->weights.push_back(weight);
		}
		x += step;
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
}

// alternative fit using quantile
PiecewiseBase * PiecewiseUniform::fit2(Distribution * distribution)
{
	PiecewiseUniform * result;

	PiecewiseComponent * component;
	double weight;
	double step = 1 / (double) fixedNumberOfComponents;
	int i;
	double p = 0;
	double x, x_step;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		try{
		x = distribution->quantile(p);
		x_step = distribution->quantile(p + step);
		}
		catch(InvalidParametersException e)
		{
		}
		weight = distribution->cdf(x_step) - distribution->cdf(x);
		if (weight)
		{
			component = new Uniform(x, x_step);
			result->components.push_back(component);
			result->weights.push_back(weight);
		}
		else
			printf("zero weight\n");
		p += step;
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
}

} // namespace stochastic
