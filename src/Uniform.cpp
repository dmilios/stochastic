/*
 * Uniform.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Uniform.h"

namespace stochastic {

Uniform::Uniform()
{
}

Uniform::~Uniform()
{
}

//FIXME: change void to 'array of samples'
void Uniform::sample(int numberOfSamples)
{
}

double Uniform::getWeight()
{
	return this->weight;
}

void Uniform::setWeight(double weight)
{
	this->weight = weight;
}

} // namespace stochastic
