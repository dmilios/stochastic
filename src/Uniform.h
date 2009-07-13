/*
 * Uniform.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "MixtureComponent.h"

namespace stochastic {

class Uniform : public stochastic::MixtureComponent
{
private:
	double alpha;
	double beta;

public:
	Uniform();
	Uniform(double, double);
	virtual ~Uniform();

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double cdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();
};

} // namespace stochastic

#endif /* UNIFORM_H_ */
