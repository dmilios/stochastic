/*
 * PiecewiseUniform.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseUniform.h"

namespace stochastic {

PiecewiseUniform::PiecewiseUniform(const char * fileName)
{
	this->constructFrom(fileName);
}

PiecewiseUniform::PiecewiseUniform(Distribution * distribution)
{
	this->constructFrom(distribution);
}

PiecewiseUniform::~PiecewiseUniform()
{
}

void PiecewiseUniform::fit(std::vector <double> data)
{
}

void PiecewiseUniform::fit(Distribution * distribution)
{
}

} // namespace stochastic
