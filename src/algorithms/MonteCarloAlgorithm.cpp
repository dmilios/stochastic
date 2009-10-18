/*
 * MonteCarloAlgorithm.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "MonteCarloAlgorithm.h"

namespace stochastic {

MonteCarloAlgorithm::MonteCarloAlgorithm(int samples)
{
	this->numberOfSamples = samples;
}

MonteCarloAlgorithm::~MonteCarloAlgorithm()
{
}

RandomVariable MonteCarloAlgorithm::calculateSum(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateDifference(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateProduct(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateRatio(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateMin(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateMax(RandomVariable & rv1,
		RandomVariable & rv2)
{
	return 0;
}

/*
 *
 *
 * Functions of one random variable
 *
 * */

RandomVariable MonteCarloAlgorithm::calculateSum(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateDifference(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateDifference(double c_arg,
		RandomVariable & rv)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateProduct(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateRatio(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateRatio(double c_arg,
		RandomVariable & rv)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateMin(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

RandomVariable MonteCarloAlgorithm::calculateMax(RandomVariable & rv,
		double c_arg)
{
	return 0;
}

} // namespace stochastic
