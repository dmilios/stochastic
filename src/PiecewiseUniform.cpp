/*
 * PiecewiseUniform.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseUniform.h"

namespace stochastic {

PiecewiseUniform::PiecewiseUniform(const char * fileName)
{
	std::vector <double> data;
	data = parser.parseDataFile(fileName);
	this->fit(data);
}

PiecewiseUniform::PiecewiseUniform(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	this->fit(distribution);
}

PiecewiseUniform::~PiecewiseUniform()
{
}

const char * PiecewiseUniform::getName()
{
	return "pUni";
}

void PiecewiseUniform::fit(std::vector <double> data)
{
}

void PiecewiseUniform::fit(Distribution * distribution)
{
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
			this->components.push_back(component);
			this->weights.push_back(weight);
		}
		x += step;
	}
	this->normalizeWeights(); // constructs cumulativeWeights vector as well
}

// alternative fit using quantile
void PiecewiseUniform::fit2(Distribution * distribution)
{
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
			this->components.push_back(component);
			this->weights.push_back(weight);
		}
		else
			printf("zero weight\n");
		p += step;
	}
	this->normalizeWeights(); // constructs cumulativeWeights vector as well
}

} // namespace stochastic
