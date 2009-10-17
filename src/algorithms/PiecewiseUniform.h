/*
 * PiecewiseUniform.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEUNIFORM_H_
#define PIECEWISEUNIFORM_H_

#include "ApproximationAlgorithm.h"


namespace stochastic {

class PiecewiseUniform : public ApproximationAlgorithm
{
private:
	MixtureComponent * sumOfComponents(MixtureComponent *, MixtureComponent *);
	MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent
			* ratioOfComponents(MixtureComponent *, MixtureComponent *);

	MixtureComponent * sumOfComponents(MixtureComponent *, double);
	MixtureComponent * differenceOfComponents(double, MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *, double);

public:
	PiecewiseUniform(int);
	virtual ~PiecewiseUniform();

	int needsApproximation(Distribution *);
	MixtureModel * performApproximation(Distribution *);
	MixtureModel * performApproximation2(Distribution *);
};

} // namespace stochastic

#endif /* PIECEWISEUNIFORM_H_ */
