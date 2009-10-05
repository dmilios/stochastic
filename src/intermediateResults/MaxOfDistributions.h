/*
 * MaxOfDistributions.h
 *
 *  Created on: 27-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef MAXOFDISTRIBUTIONS_H_
#define MAXOFDISTRIBUTIONS_H_

#include "../distributions/MixtureComponent.h"

namespace stochastic {

class MaxOfDistributions : public stochastic::MixtureComponent
{
public:
private:
	Distribution * arg1;
	Distribution * arg2;

	double cache_leftMargin;
	double cache_rightMargin;

public:
	MaxOfDistributions(Distribution *, Distribution *);
	virtual ~MaxOfDistributions();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* MAXOFDISTRIBUTIONS_H_ */
