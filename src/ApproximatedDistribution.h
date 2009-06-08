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

namespace stochastic {

class ApproximatedDistribution : public stochastic::Distribution {
private:
	stochastic::MixtureModel approximation;

public:
	ApproximatedDistribution();
	virtual ~ApproximatedDistribution();

	//FIXME: change void to 'array of samples'
	void sample(int);
};

} // namespace stochastic

#endif /* APPROXIMATEDDISTRIBUTION_H_ */
