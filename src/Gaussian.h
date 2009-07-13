/*
 * Gaussian.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "MixtureComponent.h"

namespace stochastic {

class Gaussian : public stochastic::MixtureComponent
{
private:
	double mean;
	double variance;
	static const double pi;

public:
	Gaussian();
	Gaussian(double);
	Gaussian(double, double);
	virtual ~Gaussian();

	double getMean();
	double getVariance();

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double cdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();
};

} // namespace stochastic

#endif /* GAUSSIAN_H_ */
