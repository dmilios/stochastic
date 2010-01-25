/*
 * PU_DivideAndConquer.h
 *
 *  Created on: 15 Nov 2009
 *      Author: Dimitrios Milios
 */

#ifndef PU_DIVIDEANDCONQUER_H_
#define PU_DIVIDEANDCONQUER_H_

#include "PiecewiseUniform.h"

namespace stochastic
{

class PU_DivideAndConquer: public PiecewiseUniform
{
private:
	void approximateInterval(std::vector<MixtureComponent *> &, std::vector<
			double> &, int, double, double, Distribution *);
	double errorMeasure(MixtureComponent *, double, Distribution *);

public:
	PU_DivideAndConquer(int);
	virtual ~PU_DivideAndConquer();

	std::string getName();
	MixtureModel * performApproximation(Distribution *);
};

} // namespace stochastic

#endif /* PU_DIVIDEANDCONQUER_H_ */
