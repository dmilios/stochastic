/*
 * PiecewiseLinear.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseLinear.h"

namespace stochastic {

PiecewiseLinear::PiecewiseLinear(const char * fileName)
{
	this->constructFrom(fileName);
}

PiecewiseLinear::PiecewiseLinear(Distribution * distribution)
{
	this->constructFrom(distribution);
}

PiecewiseLinear::~PiecewiseLinear()
{
}

void PiecewiseLinear::fit(std::vector <double> data)
{
}

void PiecewiseLinear::fit(Distribution * distribution)
{
}

} // namespace stochastic
