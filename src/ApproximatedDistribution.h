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
	static int fixedNumberOfComponents;

	std::vector <stochastic::ApproximationComponent *> components;
	void fit(const char *);
	void fit(std::vector <double>);
	void fit(Distribution *);

public:
	ApproximatedDistribution(const char *);
	ApproximatedDistribution(Distribution *);
	virtual ~ApproximatedDistribution();

    static void setFixedNumberOfComponents(int);

    const char *getName();
};

} // namespace stochastic

#endif /* APPROXIMATEDDISTRIBUTION_H_ */
