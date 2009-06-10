/*
 * Gaussian.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_

#include "Distribution.h"
#include "ApproximationComponent.h"

namespace stochastic {

class Gaussian : public stochastic::ApproximationComponent
{
public:
	Gaussian();
	virtual ~Gaussian();

	//FIXME: change void to 'array of samples'
	// overload virtual methods of Distribution
	void sample(int);

	// overload virtual methods of ApproximationComponent
	ApproximationComponent * add(ApproximationComponent *);
	ApproximationComponent * subtract(ApproximationComponent *);
	ApproximationComponent * multiply(ApproximationComponent *);
	ApproximationComponent * divide(ApproximationComponent *);
	ApproximationComponent * min(ApproximationComponent *);
	ApproximationComponent * max(ApproximationComponent *);
};

} // namespace stochastic

#endif /* GAUSSIAN_H_ */
