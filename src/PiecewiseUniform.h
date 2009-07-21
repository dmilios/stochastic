/*
 * PiecewiseUniform.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEUNIFORM_H_
#define PIECEWISEUNIFORM_H_

#include "PiecewiseBase.h"

#include "Uniform.h"

namespace stochastic {

class PiecewiseUniform : public stochastic::PiecewiseBase
{
private:
	MixtureComponent * sumOfComponents(MixtureComponent *, MixtureComponent *);
	MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * ratioOfComponents(MixtureComponent *,
			MixtureComponent *);
	MixtureComponent * minOfComponents(MixtureComponent *, MixtureComponent *);
	MixtureComponent * maxOfComponents(MixtureComponent *, MixtureComponent *);

	MixtureComponent * sumOfComponents(MixtureComponent *, double);
	MixtureComponent * differenceOfComponents(double, MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *, double);
	MixtureComponent * ratioOfComponents(double, MixtureComponent *);
	MixtureComponent * minOfComponents(MixtureComponent *, double);
	MixtureComponent * maxOfComponents(MixtureComponent *, double);


public:
	PiecewiseUniform();
	PiecewiseUniform(Distribution *);
	virtual ~PiecewiseUniform();

	PiecewiseBase * fit(Distribution *);
	const char * getName();

	// NOTE: alternative fit using quantile
	PiecewiseBase * fit2(Distribution * distribution);
};

} // namespace stochastic

#endif /* PIECEWISEUNIFORM_H_ */
