/*
 * MinOfDistributions.h
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef MINOFDISTRIBUTIONS_H_
#define MINOFDISTRIBUTIONS_H_

#include "../distributions/MixtureComponent.h"

namespace stochastic {

class MinOfDistributions : public stochastic::MixtureComponent
{
private:
	Distribution * arg1;
	Distribution * arg2;

	double cache_leftMargin;
	double cache_rightMargin;

public:
	MinOfDistributions(Distribution *, Distribution *);
	virtual ~MinOfDistributions();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* MINOFDISTRIBUTIONS_H_ */
