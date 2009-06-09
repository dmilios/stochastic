/*
 * Distribution.h
 *
 *  Created on: 06-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

namespace stochastic {

class Distribution
{
public:
	Distribution();
	virtual ~Distribution();

	//FIXME: change void to 'array of samples'
	virtual void sample(int) = 0;
};

} // namespace stochastic

#endif /* DISTRIBUTION_H_ */
