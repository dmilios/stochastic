/*
 * PiecewiseGaussian.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEGAUSSIAN_H_
#define PIECEWISEGAUSSIAN_H_

#include "PiecewiseBase.h"

#include "Gaussian.h"

namespace stochastic {

class PiecewiseGaussian : public stochastic::PiecewiseBase
{
public:
	PiecewiseGaussian();
	PiecewiseGaussian(const char *);
	PiecewiseGaussian(Distribution *);
	virtual ~PiecewiseGaussian();

	PiecewiseBase * fit(std::vector <double>);
	PiecewiseBase * fit(Distribution *);

	const char * getName();
};

} // namespace stochastic

#endif /* PIECEWISEGAUSSIAN_H_ */
