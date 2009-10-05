/*
 * Gaussian.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "MixtureComponent.h"
#include "../utilities/mathFunctions.h"

namespace stochastic {

class Gaussian : public stochastic::MixtureComponent
{
private:
	double mean;
	double variance;

	double cache_varX2;
	double cache_one_over_sqrt_var2PI;
	double cache_leftMargin;
	double cache_rightMargin;

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
