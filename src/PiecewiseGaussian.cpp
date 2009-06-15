/*
 * PiecewiseGaussian.cpp
 *
 *  Created on: 15-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "PiecewiseGaussian.h"

namespace stochastic {

PiecewiseGaussian::PiecewiseGaussian(const char * fileName)
{
	this->constructFrom(fileName);
}

PiecewiseGaussian::PiecewiseGaussian(Distribution * distribution)
{
	this->constructFrom(distribution);
}

PiecewiseGaussian::~PiecewiseGaussian()
{
}

void PiecewiseGaussian::fit(std::vector <double> data)
{
}

void PiecewiseGaussian::fit(Distribution * distribution)
{
}

} // namespace stochastic
