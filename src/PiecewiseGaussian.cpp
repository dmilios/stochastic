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
	std::vector <double> data;
	data = parser.parseDataFile(fileName);
	this->fit(data);
}

PiecewiseGaussian::PiecewiseGaussian(Distribution * distribution)
{
	if (!distribution)
		throw stochastic::UndefinedDistributionException();

	this->fit(distribution);
}

PiecewiseGaussian::~PiecewiseGaussian()
{
}

const char * PiecewiseGaussian::getName()
{
	return "pNorm";
}

void PiecewiseGaussian::fit(std::vector <double> data)
{
}

void PiecewiseGaussian::fit(Distribution * distribution)
{
}

} // namespace stochastic
