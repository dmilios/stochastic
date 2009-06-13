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
	double pdf(double);
	double nextSample();

	// overload virtual methods of ApproximationComponent
	ApproximationComponent * add(ApproximationComponent *);
	ApproximationComponent * subtract(ApproximationComponent *);
	ApproximationComponent * multiply(ApproximationComponent *);
	ApproximationComponent * divide(ApproximationComponent *);
	ApproximationComponent * min(ApproximationComponent *);
	ApproximationComponent * max(ApproximationComponent *);
};

} // namespace stochastic

#endif /* UNIFORM_H_ */
