/*
 * PiecewiseLinear.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseLinear.h"

namespace stochastic {

PiecewiseLinear::PiecewiseLinear(const char * fileName)
{
	std::vector <double> data;
	data = parser.parseDataFile(fileName);
	this->fit(data);
}

PiecewiseLinear::PiecewiseLinear(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	this->fit(distribution);
}

PiecewiseLinear::~PiecewiseLinear()
{
}

const char * PiecewiseLinear::getName()
{
	return "pLin";
}

void PiecewiseLinear::fit(std::vector <double> data)
{
}

void PiecewiseLinear::fit(Distribution * distribution)
{
	//FIXME: Do something with PiecewiseLinear

	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double step = (end - start) / (double) fixedNumberOfComponents;
	ApproximationComponent * component;
	double weight;
	double slope;
	int i;
	double x = start;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		slope = (distribution->pdf(x + step) - distribution->pdf(x)) / step;

		component = new Linear(x, x + step, slope / weight);

		this->components.push_back(component);
		this->weights.push_back(weight);
		x += step;
	}
	this->normalizeWeights(); // constructs cumulativeWeights vector as well

//	weights.clear();
//	for (i = 0; i < fixedNumberOfComponents; i++)
//		weights.push_back(1);
}

double PiecewiseLinear::nextSample()
{
	return rejectionSampling(pdf(0.0001), getLeftMargin(), getRightMargin());
}

} // namespace stochastic
