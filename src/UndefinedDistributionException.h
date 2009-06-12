/*
 * UndefinedDistributionException.h
 *
 *  Created on: 09-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef UNDEFINEDDISTRIBUTIONEXCEPTION_H_
#define UNDEFINEDDISTRIBUTIONEXCEPTION_H_

#include <iostream> // for std::exception

namespace stochastic {

class UndefinedDistributionException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "UndefinedDistributionException";
	}
};

} // namespace stochastic

#endif /* UNDEFINEDDISTRIBUTIONEXCEPTION_H_ */
