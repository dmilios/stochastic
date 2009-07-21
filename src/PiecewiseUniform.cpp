/*
 * PiecewiseUniform.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseUniform.h"

#include "exceptions.h"
#include <algorithm>
#include <cmath>

namespace stochastic {

PiecewiseUniform::PiecewiseUniform()
{
}

PiecewiseUniform::PiecewiseUniform(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	PiecewiseUniform temp = * (PiecewiseUniform *)fit(distribution);
	this->weights = temp.weights;
	this->components = temp.components;
	this->cumulativeWeights = temp.cumulativeWeights;
}

PiecewiseUniform::~PiecewiseUniform()
{
}

const char * PiecewiseUniform::getName()
{
	return "pUni";
}

PiecewiseBase * PiecewiseUniform::fit(Distribution * distribution)
{
	PiecewiseUniform * result = new PiecewiseUniform;

	MixtureComponent * component;
	double weight;
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double support = end - start;
	double step = support / (double) fixedNumberOfComponents;
	int i;
	double x = start;

	// check for support so as to revise the step
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		if (weight == 0)
			support -= step;
		x += step;
	}
	// revise the step
	step = support / (double) fixedNumberOfComponents;
	x = start;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		weight = distribution->cdf(x + step) - distribution->cdf(x);
		component = new Uniform(x, x + step);
		result->components.push_back(component);
		result->weights.push_back(weight);
		x += step;
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
}

// alternative fit using quantile
PiecewiseBase * PiecewiseUniform::fit2(Distribution * distribution)
{
	PiecewiseUniform * result = new PiecewiseUniform;

	MixtureComponent * component;
	double weight;
	double step = 1 / (double) fixedNumberOfComponents;
	int i;
	double p = 0;
	double x, x_step;
	for (i = 0; i < fixedNumberOfComponents; i++)
	{
		x = distribution->quantile(p);
		if (p + step > 1)
			x_step = distribution->quantile(1);
		else
			x_step = distribution->quantile(p + step);
		weight = distribution->cdf(x_step) - distribution->cdf(x);
		if (weight)
		{
			component = new Uniform(x, x_step);
			result->components.push_back(component);
			result->weights.push_back(weight);
		}
		else
			printf("zero weight\n");
		p += step;
	}
	result->cumulativeWeights = constructCumulativeWeights(result->weights);
	return result;
}

/*
 *
 * Private methods
 *
 *
 *
 * Methods for computing the results of operations between components
 * Implement pure virtual methods from 'PiecewiseBase'
 *
 *
 * */

MixtureComponent * PiecewiseUniform::sumOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = arg1->getLeftMargin() + arg2->getLeftMargin();
	double b = arg1->getRightMargin() + arg2->getRightMargin();
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::differenceOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = arg1->getLeftMargin() - arg2->getRightMargin();
	double b = arg1->getRightMargin() - arg2->getLeftMargin();
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::productOfComponents(
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

	std::vector<double>::iterator a = std::min_element(
									margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
									margins.begin(), margins.end());
	return new Uniform(* a, * b);
}

MixtureComponent * PiecewiseUniform::ratioOfComponents(
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

	std::vector<double>::iterator a = std::min_element(
			margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
			margins.begin(), margins.end());
	return new Uniform(* a, * b);
}

MixtureComponent * PiecewiseUniform::minOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = std::min<double>(arg1->getLeftMargin(), arg2->getLeftMargin());
	double b = std::min<double>(arg1->getRightMargin(), arg2->getRightMargin());
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::maxOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a = std::max<double>(arg1->getLeftMargin(), arg2->getLeftMargin());
	double b = std::max<double>(arg1->getRightMargin(), arg2->getRightMargin());
	return new Uniform(a, b);
}


/*
 *
 *
 *
 * For functions of ONE random variable
 *
 * */

MixtureComponent * PiecewiseUniform::sumOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double a = distr_arg->getLeftMargin() + c_arg;
	double b = distr_arg->getRightMargin() + c_arg;
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::differenceOfComponents(double c_arg,
		MixtureComponent * distr_arg)
{
	double a =  c_arg - distr_arg->getRightMargin();
	double b =  c_arg - distr_arg->getLeftMargin();
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::productOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double a = distr_arg->getLeftMargin() * c_arg;
	double b = distr_arg->getRightMargin() * c_arg;
	return new Uniform(std::min<double>(a, b), std::max<double>(a, b));
}

MixtureComponent * PiecewiseUniform::ratioOfComponents(double c_arg,
		MixtureComponent * distr_arg)
{
	double a = distr_arg->getLeftMargin();
	double b = distr_arg->getRightMargin();
	if (std::abs(a) < 0.001)
		return 0;
	if (std::abs(b) < 0.001)
		return 0;

	a = c_arg / a;
	b = c_arg / b;
	return new Uniform(std::min<double>(a, b), std::max<double>(a, b));
}

MixtureComponent * PiecewiseUniform::minOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double a = std::min<double>(distr_arg->getLeftMargin(), c_arg);
	double b = std::min<double>(distr_arg->getRightMargin(), c_arg);
	if (a == b)
	{
		// FIXME: Are min and max valid?
		double width = distr_arg->getRightMargin() - distr_arg->getLeftMargin();
		return new Uniform(a - width, b);
	}
	return new Uniform(a, b);
}

MixtureComponent * PiecewiseUniform::maxOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double a = std::max<double>(distr_arg->getLeftMargin(), c_arg);
	double b = std::max<double>(distr_arg->getRightMargin(), c_arg);
	if (a == b)
	{
		// FIXME: Are min and max valid?
		double width = distr_arg->getRightMargin() - distr_arg->getLeftMargin();
		return new Uniform(a, b + width);
	}
	return new Uniform(a, b);
}

} // namespace stochastic
