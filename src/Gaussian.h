/*
 * Gaussian.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "Distribution.h"
#include "PiecewiseComponent.h"

namespace stochastic {

class Gaussian : public stochastic::PiecewiseComponent
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

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double cdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();

	// overload virtual methods of PiecewiseComponent
	MixtureComponent * sum(PiecewiseComponent *);
	MixtureComponent * difference(PiecewiseComponent *);
	MixtureComponent * product(PiecewiseComponent *);
	MixtureComponent * ratio(PiecewiseComponent *);
	MixtureComponent * min(PiecewiseComponent *);
	MixtureComponent * max(PiecewiseComponent *);
};

} // namespace stochastic

#endif /* GAUSSIAN_H_ */
