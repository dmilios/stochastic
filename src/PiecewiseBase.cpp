/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseBase.h"

#include "exceptions.h"

#include <iostream>
#include <vector>
#include <typeinfo>

namespace stochastic {

FileParser PiecewiseBase::parser;

int PiecewiseBase::fixedNumberOfComponents = 10;

// Static Method: sets the wanted number of components
void PiecewiseBase::setFixedNumberOfComponents(int n)
{
	fixedNumberOfComponents = n;
}

MixtureModel * PiecewiseBase::sum(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->sum(right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::difference(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->difference(right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::product(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->product(right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::ratio(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->ratio(right);

			// discard null results
			if (currentResult)
			{
				resultComponents.push_back(currentResult);
				resultWeights.push_back(this->weights[i] * arg->weights[j]);
			}
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel *PiecewiseBase:: min(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->min(right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

MixtureModel * PiecewiseBase::max(PiecewiseBase * arg)
{
	if (typeid(* this) != typeid(* arg))
		throw stochastic::IncompatibleComponentsException();

	std::vector<MixtureComponent *> resultComponents;
	std::vector<double> resultWeights;
	int i, j;
	PiecewiseComponent * left;
	PiecewiseComponent * right;
	MixtureComponent * currentResult;
	for (i = 0; i < fixedNumberOfComponents; i++)
		for (j = 0; j < fixedNumberOfComponents; j++)
		{
			left = (PiecewiseComponent *)this->components[i];
			right = (PiecewiseComponent *)arg->components[j];
			currentResult = (MixtureComponent *)left->max(right);

			resultComponents.push_back(currentResult);
			resultWeights.push_back(this->weights[i] * arg->weights[j]);
		}
	return new MixtureModel(resultComponents, resultWeights);
}

} // namespace stochastic
