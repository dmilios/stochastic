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

	//FIXME: change void to 'array of samples'
	void sample(int);
};

} // namespace stochastic

#endif /* EXPONENTIAL_H_ */
