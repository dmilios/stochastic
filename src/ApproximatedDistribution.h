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
	void fit(const char *);
	void fit(std::vector <double>);
	void fit(Distribution *);

public:
	ApproximatedDistribution();
	ApproximatedDistribution(const char *);
	virtual ~ApproximatedDistribution();

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double nextSample();
};

} // namespace stochastic

#endif /* APPROXIMATEDDISTRIBUTION_H_ */
