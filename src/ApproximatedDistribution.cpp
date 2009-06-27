/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "ApproximatedDistribution.h"

#include "exceptions.h"

#include <iostream>
#include <vector>
#include <typeinfo>

namespace stochastic {

FileParser ApproximatedDistribution::parser;

int ApproximatedDistribution::fixedNumberOfComponents = 10;

// Static Method: sets the wanted number of components
void ApproximatedDistribution::setFixedNumberOfComponents(int n)
{
	fixedNumberOfComponents = n;
}

Distribution * ApproximatedDistribution::add(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	ApproximationComponent * leftComponent;
	ApproximationComponent * rightComponent;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			leftComponent = (ApproximationComponent *)this->components[i];
			rightComponent = (ApproximationComponent *)arg->components[j];
			resultComponents.push_back((MixtureComponent *)leftComponent->add(rightComponent));
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * ApproximatedDistribution::subtract(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	ApproximationComponent * leftComponent;
	ApproximationComponent * rightComponent;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			leftComponent = (ApproximationComponent *)this->components[i];
			rightComponent = (ApproximationComponent *)arg->components[j];
			resultComponents.push_back((MixtureComponent *)leftComponent->subtract(rightComponent));
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * ApproximatedDistribution::multiply(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	ApproximationComponent * leftComponent;
	ApproximationComponent * rightComponent;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			leftComponent = (ApproximationComponent *)this->components[i];
			rightComponent = (ApproximationComponent *)arg->components[j];
			resultComponents.push_back((MixtureComponent *)leftComponent->multiply(rightComponent));
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution * ApproximatedDistribution::divide(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	ApproximationComponent * leftComponent;
	ApproximationComponent * rightComponent;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			leftComponent = (ApproximationComponent *)this->components[i];
			rightComponent = (ApproximationComponent *)arg->components[j];
			resultComponents.push_back((MixtureComponent *)leftComponent->divide(rightComponent));
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

Distribution *ApproximatedDistribution:: min(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();
	return 0;
}

Distribution * ApproximatedDistribution::max(ApproximatedDistribution * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();
	return 0;
}

} // namespace stochastic
