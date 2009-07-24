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

	// returns two vectors that define the intervals
	// containing the support of input distribution
	// and the support itself
	double retrieveSupport(Distribution *, std::vector<double> &,
			std::vector<double> &);

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

	// for functions of ONE random variable
	virtual MixtureComponent * sumOfComponents(MixtureComponent *,
			double) = 0;
	virtual MixtureComponent * differenceOfComponents(double,
			MixtureComponent *) = 0;
	virtual MixtureComponent * productOfComponents(MixtureComponent *,
			double) = 0;
	virtual MixtureComponent * ratioOfComponents(double,
			MixtureComponent *) = 0;
	virtual MixtureComponent * minOfComponents(MixtureComponent *,
			double) = 0;
	virtual MixtureComponent * maxOfComponents(MixtureComponent *,
			double) = 0;


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


	// for functions of ONE random variable
	MixtureModel * sum(double);
	MixtureModel * differenceFrom(double);
	MixtureModel * product(double);
	MixtureModel * denominatorOf(double);
	MixtureModel * min(double);
	MixtureModel * max(double);
};

} // namespace stochastic

#endif /* PIECEWISEBASE_H_ */
