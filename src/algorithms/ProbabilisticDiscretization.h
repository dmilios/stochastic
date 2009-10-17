/*
 * ProbabilisticDiscretization.h
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#ifndef PROBABILISTICDISCRETIZATION_H_
#define PROBABILISTICDISCRETIZATION_H_

#include "PiecewiseUniform.h"

#include "../distributions/MixtureModel.h"
#include "../distributions/MixtureComponent.h"

namespace stochastic {

class ProbabilisticDiscretization : public PiecewiseUniform
{
private:
	MixtureComponent * sumOfComponents(MixtureComponent *, MixtureComponent *);
	MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent
			* ratioOfComponents(MixtureComponent *, MixtureComponent *);
};

} // namespace stochastic

#endif /* PROBABILISTICDISCRETIZATION_H_ */
