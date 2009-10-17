/*
 * PiecewiseUniform.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseUniform.h"

#include <algorithm>
#include <cmath>
#include <typeinfo>

#include "../utilities/exceptions.h"
#include "../distributions/Uniform.h"
#include "../intermediateResults/SumOfUniforms.h"
#include "../distributions/MixtureModel.h"

namespace stochastic {

PiecewiseUniform::PiecewiseUniform(int n)
{
	this->numberOfComponents = n;
}

PiecewiseUniform::~PiecewiseUniform()
{
}

int PiecewiseUniform::needsApproximation(Distribution * argument)
{
	if (typeid(*argument) != typeid(MixtureModel))
		return 1;
	int size = ((MixtureModel *) argument)->getComponents().size();
	if (size != numberOfComponents)
		return 1;

	int i;
	for (i = 0; i < size; i++)
	{
		MixtureComponent * current =
			((MixtureModel *) argument)->getComponents()[i];
		if (typeid(*current) != typeid(Uniform))
			return 1;
	}
	return 0;
}

MixtureModel * PiecewiseUniform::performApproximation(
		Distribution * distribution)
{
	MixtureModel * result;
	std::vector<MixtureComponent *> result_components;
	std::vector<double> result_weights;

	MixtureComponent * component;
	std::vector<double> supportInterval_lmargins;
	std::vector<double> supportInterval_rmargins;

	// margin vectors are called by reference
	retrieveSupport(distribution, supportInterval_lmargins,
			supportInterval_rmargins);

	int k; // counter for the support intervals
	int componentsUsed = 0;
	int total_support_intervals =
		supportInterval_lmargins.size();

	// the accuracy for each support interval will be
	// proportional to its probability mass
	for (k = 0; k < total_support_intervals; k++)
	{
		int intervalComponents;
		// (F(b) - F(a)) * totalComponentNumber
		intervalComponents
		= (int) (distribution->cdf(
				supportInterval_rmargins[k])
				- distribution->cdf(
						supportInterval_lmargins[k]))
						* numberOfComponents;
		if (k == total_support_intervals - 1) // the last one
			intervalComponents = numberOfComponents
			- componentsUsed;
		else
			componentsUsed += intervalComponents;

		int i;
		double x = supportInterval_lmargins[k];
		double weight;
		double step = (supportInterval_rmargins[k]
		                                        - supportInterval_lmargins[k])
		                                        / intervalComponents;

		double p = distribution->pdf(x);
		for (i = 0; i < intervalComponents; i++)
		{
			p = distribution->pdf(x + step);

			weight = distribution->cdf(x + step)
			- distribution->cdf(x);

			if (x + step >= supportInterval_rmargins[k])
				weight = 0;
			if (weight < 0) // negative results are just close to zero
				weight = 0;
			component = new Uniform(x, x + step);
			result_components.push_back(component);
			result_weights.push_back(weight);
			x += step;
		}
	}
	result
	= new MixtureModel(result_components,
			result_weights);
	return result;
}

// alternative fit using quantile
MixtureModel * PiecewiseUniform::performApproximation2(
		Distribution * distribution)
{
	MixtureModel * result;
	std::vector<MixtureComponent *> result_components;
	std::vector<double> result_weights;

	MixtureComponent * component;
	double weight;
	double step = 1 / (double) numberOfComponents;
	int i;
	double p = 0;
	double x, x_step;
	for (i = 0; i < numberOfComponents; i++)
	{
		x = distribution->quantile(p);
		if (p + step > 1)
			x_step = distribution->quantile(1);
		else
			x_step = distribution->quantile(p + step);

		weight = distribution->cdf(x_step) - distribution->cdf(
				x);
		if (weight < 0) // negative results are just close to zero
		weight = 0;

		try
		{
			component = new Uniform(x, x_step);
		}
		catch (InvalidParametersException e)
		{
			component = new Uniform(0, 1e-5);
			weight = 0;
		}
		result_components.push_back(component);
		result_weights.push_back(weight);
		p += step;
	}
	result
	= new MixtureModel(result_components,
			result_weights);
	return result;
}

/*
 *
 * Private methods
 *
 *
 *
 * Methods for computing the results of operations between components
 * Implement pure virtual methods from 'PiecewiseAlgorithm'
 *
 *
 * */

MixtureComponent * PiecewiseUniform::sumOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a1 = arg1->getLeftMargin();
	double b1 = arg1->getRightMargin();
	double a2 = arg2->getLeftMargin();
	double b2 = arg2->getRightMargin();
	return new SumOfUniforms(a1, b1, a2, b2);
}

MixtureComponent * PiecewiseUniform::differenceOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a1 = arg1->getLeftMargin();
	double b1 = arg1->getRightMargin();
	// multiply the second argument by -1
	double a2 = -arg2->getRightMargin();
	double b2 = -arg2->getLeftMargin();
	return new SumOfUniforms(a1, b1, a2, b2);
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
	return new Uniform(*a, *b);
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
	return new Uniform(*a, *b);
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

 MixtureComponent * PiecewiseUniform::differenceOfComponents(
		 double c_arg, MixtureComponent * distr_arg)
 {
	 double a = c_arg - distr_arg->getRightMargin();
	 double b = c_arg - distr_arg->getLeftMargin();
	 return new Uniform(a, b);
 }

 MixtureComponent * PiecewiseUniform::productOfComponents(
		 MixtureComponent * distr_arg, double c_arg)
 {
	 double a = distr_arg->getLeftMargin() * c_arg;
	 double b = distr_arg->getRightMargin() * c_arg;
	 return new Uniform(std::min<double>(a, b),
			 std::max<double>(a, b));
 }

} // namespace stochastic
