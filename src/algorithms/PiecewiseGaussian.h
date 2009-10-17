/*
 * PiecewiseGaussian.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEGAUSSIAN_H_
#define PIECEWISEGAUSSIAN_H_

#include "ApproximationAlgorithm.h"

#include "../distributions/Gaussian.h"

namespace stochastic {

class PiecewiseGaussian : public stochastic::ApproximationAlgorithm
{
private:
	MixtureComponent * sumOfComponents(MixtureComponent *, MixtureComponent *);
	MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * ratioOfComponents(MixtureComponent *,
			MixtureComponent *);

	MixtureComponent * sumOfComponents(MixtureComponent *, double);
	MixtureComponent * differenceOfComponents(double, MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *, double);

public:
	PiecewiseGaussian(int);
	virtual ~PiecewiseGaussian();

	int needsApproximation(Distribution *);
	MixtureModel * performApproximation(Distribution *);
};

} // namespace stochastic

#endif /* PIECEWISEGAUSSIAN_H_ */
