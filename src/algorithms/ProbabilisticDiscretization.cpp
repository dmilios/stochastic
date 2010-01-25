/*
 * GeneralizedProbabilisticDiscretization.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "ProbabilisticDiscretization.h"

#include <algorithm>
#include <cmath>
#include <typeinfo>

#include "../utilities/exceptions.h"
#include "../distributions/Uniform.h"
#include "../distributions/MixtureModel.h"

namespace stochastic
{

ProbabilisticDiscretization::ProbabilisticDiscretization(int n) :
	PiecewiseUniform(n)
{
}

ProbabilisticDiscretization::~ProbabilisticDiscretization()
{
}

std::string ProbabilisticDiscretization::getName()
{
	return string("Discretization");
}

MixtureComponent * ProbabilisticDiscretization::sumOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = arg1->getLeftMargin() + arg2->getLeftMargin();
	double b = arg1->getRightMargin() + arg2->getRightMargin();
	return new Uniform(a, b);
}

MixtureComponent * ProbabilisticDiscretization::differenceOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = arg1->getLeftMargin() - arg2->getRightMargin();
	double b = arg1->getRightMargin() - arg2->getLeftMargin();
	return new Uniform(a, b);
}

MixtureComponent * ProbabilisticDiscretization::productOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a1 = arg1->getLeftMargin();
	double b1 = arg1->getRightMargin();
	double a2 = arg2->getLeftMargin();
	double b2 = arg2->getRightMargin();

	std::vector<double> margins;
	margins.push_back(a1 * a2);
	margins.push_back(a1 * b2);
	margins.push_back(b1 * a2);
	margins.push_back(b1 * b2);

	std::vector<double>::iterator a = std::min_element(margins.begin(),
			margins.end());
	std::vector<double>::iterator b = std::max_element(margins.begin(),
			margins.end());
	return new Uniform(*a, *b);
}

MixtureComponent * ProbabilisticDiscretization::ratioOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a1 = arg1->getLeftMargin();
	double b1 = arg1->getRightMargin();
	double a2 = arg2->getLeftMargin();
	double b2 = arg2->getRightMargin();

	if (std::abs(a2) < 0.001)
		return 0;
	if (std::abs(b2) < 0.001)
		return 0;

	std::vector<double> margins;
	margins.push_back(a1 / a2);
	margins.push_back(a1 / b2);
	margins.push_back(b1 / a2);
	margins.push_back(b1 / b2);

	std::vector<double>::iterator a = std::min_element(margins.begin(),
			margins.end());
	std::vector<double>::iterator b = std::max_element(margins.begin(),
			margins.end());
	return new Uniform(*a, *b);
}

} // namespace stochastic
