/*
 * PiecewiseBase.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEBASE_H_
#define PIECEWISEBASE_H_

#include "../distributions/Distribution.h"
#include "../distributions/MixtureModel.h"
#include "../utilities/FileParser.h"
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
	int fixedNumberOfComponents;

	// returns two vectors that define the intervals
	// containing the support of input distribution
	// and the support itself
	double retrieveSupport(Distribution *, std::vector<double> &, std::vector<
			double> &);

	virtual MixtureComponent * sumOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * differenceOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * productOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;
	virtual MixtureComponent * ratioOfComponents(MixtureComponent *,
			MixtureComponent *) = 0;

	// for functions of ONE random variable
	virtual MixtureComponent * sumOfComponents(MixtureComponent *, double) = 0;
	virtual MixtureComponent * differenceOfComponents(double,
			MixtureComponent *) = 0;
	virtual MixtureComponent
			* productOfComponents(MixtureComponent *, double) = 0;
	virtual MixtureComponent * ratioOfComponents(double, MixtureComponent *) = 0;

public:
	virtual MixtureModel * approximate(Distribution *) = 0;
	virtual const char * getName() = 0;

	// in order to set the global fixedNumberOfComponents
	void setFixedNumberOfComponents(int);

	Distribution * calculateSum(Distribution *, Distribution *);
	Distribution * calculateDifference(Distribution *, Distribution *);
	Distribution * calculateProduct(Distribution *, Distribution *);
	Distribution * calculateRatio(Distribution *, Distribution *);

	Distribution * calculateMin(Distribution *, Distribution *) {};
	Distribution * calculateMax(Distribution *, Distribution *) {};

	// for functions of ONE random variable
	Distribution * calculateSum(Distribution *, double);
	Distribution * calculateDifference(Distribution *, double);
	Distribution * calculateDifference(double, Distribution *) {};
	Distribution * calculateProduct(Distribution *, double);
	Distribution * calculateRatio(Distribution *, double);
	Distribution * calculateRatio(double, Distribution *) {};

	Distribution * calculateMin(Distribution *, double) {};
	Distribution * calculateMax(Distribution *, double) {};
};

} // namespace stochastic

#endif /* PIECEWISEBASE_H_ */
