/*
 * PiecewiseComponent.h
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

#ifndef PIECEWISECOMPONENT_H_
#define PIECEWISECOMPONENT_H_

#include "MixtureComponent.h"

namespace stochastic {

class PiecewiseComponent : public stochastic::MixtureComponent
{
public:
	virtual MixtureComponent * sum(PiecewiseComponent *) = 0;
	virtual MixtureComponent * difference(PiecewiseComponent *) = 0;
	virtual MixtureComponent * product(PiecewiseComponent *) = 0;
	virtual MixtureComponent * ratio(PiecewiseComponent *) = 0;

	virtual MixtureComponent * min(PiecewiseComponent *) = 0;
	virtual MixtureComponent * max(PiecewiseComponent *) = 0;
};

} // namespace stochastic

#endif /* PIECEWISECOMPONENT_H_ */
