/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "ApproximatedDistribution.h"

#include "exceptions.h"

#include <iostream>

namespace stochastic {

FileParser ApproximatedDistribution::parser;

int ApproximatedDistribution::fixedNumberOfComponents = 10;

// Static Method: sets the wanted number of components
void ApproximatedDistribution::setFixedNumberOfComponents(int n)
{
	fixedNumberOfComponents = n;
}

ApproximatedDistribution::~ApproximatedDistribution()
{
}

/**
 * Private Method:
 * fits an 'ApproximatedDistribution' to the data
 * contained in the file 'fileName'
 * */
void ApproximatedDistribution::constructFrom(const char * fileName)
{
	std::vector <double> data;
	data = parser.parseDataFile(fileName);
	fit(data);
}

void ApproximatedDistribution::constructFrom(Distribution * distribution)
{
	fit(distribution);
}

} // namespace stochastic
