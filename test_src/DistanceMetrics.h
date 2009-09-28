/*
 * DistanceMetrics.h
 *
 *  Created on: 28-Sep-2009
 *      Author: Dimitrios Milios
 */

#ifndef DISTANCEMETRICS_H_
#define DISTANCEMETRICS_H_

#include "../src/stochastic.h"

using namespace stochastic;

inline double kolmogorovDistance(Distribution * arg1, Distribution * arg2)
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

/* @brief Computes KL-Div(P||Q) */
inline double KL_Divergence(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 100000;
	int i;
	double sum = 0;
	double x;
	for (i = 0; i < accuracy; i++)
	{
		x = arg1->nextSample();
		double tmp = log(arg1->pdf(x) / arg2->pdf(x));
		if (tmp != INFINITY)
			sum += tmp;
	}
	if (sum < 0) // computatinal error -> try again
		return KL_Divergence(arg1, arg2);
	return sum / accuracy;
}

inline double hellingerDistance(Distribution * arg1, Distribution * arg2)
{
	int accuracy = 100;
	int i;
	double x;

	double result = 0;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;

	fx_a = pow(sqrt(arg1->pdf(x)) - sqrt(arg2->pdf(x)), 2);
	for (i = 0; i < accuracy; i++)
	{
		fx_b = pow(sqrt(arg1->pdf(x + step)) - sqrt(arg2->pdf(x + step)), 2);
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return (result / 2);
}

inline double manhattanDistancePDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	fx_a = std::abs(arg1->pdf(x) - arg2->pdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(arg1->pdf(x + step) - arg2->pdf(x + step));
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return result;
}

inline double manhattanDistanceCDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
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

	fx_a = std::abs(arg1->cdf(x) - arg2->cdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(arg1->cdf(x + step) - arg2->cdf(x + step));
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return result;
}

#endif /* DISTANCEMETRICS_H_ */
