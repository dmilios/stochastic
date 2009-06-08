/*
 * Uniform.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "Distribution.h"
#include "PieceDistribution.h"

namespace stochastic {

class Uniform : public stochastic::Distribution,
		public stochastic::PieceDistribution {
public:
	Uniform();
	virtual ~Uniform();

	//FIXME: change void to 'array of samples'
	void sample(int);

	double getWeight();
	void setWeight(double);
};

} // namespace stochastic

#endif /* UNIFORM_H_ */
