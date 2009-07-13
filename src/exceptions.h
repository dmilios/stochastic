/*
 * exceptions.h
 *
 *  Created on: 13-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream> // for std::exception
#include <string>

namespace stochastic {

class IncompatibleComponentsException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "IncompatibleComponentsException";
	}
};

class InvalidParametersException : public std::exception
{
public:
	InvalidParametersException()
	{
	}

	InvalidParametersException(std::string message)
	{
		std::cerr << message.c_str() << std::endl;
	}

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

class FileNotFoundException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "FileNotFoundException";
	}
};

class InvalidDataFileException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "InvalidDataFileException";
	}
};

class InvalidWeightsException : public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return "InvalidWeightsException";
	}
};

} // namespace stochastic


#endif /* EXCEPTIONS_H_ */
