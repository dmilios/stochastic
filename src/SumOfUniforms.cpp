/*
 * SumUniform.cpp
 *
 *  Created on: 26-Jul-2009
 *      Author: Dimitrios Milios
 */

#include "SumOfUniforms.h"

#include "exceptions.h"
#include <sstream>

namespace stochastic {

// Initialise with U[a1,b1] and U[a2, b2]
SumOfUniforms::SumOfUniforms(double a1, double b1, double a2, double b2)
{
	this->a1 = a1;
	this->b1 = b1;
	this->a2 = a2;
	this->b2 = b2;

	range1 = b1 - a1;
	range2 = b2 - a2;
	a12  = a1 + a2;
	b12 = b1 + b2;
	c1 = (a12 * a12) / (2 * range1 * range2);
	c3 = -(b12 * b12) / (2 * range1 * range2) + 1;

	if (range1 <= 0 || range2 <= 0)
		throw InvalidParametersException("Invalid ranges in sum of uniforms");

	if (a1 + b2 < a2 + b1)
	{
		case_flag = 0;
		c2 = (((a1 + b2) * (a1 + b2) - 2 * a12 * (a1 + b2)) / (2 * range1
				* range2)) + c1 - (a1 + b2) / range1;
	}
	if (a1 + b2 > a2 + b1)
	{
		case_flag = 1;
		c2 = (((a2 + b1) * (a2 + b1) - 2 * a12 * (a2 + b1)) / (2 * range1
				* range2)) + c1 - (a2 + b1) / range2;
	}
	else if (a1 + b2 == a2 + b1)
		case_flag = 2;
}

SumOfUniforms::~SumOfUniforms()
{
}

const char *SumOfUniforms::getName()
{
	std::stringstream alpha1_s;
	std::stringstream beta1_s;
	alpha1_s << a1;
	beta1_s << b1;
	std::stringstream alpha2_s;
	std::stringstream beta2_s;
	alpha2_s << a2;
	beta2_s << b2;

	std::string message = "U(";
	message.append(alpha1_s.str());
	message.append(", ");
	message.append(beta1_s.str());
	message.append(") + U(");
	message.append(alpha2_s.str());
	message.append(", ");
	message.append(beta2_s.str());
	message.append(")");
	return message.c_str();
}

double SumOfUniforms::pdf(double x)
{
	if (x <= getLeftMargin())
		return 0;
	if (x >= getRightMargin())
		return 0;

	switch(case_flag)
	{
		case 0:
			if (x < a1 + b2)
				return (x - a12) / (range1 * range2);
			else if (x < a2 + b1)
				return 1 / range1;
			else // if (x < b1 + b2) // covered in the beginning
				return (-x + b12) / (range1 * range2);
			break;
		case 1:
			if (x < a2 + b1)
				return (x - a12) / (range1 * range2);
			else if (x < a1 + b2)
				return 1 / range2;
			else // if (x < b1 + b2) // covered in the beginning
				return (-x + b12) / (range1 * range2);
			break;
		case 2:
			if (x <= a1 + b2)
				return (x - a12) / (range1 * range2);
			else // if (x < b1 + b2) // cover in the beginning
				return (-x + b12) / (range1 * range2);
			break;
		default:
			break;
	}
	throw 0; // this should never happen
}

double SumOfUniforms::cdf(double x)
{
	if (x <= getLeftMargin())
		return 0;
	if (x >= getRightMargin())
		return 1;

	switch(case_flag)
	{
		case 0:
			if (x < a1 + b2)
				return (x * x - 2 *
						a12 * x) / (2 * range1 * range2) + c1;
			else if (x < a2 + b1)
				return x / range1 + c2;
			else // if (x < b1 + b2) // covered in the beginning
				return (-(x * x) + 2 * b12 * x) / (2 * range1 * range2) + c3;
			break;
		case 1:
			if (x < a2 + b1)
				return (x * x - 2 * a12 * x) / (2 * range1 * range2) + c1;
			else if (x < a1 + b2)
				return x / range2 + c2;
			else // if (x < b1 + b2) // covered in the beginning
				return (-(x * x) + 2 * b12 * x) / (2 * range1 * range2) + c3;
			break;
		case 2:
			if (x <= a1 + b2)
				return (x * x - 2 * a12 * x) / (2 * range1 * range2) + c1;
			else // if (x < b1 + b2) // cover in the beginning
				return (-(x * x) + 2 * b12 * x) / (2 * range1 * range2) + c3;
			break;
		default:
			break;
	}
	throw 0; // this should never happen
}

double SumOfUniforms::getLeftMargin()
{
	return a1 + a2;
}

double SumOfUniforms::getRightMargin()
{
	return b1 + b2;
}

double SumOfUniforms::nextSample()
{
	double maxprob;
	switch(case_flag)
	{
		case 0:
			maxprob = 1 / range1;
			break;
		case 1:
			maxprob = 1 / range2;
			break;
		case 2:
			maxprob = pdf(a1 + b2);
			break;
		default:
			break;
	}
	return rejectionSampling(maxprob, getLeftMargin(), getRightMargin());
}

} // end stochastic
