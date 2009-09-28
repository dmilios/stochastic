/*
 * Cauchy.h
 *
 *  Created on: 14-Aug-2009
 *      Author: Dimitrios Milios
 */

#ifndef CAUCHY_H_
#define CAUCHY_H_

#include "MixtureComponent.h"

namespace stochastic {

class Cauchy : public stochastic::MixtureComponent
{
private:
	double location;
	double gamma;

public:
	Cauchy(double, double);
	virtual ~Cauchy();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* CAUCHY_H_ */
