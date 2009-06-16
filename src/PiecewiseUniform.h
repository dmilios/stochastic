/*
 * PiecewiseUniform.h
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef PIECEWISEUNIFORM_H_
#define PIECEWISEUNIFORM_H_

#include "ApproximatedDistribution.h"

#include "Uniform.h"

namespace stochastic {

class PiecewiseUniform : public stochastic::ApproximatedDistribution
{
private:
	void fit(std::vector <double>);
	void fit(Distribution *);

public:
	PiecewiseUniform(const char *);
	PiecewiseUniform(Distribution *);
	virtual ~PiecewiseUniform();

	const char * getName();
};

} // namespace stochastic

#endif /* PIECEWISEUNIFORM_H_ */
