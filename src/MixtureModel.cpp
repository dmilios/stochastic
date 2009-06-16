/*
 * MixtureModel.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "MixtureModel.h"

#include <typeinfo>
#include <cmath> // for INFINITY
#include <sstream>

namespace stochastic {

MixtureModel::MixtureModel(std::vector <MixtureComponent *> components,
		std::vector <double> weights)
{
	if (components.size() <= 0)
		throw UndefinedDistributionException();
	if (components.size() != weights.size())
		throw InvalidWeightsException();

	this->components = components;
	this->weights = weights;
	this->normalizeWeights(); // constructs cumulativeWeights vector as well
}

MixtureModel::~MixtureModel()
{
}

void MixtureModel::normalizeWeights()
{
	unsigned int i;
	double sum = 0;
	double cumulativeWeight = 0;
	for (i = 0; i < weights.size(); i++)
	{
		if (weights[i] < 0)
			throw InvalidWeightsException();

		sum += weights[i];
	}
	for (i = 0; i < weights.size(); i++)
	{
		weights[i] /= sum;
		cumulativeWeight += weights[i];
		this->cumulativeWeights.push_back(cumulativeWeight);
	}
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

	//TODO: somehow make MM::pdf() more efficient

	unsigned int i;
	double weighted_sum = 0;
	for (i = 0; i < components.size(); i++)
		weighted_sum += components[i]->pdf(x) * weights[i];
	return weighted_sum;
}

double MixtureModel::cdf(double x)
{
	//TODO: implement cdf() for MM
	return 0;
}

double MixtureModel::getLeftMargin()
{
	double minimum = INFINITY;
	unsigned int i;
	for (i = 0; i < components.size(); i++)
		if (components[i]->getLeftMargin() < minimum)
			minimum = components[i]->getLeftMargin();
	return minimum;
}

double MixtureModel::getRightMargin()
{
	double maximum = -INFINITY;
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
