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
	virtual RandomVariable operator +(RandomVariable) = 0;
	virtual RandomVariable operator -(RandomVariable) = 0;
	virtual RandomVariable operator *(RandomVariable) = 0;
	virtual RandomVariable operator /(RandomVariable) = 0;

	virtual RandomVariable min(RandomVariable) = 0;
	virtual RandomVariable max(RandomVariable) = 0;
};

} // namespace stochastic

#endif /* APPROXIMATIONCOMPONENT_H_ */
