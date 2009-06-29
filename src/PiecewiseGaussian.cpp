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

PiecewiseGaussian::PiecewiseGaussian(const char * fileName)
{
	std::vector<double> data;
	data = parser.parseDataFile(fileName);

	PiecewiseGaussian temp = * (PiecewiseGaussian *)fit(data);
	this->weights = temp.weights;
	this->components = temp.components;
	this->cumulativeWeights = temp.cumulativeWeights;
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

PiecewiseBase * PiecewiseGaussian::fit(std::vector<double> data)
{
	PiecewiseGaussian * result = new PiecewiseGaussian;

	double means[fixedNumberOfComponents];
	double variances[fixedNumberOfComponents];
	double coefficients[fixedNumberOfComponents];
	int k;
	std::vector<double>::iterator minimum = std::min_element(data.begin(),
			data.end());
	std::vector<double>::iterator maximum = std::max_element(data.begin(),
			data.end());
	// Initialisation
	for (k = 0; k < fixedNumberOfComponents; k++)
	{
		means[k] = this->generator.nextDouble(*minimum, *maximum);
		variances[k] = 1;
		coefficients[k] = 1.0 / fixedNumberOfComponents;
	}

	unsigned int instances = data.size();
	double responsibilities[instances][fixedNumberOfComponents];
	unsigned int j;

//	double logLikelihood = -std::numeric_limits<double>::infinity();
	int iterations = 0;
	while (iterations++ < 100)
	{
		// Expectation step
		for (j = 0; j < instances; j++)
		{
			double denominator = 0;
			for (k = 0; k < fixedNumberOfComponents; k++)
			{
				responsibilities[j][k] = coefficients[k] * Gaussian(means[k],
						variances[k]).pdf(data[j]);
				denominator += responsibilities[j][k];
			}
			for (k = 0; k < fixedNumberOfComponents; k++)
				responsibilities[j][k] /= denominator;
		}

		// Maximisation step
		double ni[fixedNumberOfComponents];
		for (k = 0; k < fixedNumberOfComponents; k++) // update weights
		{
			ni[k] = 0;
			for (j = 0; j < instances; j++)
				ni[k] += responsibilities[j][k];
			coefficients[k] = ni[k] / instances;
		}
		for (k = 0; k < fixedNumberOfComponents; k++) // update means
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * data[j];
			means[k] = sum / ni[k];
		}
		for (k = 0; k < fixedNumberOfComponents; k++) // update variances
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * pow(data[j] - means[k], 2);
			variances[k] = sum / ni[k];
			if (!variances[k])
				variances[k] = 0.001;
		}

		// Evaluate log likelihood
//		logLikelihood = 0;
//		for (j = 0; j < instances; j++)
//		{
//			double internalSum = 0;
//			for (k = 0; k < fixedNumberOfComponents; k++)
//				internalSum += coefficients[k] * Gaussian(means[k],
//						variances[k]).pdf(data[j]);
//			logLikelihood += log(internalSum);
//		}
//		printf("log likelihood: %f\n", logLikelihood);
	}

	PiecewiseComponent * component;
	for (k = 0; k < fixedNumberOfComponents; k++)
	{
		component = new Gaussian(means[k], variances[k]);
		result->components.push_back(component);
		result->weights.push_back(coefficients[k]);
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
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
