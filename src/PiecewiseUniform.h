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

	MixtureComponent * sumOfComponents(MixtureComponent *, double);
	MixtureComponent * differenceOfComponents(double, MixtureComponent *);
	MixtureComponent * productOfComponents(MixtureComponent *, double);
	MixtureComponent * ratioOfComponents(double, MixtureComponent *);


public:
	PiecewiseUniform();
	PiecewiseUniform(Distribution *);
	virtual ~PiecewiseUniform();

	PiecewiseBase * fit(Distribution *);
	PiecewiseBase * fit2(Distribution *);
	const char * getName();


	// TODO: isolate discretization in another class
	static int useold; // TO BE DISCARDED, just for the experiment
};

} // namespace stochastic

#endif /* PIECEWISEUNIFORM_H_ */
