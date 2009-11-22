/*
 * PG_EM.cpp
 *
 *  Created on: 10 Nov 2009
 *      Author: Dimitrios Milios
 */

#include "PG_EM.h"

#include "../utilities/RandomGenerator.h"
#include <algorithm>
#include <cstdlib>

namespace stochastic
{

PG_EM::PG_EM(int n, int samples) :
	PiecewiseGaussian(n)
{
	this->intermediateSamples = samples;
}

PG_EM::~PG_EM()
{
}

std::vector<double> PG_EM::produceData(Distribution * d)
{
	double samples = (double) intermediateSamples;

	std::vector<double> data;
	double start = d->getLeftMargin();
	double end = d->getRightMargin();
	double step = (end - start) / numberOfComponents;

	double x = start;
	int i;
	for (i = 0; i < numberOfComponents; i++)
	{
		Gaussian gaussian(x + (step / 2), step / 100);
		double weight = d->cdf(x + step) - d->cdf(x);
		int j;
		for (j = 0; j < samples * weight; j++)
		{
			double sample = gaussian.nextSample();
			if (sample < x || sample > x + step)
				j--;
			else
				data.push_back(sample);
		}
		x += step;
	}
	return data;
}

MixtureModel * PG_EM::performApproximation(Distribution * distribution)
{
	MixtureModel * result;
	std::vector<MixtureComponent *> result_components;
	std::vector<double> result_weights;

	double *means = new double[numberOfComponents];
	double *variances = new double[numberOfComponents];
	double *coefficients = new double[numberOfComponents];
	int k;

	std::vector<double> data;
	data = produceData(distribution);
	// data = distribution->sample(intermediateSamples);

	std::vector<double>::iterator minimum = std::min_element(data.begin(),
			data.end());
	std::vector<double>::iterator maximum = std::max_element(data.begin(),
			data.end());

	// Initialisation
	for (k = 0; k < numberOfComponents; k++)
	{
		means[k] = this->generator.nextDouble(*minimum, *maximum);
		variances[k] = 1;
		coefficients[k] = 1.0 / numberOfComponents;
	}

	unsigned long instances = data.size();
	double **responsibilities = new double*[instances];
	unsigned long arrayCounter;
	for (arrayCounter = 0; arrayCounter < instances; arrayCounter++)
		responsibilities[arrayCounter] = new double[numberOfComponents];

	unsigned int j;

	//	double logLikelihood = -std::numeric_limits<double>::infinity();
	int iterations = 0;
	while (iterations++ < 100)
	{
		// Expectation step
		for (j = 0; j < instances; j++)
		{
			double denominator = 0;
			for (k = 0; k < numberOfComponents; k++)
			{
				responsibilities[j][k] = coefficients[k] * Gaussian(means[k],
						variances[k]).pdf(data[j]);
				denominator += responsibilities[j][k];
			}
			for (k = 0; k < numberOfComponents; k++)
				responsibilities[j][k] /= denominator;
		}

		// Maximisation step
		double *ni = new double[numberOfComponents];
		for (k = 0; k < numberOfComponents; k++) // update weights
		{
			ni[k] = 0;
			for (j = 0; j < instances; j++)
				ni[k] += responsibilities[j][k];
			coefficients[k] = ni[k] / instances;
		}
		for (k = 0; k < numberOfComponents; k++) // update means
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * data[j];
			means[k] = sum / ni[k];
		}
		for (k = 0; k < numberOfComponents; k++) // update variances
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * pow(data[j] - means[k], 2);
			variances[k] = sum / ni[k];
			if (!variances[k])
				variances[k] = 0.001;
		}
		delete ni;

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

	MixtureComponent * component;
	for (k = 0; k < numberOfComponents; k++)
	{
		component = new Gaussian(means[k], variances[k]);
		result_components.push_back(component);
		result_weights.push_back(coefficients[k]);
	}

	delete means;
	delete variances;
	delete coefficients;
	for (arrayCounter = 0; arrayCounter < instances; arrayCounter++)
		delete[] responsibilities[arrayCounter];
	delete responsibilities;

	result = new MixtureModel(result_components, result_weights);
	return result;
}

} // namespace stochastic
