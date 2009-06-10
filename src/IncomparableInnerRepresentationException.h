/*
 * IncomparableInnerRepresentationException.h
 *
 *  Created on: 10-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef INCOMPARABLEINNERREPRESENTATIONEXCEPTION_H_
#define INCOMPARABLEINNERREPRESENTATIONEXCEPTION_H_

#include <iostream> // for std::exception

namespace stochastic {

class IncomparableInnerRepresentationException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "IncomparableInnerRepresentationException";
	}
};

}

#endif /* INCOMPARABLEINNERREPRESENTATIONEXCEPTION_H_ */
