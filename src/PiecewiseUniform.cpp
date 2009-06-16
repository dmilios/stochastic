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
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double step = (end - start) / (double) fixedNumberOfComponents;
	ApproximationComponent * component;
	double weight;
	int i;
	double x = start;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		component = new Uniform(x, x + step);
		this->components.push_back(component);
		this->weights.push_back(weight);
		x += step;
	}
	this->normalizeWeights(); // constructs cumulativeWeights vector as well
}

} // namespace stochastic
