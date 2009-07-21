/*
 * Experiments.h
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#include "../src/stochastic.h"

namespace stochastic {

class Experiments
{
public:
	static double kolmogorovDistance(Distribution *, Distribution *);
	static double KL_Divergence(Distribution *, Distribution *);
	static double hellingerDistance(Distribution *, Distribution *);
};

} // namespace stochastic

#endif /* EXPERIMENTS_H_ */
