/*
 * Uniform.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "Distribution.h"
#include "ApproximationComponent.h"

namespace stochastic {

class Uniform : public stochastic::ApproximationComponent
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

	// overload virtual methods of ApproximationComponent
	Distribution * add(ApproximationComponent *);
	Distribution * subtract(ApproximationComponent *);
	Distribution * multiply(ApproximationComponent *);
	Distribution * divide(ApproximationComponent *);
	Distribution * min(ApproximationComponent *);
	Distribution * max(ApproximationComponent *);
};

} // namespace stochastic

#endif /* UNIFORM_H_ */
