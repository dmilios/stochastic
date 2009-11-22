/*
 * PU_DivideAndConquer.cpp
 *
 *  Created on: 15 Nov 2009
 *      Author: Dimitrios Milios
 */

#include "PU_DivideAndConquer.h"

#include "../distributions/Uniform.h"
#include <cmath>

namespace stochastic
{

PU_DivideAndConquer::PU_DivideAndConquer(int n) :
	PiecewiseUniform(n)
{
}

PU_DivideAndConquer::~PU_DivideAndConquer()
{
}

void PU_DivideAndConquer::approximateInterval(
		std::vector<MixtureComponent *> &components,
		std::vector<double> &weights, int componentNumber, double start,
		double end, Distribution *dist)
{
	double x1 = start;
	double x2;
	double x3 = end;
	std::vector<double> errors;

	Uniform *curr = new Uniform(x1, x3);
	double w = dist->cdf(x3) - dist->cdf(x1);
	components.push_back(curr);
	weights.push_back(w);
	errors.push_back(0);

	while (components.size() != (unsigned) componentNumber)
	{
		std::vector<MixtureComponent *>::iterator it_comp = components.begin();
		std::vector<double>::iterator it_w = weights.begin();
		std::vector<double>::iterator it_er = errors.begin();
		MixtureComponent *popComponent = *it_comp;

		components.erase(it_comp);
		weights.erase(it_w);
		x1 = popComponent->getLeftMargin();
		x3 = popComponent->getRightMargin();
		x2 = (x1 + x3) / 2;

		Uniform *split1 = new Uniform(x1, x2);
		Uniform *split2 = new Uniform(x2, x3);
		double w1 = dist->cdf(x2) - dist->cdf(x1);
		if (w1 < 0)
			w1 = 0;
		double w2 = dist->cdf(x3) - dist->cdf(x2);
		if (w2 < 0)
			w2 = 0;
		double error1 = errorMeasure(split1, w1, dist);
		double error2 = errorMeasure(split2, w2, dist);

		int i;
		it_comp = components.begin();
		it_w = weights.begin();
		it_er = errors.begin();
		int insertedFlag = 0;
		for (i = 0; errors.size() < (unsigned) i; i++)
		{
			if (error1 > errors[i])
			{
				components.insert(it_comp, split1);
				weights.insert(it_w, w1);
				errors.insert(it_er, error1);
				insertedFlag = 1;
				break;
			}
			it_comp++;
			it_w++;
			it_er++;
		}
		if (!insertedFlag)
		{
			components.push_back(split1);
			weights.push_back(w1);
			errors.push_back(error1);
		}

		it_comp = components.begin();
		it_w = weights.begin();
		it_er = errors.begin();
		insertedFlag = 0;
		for (i = 0; errors.size() < (unsigned) i; i++)
		{
			if (error2 > errors[i])
			{
				components.insert(it_comp, split2);
				weights.insert(it_w, w2);
				errors.insert(it_er, error2);
				insertedFlag = 1;
				break;
			}
			it_comp++;
			it_w++;
			it_er++;
		}
		if (!insertedFlag)
		{
			components.push_back(split2);
			weights.push_back(w2);
			errors.push_back(error2);
		}
	}
}

double pdfDistance(MixtureComponent * mc, double w, Distribution * dist)
{
	int accuracy = 100;

	double error = 0;
	double x1 = mc->getLeftMargin();
	double x2 = mc->getRightMargin();
	double x = x1;
	double step = (x2 - x1) / accuracy;
	double fx_a, fx_b;
	int i;
	fx_a = std::abs(w * mc->pdf(x) - dist->pdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(w * mc->pdf(x + step) - dist->pdf(x + step));
		error += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return error;
}

double PU_DivideAndConquer::errorMeasure(MixtureComponent * mc, double w,
		Distribution * dist)
{
	return pdfDistance(mc, w, dist);
}

MixtureModel * PU_DivideAndConquer::performApproximation(
		Distribution * distribution)
{
	MixtureModel * result;
	std::vector<MixtureComponent *> result_components;
	std::vector<double> result_weights;

	std::vector<double> supportInterval_lmargins;
	std::vector<double> supportInterval_rmargins;
	// margin vectors are called by reference
	retrieveSupport(distribution, supportInterval_lmargins,
			supportInterval_rmargins);

	int k; // counter for the support intervals
	int total_support_intervals = supportInterval_lmargins.size();

	// the accuracy for each support interval will be
	// proportional to its probability mass
	int componentsUsed = 0;
	for (k = 0; k < total_support_intervals; k++)
	{
		// (F(b) - F(a)) * totalComponentNumber
		int intervalComponents = (int) (distribution->cdf(
				supportInterval_rmargins[k]) - distribution->cdf(
				supportInterval_lmargins[k])) * numberOfComponents;
		if (k == total_support_intervals - 1) // the last one
			intervalComponents = numberOfComponents - componentsUsed;
		else
			componentsUsed += intervalComponents;

		std::vector<MixtureComponent *> tmp_components;
		std::vector<double> tmp_weights;
		approximateInterval(tmp_components, tmp_weights, intervalComponents,
				supportInterval_lmargins[k], supportInterval_rmargins[k],
				distribution);
		unsigned int i;
		for (i = 0; i < tmp_components.size(); i++)
		{
			result_components.push_back(tmp_components[i]);
			result_weights.push_back(tmp_weights[i]);
		}
	}

	result = new MixtureModel(result_components, result_weights);
	return result;
}

} // namespace stochastic
