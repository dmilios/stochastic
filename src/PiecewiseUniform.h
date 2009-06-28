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
public:
	PiecewiseUniform();
	PiecewiseUniform(const char *);
	PiecewiseUniform(Distribution *);
	virtual ~PiecewiseUniform();

	PiecewiseBase * fit(std::vector <double>);
	PiecewiseBase * fit(Distribution *);

	// NOTE: alternative fit using quantile
	PiecewiseBase * fit2(Distribution * distribution);

	const char * getName();
};

} // namespace stochastic

#endif /* PIECEWISEUNIFORM_H_ */
