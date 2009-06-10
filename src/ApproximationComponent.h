/*
 * ApproximationComponent.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 *
 *  This class serves as an "interface", so as to
 *  group the distributions that can be parts of
 *  approximated distributions.
 *
 *  Operators that are applied on the parts are defined
 */

#ifndef APPROXIMATIONCOMPONENT_H_
#define APPROXIMATIONCOMPONENT_H_

#include "MixtureComponent.h"

namespace stochastic {

class ApproximationComponent : public stochastic::MixtureComponent
{
public:
	virtual ApproximationComponent * add(ApproximationComponent *) = 0;
	virtual ApproximationComponent * subtract(ApproximationComponent *) = 0;
	virtual ApproximationComponent * multiply(ApproximationComponent *) = 0;
	virtual ApproximationComponent * divide(ApproximationComponent *) = 0;

	virtual ApproximationComponent * min(ApproximationComponent *) = 0;
	virtual ApproximationComponent * max(ApproximationComponent *) = 0;
};

} // namespace stochastic

#endif /* APPROXIMATIONCOMPONENT_H_ */
