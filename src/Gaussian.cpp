/*
 * Gaussian.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Gaussian.h"

#include "IncomparableInnerRepresentationException.h"
#include "InvalidParametersException.h"
#include <typeinfo>
#include <cmath>

namespace stochastic {

const double Gaussian::pi = 3.14159265;

Gaussian::Gaussian()
{
	mean = 0;
	variance = 1;
}

Gaussian::Gaussian(double mean)
{
	this->mean = mean;
	variance = 1;
}

Gaussian::Gaussian(double mean, double variance)
{
	if (variance <= 0)
		throw InvalidParametersException();

	this->mean = mean;
	this->variance = variance;
}

Gaussian::~Gaussian()
{
}

double Gaussian::pdf(double x)
{
	return ( 1 / sqrt(2 * pi * variance) * exp(-pow(x - mean,2) / (2 * variance)) );
}

double Gaussian::nextSample()
{
	double proposedSample;
	double uniformSample_0_1;
	double px;

	double highestProbability = pdf(mean);
	double leftMargin = mean - 3 * sqrt(variance);
	double rightMargin = mean + 3 * sqrt(variance);

	double proposalUniform = 1 / (rightMargin - leftMargin);
	double k = 1;
	if (proposalUniform < highestProbability)
		k = ceil(highestProbability / proposalUniform);

	do
	{
		proposedSample = this->nextUniform_0_1() * (rightMargin - leftMargin) + leftMargin;
		uniformSample_0_1 = this->nextUniform_0_1();
		px = this->pdf(proposedSample);
	}while(uniformSample_0_1 >= px / (k * proposalUniform));
	return proposedSample;
}

/*
 *
 * --- Implement Binary Operators: '+', '-', '*', '/'
 * --- for Gaussian Approximation Component
 */

ApproximationComponent * Gaussian::add(ApproximationComponent * rightarg)
{
	ApproximationComponent * result;
	if (typeid(*this) != typeid(*rightarg))
				throw stochastic::IncomparableInnerRepresentationException();
			result = new Gaussian;

			return result;
		}

		ApproximationComponent * Gaussian::subtract(
				ApproximationComponent * rightarg)
		{
			ApproximationComponent * result;
			if (typeid(*this) != typeid(*rightarg))
						throw stochastic::IncomparableInnerRepresentationException();
					result = new Gaussian;

					return result;
				}

				ApproximationComponent * Gaussian::multiply(
						ApproximationComponent * rightarg)
				{
					ApproximationComponent * result;
					if (typeid(*this) != typeid(*rightarg))
								throw stochastic::IncomparableInnerRepresentationException();
							result = new Gaussian;

							return result;
						}

						ApproximationComponent * Gaussian::divide(
								ApproximationComponent * rightarg)
						{
							ApproximationComponent * result;
							if (typeid(*this) != typeid(*rightarg))
										throw stochastic::IncomparableInnerRepresentationException();
									result = new Gaussian;

									return result;
								}

								/*
								 *
								 * --- Implement Binary Operators: min, max
								 * --- for Gaussian Approximation Component
								 */

								ApproximationComponent * Gaussian::min(
										ApproximationComponent * secondarg)
								{
									ApproximationComponent * result;
									if (typeid(*this) != typeid(*secondarg))
												throw stochastic::IncomparableInnerRepresentationException();
											result = new Gaussian;

											return result;
										}

										ApproximationComponent * Gaussian::max(
												ApproximationComponent * secondarg)
										{
											ApproximationComponent * result;
											if (typeid(*this)
															!= typeid(*secondarg))
														throw stochastic::IncomparableInnerRepresentationException();
													result = new Gaussian;

													return result;
												}

												} // namespace stochastic
