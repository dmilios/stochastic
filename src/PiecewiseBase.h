/*
 * PiecewiseBase.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEBASE_H_
#define PIECEWISEBASE_H_

#include "Distribution.h"
#include "MixtureModel.h"
#include "FileParser.h"
#include <vector>

namespace stochastic {

/**
 * This class defines the interface of the Mixture Models
 * that will be used as approximations of distributions
 *
 * The pure virtual 'fit' methods have to be overridden, so as to
 * define different approximation methods for each approximation class,
 * but a unique interface.
 * */
class PiecewiseBase : public stochastic::MixtureModel
{
protected:
	static int fixedNumberOfComponents;

	virtual MixtureComponent * sumOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * ratioOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * minOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * maxOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;

public:
	virtual PiecewiseBase * fit(Distribution *) = 0;
	virtual const char * getName() = 0;

	// in order to set the global fixedNumberOfComponents
	static void setFixedNumberOfComponents(int);

	MixtureModel * sum(PiecewiseBase *);
	MixtureModel * difference(PiecewiseBase *);
	MixtureModel * product(PiecewiseBase *);
	MixtureModel * ratio(PiecewiseBase *);

	MixtureModel * min(PiecewiseBase *);
	MixtureModel * max(PiecewiseBase *);
};

} // namespace stochastic

#endif /* PIECEWISEBASE_H_ */
