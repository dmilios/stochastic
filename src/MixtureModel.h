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
#include "exceptions.h"
#include <vector>

namespace stochastic {

class MixtureModel : public stochastic::Distribution
{
private:
	std::vector <stochastic::MixtureComponent *> components;

protected:
	std::vector <double> weights;
	std::vector <double> cumulativeWeights; // needed for sampling

	// This constructor exists just to be inherited
	// it should not be visible out of the class
	// No empty Mixture Models are allows to be declared
	MixtureModel()
	{
	}

public:
	MixtureModel(std::vector <MixtureComponent *>, std::vector <double>);
	virtual ~MixtureModel();

	// overload virtual methods of Distribution
	virtual const char * getName();
	double pdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();
};

} // namespace stochastic

#endif /* MIXTUREMODEL_H_ */
