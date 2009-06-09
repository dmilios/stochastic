/*
 * MixtureComponent.h
 *
 *  Created on: 09-Jun-2009
 *      Author: Dimitrios Milios
 *
 *
 *  This class serves as an "interface", so as to
 *  group the distributions that can be parts of mixture models.
 *
 *  In fact, any distribution could be part of a Mixture Model
 *  except for MixtureModel instances
 *
 *  All the 'distribution' classes
 *  that are not subclasses of MixtureModel
 *  should inherit from 'this' class,
 *  instead of inheriting from Distribution class directly
 */

#ifndef MIXTURECOMPONENT_H_
#define MIXTURECOMPONENT_H_

#include "Distribution.h"

namespace stochastic {

class MixtureComponent : public stochastic::Distribution
{
};

}

#endif /* MIXTURECOMPONENT_H_ */
