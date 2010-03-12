/*
 * PG_EM2.h
 *
 *  Created on: 8 Mar 2010
 *      Author: Dimitrios Milios
 */

#ifndef PG_EM2_H_
#define PG_EM2_H_

#include "PiecewiseGaussian.h"
#include <string>

namespace stochastic
{

class PG_EM2: public PiecewiseGaussian
{
private:
	RandomGenerator generator;

public:
	PG_EM2(int);
	virtual ~PG_EM2();

	std::string getName();
	MixtureModel * performApproximation(Distribution *);
};

} // namespace stochastic

#endif /* PG_EM2_H_ */
