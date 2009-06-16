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

} // namespace stochastic
