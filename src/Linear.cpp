/*
 * Linear.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Linear.h"

namespace stochastic {

Linear::Linear()
{
}

Linear::~Linear()
{
}

//FIXME: change void to 'array of samples'
void Linear::sample(int numberOfSamples)
{
}

double Linear::getWeight()
{
	return this->weight;
}

void Linear::setWeight(double weight)
{
	this->weight = weight;
}

} // namespace stochastic
