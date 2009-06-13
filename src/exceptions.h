/*
 * exceptions.h
 *
 *  Created on: 13-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

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

class InvalidParametersException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "InvalidParametersException";
	}
};

class UndefinedDistributionException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "UndefinedDistributionException";
	}
};

} // namespace stochastic


#endif /* EXCEPTIONS_H_ */
