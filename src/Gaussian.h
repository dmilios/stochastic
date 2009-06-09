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
	void sample(int);
};

} // namespace stochastic

#endif /* GAUSSIAN_H_ */
