/*
 * PG_EM2.cpp
 *
 *  Created on: 8 Mar 2010
 *      Author: Dimitrios Milios
 */

#include "PG_EM2.h"
#include "PiecewiseUniform.h"

namespace stochastic
{

PG_EM2::PG_EM2(int n) :
	PiecewiseGaussian(n)
{
}

PG_EM2::~PG_EM2()
{
}

std::string PG_EM2::getName()
{
	return std::string("PG EM2");
}

MixtureModel * PG_EM2::performApproximation(Distribution * distribution)
{
	MixtureModel * result;
	std::vector<MixtureComponent *> result_components;
	std::vector<double> result_weights;

	double *means = new double[numberOfComponents];
	double *variances = new double[numberOfComponents];
	double *coefficients = new double[numberOfComponents];
	int k;

	// Initialisation
	for (k = 0; k < numberOfComponents; k++)
	{
		means[k] = this->generator.nextDouble(distribution->getLeftMargin(),
				distribution->getRightMargin());
		variances[k] = 1;
		coefficients[k] = 1.0 / numberOfComponents;
	}
	unsigned long instances = numberOfComponents;
	double **responsibilities = new double*[instances];
	unsigned long arrayCounter;
	for (arrayCounter = 0; arrayCounter < instances; arrayCounter++)
		responsibilities[arrayCounter] = new double[numberOfComponents];
	unsigned int j;

	/*
	 *
	 * */
	PiecewiseUniform pu(instances);
	MixtureModel * m = pu.performApproximation(distribution);
	double * dataMean = new double[instances];
	double * dataWeight = new double[instances];
	for (j = 0; j < instances; j++)
	{
		dataMean[j] = 0.5 * (m->getComponents()[j]->getLeftMargin()
				+ m->getComponents()[j]->getRightMargin());
		dataWeight[j] = m->getWeights()[j];
	}

	/*
	 *
	 * */

	// Actual EM steps
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
						variances[k]).pdf(dataMean[j]) * dataWeight[j];
				denominator += responsibilities[j][k];
			}
			for (k = 0; k < numberOfComponents; k++)
			{
				if (!denominator)
					denominator = 0.000001;
				responsibilities[j][k] /= denominator;
			}
		}

		// Maximisation step
		double *ni = new double[numberOfComponents];
		for (k = 0; k < numberOfComponents; k++) // update weights
		{
			ni[k] = 0;
			for (j = 0; j < instances; j++)
				ni[k] += responsibilities[j][k];
			if (!ni[k])
				ni[k] = 0.000001;
			coefficients[k] = ni[k] / instances;
		}
		for (k = 0; k < numberOfComponents; k++) // update means
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * dataMean[j];
			means[k] = sum / ni[k];
		}
		for (k = 0; k < numberOfComponents; k++) // update variances
		{
			double sum = 0;
			for (j = 0; j < instances; j++)
				sum += responsibilities[j][k] * pow(dataMean[j] - means[k], 2) * dataWeight[j];
			variances[k] = sum / ni[k];
			if (!variances[k])
				variances[k] = 0.001;
		}
		delete ni;
	}

	// ending -- after EM steps
	Gaussian * component;
	for (k = 0; k < numberOfComponents; k++)
	{
		component = new Gaussian(means[k], variances[k]);
		result_components.push_back(component);
		result_weights.push_back(coefficients[k]);
	}

	delete dataMean;
	delete dataWeight;

	delete means;
	delete variances;
	delete coefficients;
	for (arrayCounter = 0; arrayCounter < instances; arrayCounter++)
		delete[] responsibilities[arrayCounter];
	delete responsibilities;

	// construct and return the resulting mixture model
	result = new MixtureModel(result_components, result_weights);
	return result;
}

} // namespace stochastic
