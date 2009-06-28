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
#include "PiecewiseComponent.h"
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
	static FileParser parser;
	static int fixedNumberOfComponents;

public:
	virtual PiecewiseBase * fit(std::vector <double>) = 0;
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
