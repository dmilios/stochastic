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

PiecewiseGaussian::PiecewiseGaussian(const char * fileName)
{
	std::vector<double> data;
	data = parser.parseDataFile(fileName);
	this->fit(data);
}

PiecewiseGaussian::PiecewiseGaussian(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	this->fit(distribution);
}

PiecewiseGaussian::~PiecewiseGaussian()
{
}

const char * PiecewiseGaussian::getName()
{
	return "pNorm";
}

void PiecewiseGaussian::fit(std::vector<double> data)
{
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

	ApproximationComponent * component;
	for (k = 0; k < fixedNumberOfComponents; k++)
	{
		component = new Gaussian(means[k], variances[k]);
		this->components.push_back(component);
		this->weights.push_back(coefficients[k]);
	}
	this->normalizeWeights();
}

void PiecewiseGaussian::fit(Distribution * distribution)
{
}

} // namespace stochastic
