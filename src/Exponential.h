/*
 * Exponential.h
 *
 *  Created on: 08-Jun-2009
 *      Author: dimitrios
 */

#ifndef EXPONENTIAL_H_
#define EXPONENTIAL_H_

#include "MixtureComponent.h"

namespace stochastic {

class Exponential : public stochastic::MixtureComponent
{
public:
	Exponential();
	virtual ~Exponential();

	// overload virtual methods of Distribution
	double nextSample();
};

} // namespace stochastic

#endif /* EXPONENTIAL_H_ */
