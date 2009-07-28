/*
 * MinOfGaussians.h
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef MINOFGAUSSIANS_H_
#define MINOFGAUSSIANS_H_

#include "MixtureComponent.h"
#include "Gaussian.h"

namespace stochastic {

class MinOfGaussians : public stochastic::MixtureComponent
{
private:
	Gaussian arg1;
	Gaussian arg2;

	double cache_leftMargin;
	double cache_rightMargin;

public:
	MinOfGaussians(Gaussian, Gaussian);
	virtual ~MinOfGaussians();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* MINOFGAUSSIANS_H_ */
