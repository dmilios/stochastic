/*
 * Uniform.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "Distribution.h"
#include "PiecewiseComponent.h"

namespace stochastic {

class Uniform : public stochastic::PiecewiseComponent
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

	// overload virtual methods of PiecewiseComponent
	MixtureComponent * sum(PiecewiseComponent *);
	MixtureComponent * difference(PiecewiseComponent *);
	MixtureComponent * product(PiecewiseComponent *);
	MixtureComponent * ratio(PiecewiseComponent *);
	MixtureComponent * min(PiecewiseComponent *);
	MixtureComponent * max(PiecewiseComponent *);
};

} // namespace stochastic

#endif /* UNIFORM_H_ */
