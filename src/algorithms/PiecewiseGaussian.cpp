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
#include <typeinfo>

#include "../distributions/MixtureModel.h"
#include "../utilities/exceptions.h"
#include "../utilities/mathFunctions.h"


namespace stochastic {

PiecewiseGaussian::PiecewiseGaussian(int n)
{
	this->numberOfComponents = n;
}

PiecewiseGaussian::~PiecewiseGaussian()
{
}

string PiecewiseGaussian::getName()
{
	return string("Piecewise Gaussian");
}

int PiecewiseGaussian::needsApproximation(Distribution * argument)
{
	if (typeid(* argument) != typeid(MixtureModel))
		return 1;
	int size = ((MixtureModel *) argument)->getComponents().size();
	if (size != numberOfComponents)
		return 1;

	int i;
	for (i = 0; i < size; i++)
	{
		MixtureComponent * current = ((MixtureModel *) argument)->getComponents()[i];
		if (typeid(* current) != typeid(Gaussian))
			return 1;
	}
	return 0;
}

MixtureModel * PiecewiseGaussian::performApproximation(Distribution * distribution)
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
	int total_support_intervals = supportInterval_lmargins.size();

	// the accuracy for each support interval will be
	// proportional to its probability mass
	for (k = 0; k < total_support_intervals; k++)
	{
		int intervalComponents;
		// (F(b) - F(a)) * totalComponentNumber
		intervalComponents = (int) (distribution->cdf(supportInterval_rmargins[k])
				- distribution->cdf(supportInterval_lmargins[k]))
				* numberOfComponents;
		if (k == total_support_intervals - 1) // the last one
			intervalComponents = numberOfComponents - componentsUsed;
		else
			componentsUsed += intervalComponents;


		int i;
		double x = supportInterval_lmargins[k];
		double weight;
		double step = (supportInterval_rmargins[k]
				- supportInterval_lmargins[k]) / intervalComponents;
		double var = step * step;

		for (i = 0; i < intervalComponents; i++)
		{
			weight = distribution->cdf(x + step / 2)
						- distribution->cdf(x - step / 2);

			if (x + step / 2 >= supportInterval_rmargins[k])
				weight = 0;
			if (x - step / 2 <= supportInterval_lmargins[k])
				weight = 0;
			if (weight < 0) // negative results are just close to zero
				weight = 0;
			component = new Gaussian(x, var);
			result_components.push_back(component);
			result_weights.push_back(weight);
			x += step;
		}
	}
	result = new MixtureModel(result_components, result_weights);
	return result;
}

/*
 *
 * Methods for computing the results of operations between components
 * Implement pure virtual methods from 'PiecewiseBase'
 *
 * */

MixtureComponent * PiecewiseGaussian::sumOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double m1 = ((Gaussian *) arg1)->getMean();
	double m2 = ((Gaussian *) arg2)->getMean();
	double var1 = ((Gaussian *) arg1)->getVariance();
	double var2 = ((Gaussian *) arg2)->getVariance();
	return new Gaussian(m1 + m2, var1 + var2);
}

MixtureComponent * PiecewiseGaussian::differenceOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double m1 = ((Gaussian *) arg1)->getMean();
	double m2 = ((Gaussian *) arg2)->getMean();
	double var1 = ((Gaussian *) arg1)->getVariance();
	double var2 = ((Gaussian *) arg2)->getVariance();
	return new Gaussian(m1 - m2, var1 + var2);
}

MixtureComponent * PiecewiseGaussian::productOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double m1 = ((Gaussian *) arg1)->getMean();
	double v1 = ((Gaussian *) arg1)->getVariance();
	double m2 = ((Gaussian *) arg2)->getMean();
	double v2 = ((Gaussian *) arg2)->getVariance();

	double m = m1 * m2;
	double var = v1 * v2 + v1 * m2 * m2 + v2 * m1 * m1;
	return new Gaussian(m, var);
}

MixtureComponent * PiecewiseGaussian::ratioOfComponents(
		MixtureComponent * arg1, MixtureComponent * arg2)
{
	double a1 = arg1->getLeftMargin();
	double b1 = arg1->getRightMargin();
	double a2 = arg2->getLeftMargin();
	double b2 = arg2->getRightMargin();

	std::vector<double> margins;
	margins.push_back(a1 / a2);
	margins.push_back(a1 / b2);
	margins.push_back(b1 / a2);
	margins.push_back(b1 / b2);

	if (std::abs(a2) < 0.001)
		return 0;
	if (std::abs(b2) < 0.001)
		return 0;

	std::vector<double>::iterator a = std::min_element(
			margins.begin(), margins.end());
	std::vector<double>::iterator b = std::max_element(
			margins.begin(), margins.end());

	double var = pow((* b - * a) / 8, 2);
	double m = (* a + * b) / 2;
	return new Gaussian(m, var);
}

/*
 *
 *
 * for functions of ONE random variable
 *
 * */

MixtureComponent * PiecewiseGaussian::sumOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double m = ((Gaussian *) distr_arg)->getMean();
	double var = ((Gaussian *) distr_arg)->getVariance();
	return new Gaussian(m + c_arg, var);
}

MixtureComponent * PiecewiseGaussian::differenceOfComponents(double c_arg,
		MixtureComponent * distr_arg)
{
	double m = ((Gaussian *) distr_arg)->getMean();
	double var = ((Gaussian *) distr_arg)->getVariance();
	return new Gaussian(c_arg - m, var);
}

MixtureComponent * PiecewiseGaussian::productOfComponents(
		MixtureComponent * distr_arg, double c_arg)
{
	double m = ((Gaussian *) distr_arg)->getMean();
	double var = ((Gaussian *) distr_arg)->getVariance();
	return new Gaussian(m * c_arg, var * pow(c_arg, 2));
}

} // namespace stochastic
