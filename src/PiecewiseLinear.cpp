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
	std::vector <double> data;
	data = parser.parseDataFile(fileName);
	this->fit(data);
}

PiecewiseLinear::PiecewiseLinear(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	this->fit(distribution);
}

PiecewiseLinear::~PiecewiseLinear()
{
}

const char * PiecewiseLinear::getName()
{
	return "pLin";
}

void PiecewiseLinear::fit(std::vector <double> data)
{
}

void PiecewiseLinear::fit(Distribution * distribution)
{
}

} // namespace stochastic
