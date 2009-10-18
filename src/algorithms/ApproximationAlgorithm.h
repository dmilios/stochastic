/*
 * ApproximationAlgorithm.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef APPROXIMATIONALGORITHM_H_
#define APPROXIMATIONALGORITHM_H_

#include "RandomVariableAlgorithm.h"

#include "../RandomVariable.h"
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
class ApproximationAlgorithm : public RandomVariableAlgorithm
{
protected:
	int numberOfComponents;

	/* returns two vectors that define the intervals
	 * containing the support of input distribution
	 * and the support itself */
	double retrieveSupport(Distribution *, std::vector<double> &, std::vector<
			double> &);

public:
	virtual ~ApproximationAlgorithm();
	Distribution * approximate(Distribution *);

	RandomVariable calculateSum(RandomVariable &, RandomVariable &);
	RandomVariable calculateDifference(RandomVariable &, RandomVariable &);
	RandomVariable calculateProduct(RandomVariable &, RandomVariable &);
	RandomVariable calculateRatio(RandomVariable &, RandomVariable &);

	RandomVariable calculateMin(RandomVariable &, RandomVariable &);
	RandomVariable calculateMax(RandomVariable &, RandomVariable &);

	// for functions of ONE random variable
	RandomVariable calculateSum(RandomVariable &, double);
	RandomVariable calculateDifference(RandomVariable &, double);
	RandomVariable calculateDifference(double, RandomVariable &);
	RandomVariable calculateProduct(RandomVariable &, double);
	RandomVariable calculateRatio(RandomVariable &, double);
	RandomVariable calculateRatio(double, RandomVariable &);

	RandomVariable calculateMin(RandomVariable &, double);
	RandomVariable calculateMax(RandomVariable &, double);

	/*
	 *
	 *
	 * Pure Virtual Methods
	 *
	 * */
protected:
	virtual int needsApproximation(Distribution *) = 0;
	virtual MixtureModel * performApproximation(Distribution *) = 0;

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
};

} // namespace stochastic

#endif /* APPROXIMATIONALGORITHM_H_ */
