/*
 * ApproximatedDistribution.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef APPROXIMATEDDISTRIBUTION_H_
#define APPROXIMATEDDISTRIBUTION_H_

#include "Distribution.h"
#include "MixtureModel.h"
#include "ApproximationComponent.h"
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
class ApproximatedDistribution : public stochastic::MixtureModel
{
protected:
	static FileParser parser;
	static int fixedNumberOfComponents;

	virtual void fit(std::vector <double>) = 0;
	virtual void fit(Distribution *) = 0;

public:
	virtual const char * getName() = 0;

	// in order to set the global fixedNumberOfComponents
    static void setFixedNumberOfComponents(int);
};

} // namespace stochastic

#endif /* APPROXIMATEDDISTRIBUTION_H_ */
