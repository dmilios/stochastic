/*
 * Exponential.h
 *
 *  Created on: 08-Jun-2009
 *      Author: dimitrios
 */

#ifndef EXPONENTIAL_H_
#define EXPONENTIAL_H_

#include "MixtureComponent.h"

namespace stochastic {

class Exponential : public stochastic::MixtureComponent
{
private:
	double lambda;

public:
	Exponential();
	Exponential(double);
	virtual ~Exponential();

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double cdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();
};

} // namespace stochastic

#endif /* EXPONENTIAL_H_ */
