/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "ApproximatedDistribution.h"

#include "exceptions.h"
#include "FileParser.h"

namespace stochastic {

ApproximatedDistribution::ApproximatedDistribution()
{
}

ApproximatedDistribution::ApproximatedDistribution(const char * fileName)
{
	fit(fileName);
}

ApproximatedDistribution::~ApproximatedDistribution()
{
}

/**
 * Private Method:
 * fits an 'ApproximatedDistribution' to the data
 * contained in the file 'fileName'
 * */
void ApproximatedDistribution::fit(const char * fileName)
{
	std::vector <double> data;
	FileParser parser;
	data = parser.parseDataFile(fileName);
	fit(data);
}

void ApproximatedDistribution::fit(std::vector <double> data)
{
}

/**
 * Private Method:
 * fits an 'ApproximatedDistribution' to the given distribution
 * */
void ApproximatedDistribution::fit(Distribution * distribution)
{
}

const char * ApproximatedDistribution::getName()
{
	return "appr";
}

double ApproximatedDistribution::pdf(double x)
{
	return 0;
}

double ApproximatedDistribution::nextSample()
{
	return 0;
}

} // namespace stochastic
