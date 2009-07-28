/*
 * MaxOfGaussians.h
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef MAXOFGAUSSIANS_H_
#define MAXOFGAUSSIANS_H_

#include "MixtureComponent.h"
#include "Gaussian.h"

namespace stochastic {

class MaxOfGaussians : public stochastic::MixtureComponent
{
public:
private:
	Gaussian arg1;
	Gaussian arg2;

	double cache_leftMargin;
	double cache_rightMargin;

public:
	MaxOfGaussians(Gaussian, Gaussian);
	virtual ~MaxOfGaussians();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* MAXOFGAUSSIANS_H_ */
