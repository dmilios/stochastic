/*
 * InverseRV_Distribution.h
 *
 *  Created on: 03-Aug-2009
 *      Author: Dimitrios Milios
 */

#ifndef INVERSERV_DISTRIBUTION_H_
#define INVERSERV_DISTRIBUTION_H_

#include "../distributions/MixtureComponent.h"

namespace stochastic {

// The distribution of Y = 1 / X
class InverseRV_Distribution : public stochastic::MixtureComponent
{
private:
	Distribution * original;

	double cache_leftMargin;
	double cache_rightMargin;

public:
	InverseRV_Distribution(Distribution *);
	virtual ~InverseRV_Distribution();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // end stochastic

#endif /* INVERSERV_DISTRIBUTION_H_ */
