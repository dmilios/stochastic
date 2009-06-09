/*
 * Linear.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef LINEAR_H_
#define LINEAR_H_

#include "Distribution.h"
#include "ApproximationComponent.h"

namespace stochastic {

class Linear : public stochastic::ApproximationComponent
{
public:
	Linear();
	virtual ~Linear();

	//FIXME: change void to 'array of samples'
	void sample(int);
};

} // namespace stochastic

#endif /* LINEAR_H_ */
