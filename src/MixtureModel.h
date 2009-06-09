/*
 * MixtureModel.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef MIXTUREMODEL_H_
#define MIXTUREMODEL_H_

#include "Distribution.h"
#include "MixtureComponent.h"
#include <vector>

namespace stochastic {

class MixtureModel : public stochastic::Distribution
{
private:
	std::vector <stochastic::MixtureComponent> components;

protected:
	double numberOfComponents;
	std::vector <double> weights;

public:
	MixtureModel();
	virtual ~MixtureModel();

	//FIXME: change void to 'array of samples'
	void sample(int);
};

} // namespace stochastic

#endif /* MIXTUREMODEL_H_ */
