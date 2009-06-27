/*
 * Distribution.cpp
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Distribution.h"

#include <cmath>
#include <limits>
#include "exceptions.h"

namespace stochastic {

// Static Member: Random Generator
RandomGenerator Distribution::generator;

Distribution::Distribution()
{
}

Distribution::~Distribution()
{
}

/* Compute the inverse CDF of 'p' for the current distribution
 * using Bisection method  */
double Distribution::quantile(double p)
{
	if (p > 1 || p < 0)
		throw InvalidParametersException();
	if (p < 1e-4)
		return this->getLeftMargin();
	if (p > 1 - 1e-4)
		return this->getRightMargin();

	double a = getLeftMargin();
	double b = getRightMargin();
	double x, difference = std::numeric_limits<double>::infinity();
	int tries = 0;
	do
	{
		x = (a + b) / 2;
		if ((cdf(a) - p) * (cdf(x) - p) >= 0)
			a = x;
		else if ((cdf(b) - p) * (cdf(b) - p) >= 0)
			b = x;
		if (difference > cdf(x) - p)
			difference = cdf(x) - p;
		difference = std::abs(difference);
	} while (difference > 1e-4 && tries++ < 100);
	return x;
}

double Distribution::kolmogorovDistance(Distribution * arg)
{
	int accuracy = 1000;
	double supremum = 0;
	double start = std::min(this->getLeftMargin(), arg->getLeftMargin());
	double end = std::max(this->getRightMargin(), arg->getRightMargin());
	double step = (end - start) / (double) accuracy;
	double x = start;
	double distance;
	int i;
	for (i = 0; i < accuracy; i++)
	{
		distance = std::abs(this->cdf(x) - arg->cdf(x));
		if (supremum < distance)
			supremum = distance;
		x += step;
	}
	return supremum;
}

/* @brief Computes KL-Div(P||Q), where P==this, Q==arg
 * Integral is computed by constructing interpolating linear functions */
double Distribution::KL_Divergence(Distribution * arg)
{
	double result = 0;
	int accuracy = 100;
	double start = this->getLeftMargin();
	double end = this->getRightMargin();
	if (arg->getLeftMargin() < start)
		start = arg->getLeftMargin();
	if (arg->getRightMargin() > end)
		end = arg->getRightMargin();

	// FIXME: margin staff
	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;
	double px = this->pdf(x);
	double qx = arg->pdf(x);

	fx_a = px * log(px / qx);
	for (i = 0; i < accuracy; i++)
	{
		px = this->pdf(x + step);
		qx = arg->pdf(x + step);
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

double Distribution::hellingerDistance(Distribution * arg)
{
	double result = 0;
	int accuracy = 100;
	double start = this->getLeftMargin();
	double end = this->getRightMargin();
	if (arg->getLeftMargin() < start)
		start = arg->getLeftMargin();
	if (arg->getRightMargin() > end)
		end = arg->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;

	fx_a = pow(sqrt(this->pdf(x)) - sqrt(arg->pdf(x)), 2);
	for (i = 0; i < accuracy; i++)
	{
		fx_b = pow(sqrt(this->pdf(x + step)) - sqrt(arg->pdf(x + step)), 2);
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return sqrt(result / 2);
}

std::vector<double> Distribution::sample(int numberOfSamples)
{
	int i;
	std::vector<double> samples;
	for (i = 0; i < numberOfSamples; i++)
		samples.push_back(nextSample());
	return samples;
}

/**
 * @brief Protected member, implements rejection sampling
 * Arguments are used to define an envelope uniform distribution
 * Returns a sample of the wanted distribution,
 * according to its defined 'pdf()' method
 */
double Distribution::rejectionSampling(double highestProbability,
		double leftMargin, double rightMargin)
{
	double proposedSample;
	double uniformSample_0_1;
	double px;
	double proposalUniform = 1 / (rightMargin - leftMargin);
	double k = 1;
	if (proposalUniform < highestProbability)
		k = ceil(highestProbability / proposalUniform);
	do
	{
		proposedSample = generator.nextDouble(leftMargin, rightMargin);
		uniformSample_0_1 = generator.nextDouble();
		px = this->pdf(proposedSample);
	} while (uniformSample_0_1 >= px / (k * proposalUniform));
	return proposedSample;
}

} // namespace stochastic
