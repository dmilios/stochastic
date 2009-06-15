/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "ApproximatedDistribution.h"

#include "exceptions.h"
#include "FileParser.h"
#include <sstream>

namespace stochastic {

int ApproximatedDistribution::fixedNumberOfComponents = 10;

// Static Method: sets the wanted number of components
void ApproximatedDistribution::setFixedNumberOfComponents(int n)
{
	fixedNumberOfComponents = n;
}

ApproximatedDistribution::ApproximatedDistribution(const char * fileName)
{
	this->fit(fileName);
}

ApproximatedDistribution::ApproximatedDistribution(Distribution * distribution)
{
	this->fit(distribution);
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

/**
 * Private Method:
 * fits an 'ApproximatedDistribution' to the data stored in the vector
 * */
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
	std::stringstream numberOfComponents_s;
	numberOfComponents_s << this->components.size();
	std::string firstComponent(components[0]->getName());

	std::string name("ap");
	name.append(numberOfComponents_s.str());
	name.append("_");
	name.append(firstComponent);
	return name.c_str();
}

} // namespace stochastic
