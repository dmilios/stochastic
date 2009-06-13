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
#include <vector>

namespace stochastic {

class ApproximatedDistribution : public stochastic::MixtureModel
{
private:
	std::vector <stochastic::ApproximationComponent> components;

public:
	ApproximatedDistribution();
	virtual ~ApproximatedDistribution();

	double pdf(double);
	double nextSample();
};

} // namespace stochastic

#endif /* APPROXIMATEDDISTRIBUTION_H_ */
