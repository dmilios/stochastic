/*
 * Experiments.cpp
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "Experiments.h"
#include <cmath>
#include <algorithm>

namespace stochastic {

double Experiments::kolmogorovDistance(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 1000;
	double supremum = 0;
	double start = std::min(arg1->getLeftMargin(), arg2->getLeftMargin());
	double end = std::max(arg1->getRightMargin(), arg2->getRightMargin());
	double step = (end - start) / (double) accuracy;
	double x = start;
	double distance;
	int i;
	for (i = 0; i < accuracy; i++)
	{
		distance = std::abs(arg1->cdf(x) - arg2->cdf(x));
		if (supremum < distance)
			supremum = distance;
		x += step;
	}
	return supremum;
}

/* @brief Computes KL-Div(P||Q), where P==this, Q==arg
 * Integral is computed by constructing interpolating linear functions */
double Experiments::KL_Divergence(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 100;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;
	double px = arg1->pdf(x);
	double qx = arg2->pdf(x);

	fx_a = px * log(px / qx);
	for (i = 0; i < accuracy; i++)
	{
		px = arg1->pdf(x + step);
		qx = arg2->pdf(x + step);
		if (!px || !qx) // any pdf is zero
		{
			x = x + step;
			continue;
		}
		fx_b = px * log(px / qx);
		result += step * (fx_a + fx_b) / 2;

		fx_a = fx_b;
		x = x + step;
	}
	return result;
}

double Experiments::hellingerDistance(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 100;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;

	fx_a = pow(sqrt(arg1->pdf(x)) - sqrt(arg1->pdf(x)), 2);
	for (i = 0; i < accuracy; i++)
	{
		fx_b = pow(sqrt(arg1->pdf(x + step)) - sqrt(arg1->pdf(x + step)), 2);
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return sqrt(result / 2);
}

} // namespace stochastic
