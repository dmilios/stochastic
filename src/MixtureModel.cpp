/*
 * MixtureModel.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "MixtureModel.h"

#include <typeinfo>
#include <limits>
#include <sstream>

namespace stochastic {

MixtureModel::MixtureModel(std::vector<MixtureComponent *> components,
		std::vector<double> weights)
{
	if (components.size() <= 0)
		throw UndefinedDistributionException();
	if (components.size() != weights.size())
		throw InvalidWeightsException();

	this->components = components;
	this->weights = weights;
	cumulativeWeights = this->constructCumulativeWeights(weights);
}

MixtureModel::~MixtureModel()
{
}

std::vector<double> MixtureModel::constructCumulativeWeights(
		std::vector<double> & w)
{
	std::vector<double> cweights;
	unsigned int i;
	double sum = 0;
	double cumulativeWeight = 0;
	for (i = 0; i < w.size(); i++)
	{
		if (w[i] < 0)
			throw InvalidWeightsException();

		sum += w[i];
	}
	for (i = 0; i < w.size(); i++)
	{
		w[i] /= sum;
		cumulativeWeight += w[i];
		cweights.push_back(cumulativeWeight);
	}
	return cweights;
}

const char * MixtureModel::getName()
{
	std::stringstream numberOfComponents_s;
	numberOfComponents_s << this->components.size();
	std::string firstComponent(components[0]->getName());

	std::string name("mm");
	name.append(numberOfComponents_s.str());
	name.append("_");
	name.append(firstComponent);
	return name.c_str();
}

double MixtureModel::pdf(double x)
{
	if (x < this->getLeftMargin() || x > this->getRightMargin())
		return 0;

	//TODO: somehow make MM::pdf() and MM::cdf() more efficient

	unsigned int i;
	double weighted_sum = 0;
	for (i = 0; i < components.size(); i++)
		weighted_sum += components[i]->pdf(x) * weights[i];
	return weighted_sum;
}

double MixtureModel::cdf(double x)
{
	if (x < this->getLeftMargin())
		return 0;
	if (x >= this->getRightMargin())
		return 1;

	unsigned int i;
	double weighted_sum = 0;
	for (i = 0; i < components.size(); i++)
		weighted_sum += components[i]->cdf(x) * weights[i];
	return weighted_sum;
}

double MixtureModel::getLeftMargin()
{
	double minimum = std::numeric_limits<double>::infinity();
	unsigned int i;
	for (i = 0; i < components.size(); i++)
		if (components[i]->getLeftMargin() < minimum)
			minimum = components[i]->getLeftMargin();
	return minimum;
}

double MixtureModel::getRightMargin()
{
	double maximum = -std::numeric_limits<double>::infinity();
	unsigned int i;
	for (i = 0; i < components.size(); i++)
		if (components[i]->getRightMargin() > maximum)
			maximum = components[i]->getRightMargin();
	return maximum;
}

double MixtureModel::nextSample()
{
	double roulette = generator.nextDouble();
	unsigned int i;
	for (i = 0; i < weights.size(); i++)
		if (roulette < cumulativeWeights[i])
			return this->components[i]->nextSample();

	// this line should never be executed
	throw 0;
}

} // namespace stochastic
