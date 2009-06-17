/*
 * PiecewiseGaussian.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEGAUSSIAN_H_
#define PIECEWISEGAUSSIAN_H_

#include "ApproximatedDistribution.h"

#include "Gaussian.h"

namespace stochastic {

class PiecewiseGaussian : public stochastic::ApproximatedDistribution
{
private:
	void fit(std::vector <double>);
	void fit(Distribution *);

public:
	PiecewiseGaussian(const char *);
	PiecewiseGaussian(Distribution *);
	virtual ~PiecewiseGaussian();

	const char * getName();
};

} // namespace stochastic

#endif /* PIECEWISEGAUSSIAN_H_ */
