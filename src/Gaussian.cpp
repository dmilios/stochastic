/*
 * Gaussian.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Gaussian.h"

namespace stochastic {

Gaussian::Gaussian()
{
}

Gaussian::~Gaussian()
{
}

//FIXME: change void to 'array of samples'
void Gaussian::sample(int numberOfSamples)
{
}

double Gaussian::getWeight()
{
	return this->weight;
}

void Gaussian::setWeight(double weight)
{
	this->weight = weight;
}

} // namespace stochastic
