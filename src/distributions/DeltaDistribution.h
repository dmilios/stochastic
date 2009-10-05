/*
 * DeltaDistribution.h
 *
 *  Created on: 29-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef DELTADISTRIBUTION_H_
#define DELTADISTRIBUTION_H_

#include "MixtureComponent.h"

namespace stochastic {

class DeltaDistribution : public stochastic::MixtureComponent
{
private:
	double value;

public:
	DeltaDistribution(double);
	virtual ~DeltaDistribution();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();

	double quantile(double);
};

} // namespace stochastic

#endif /* DELTADISTRIBUTION_H_ */
