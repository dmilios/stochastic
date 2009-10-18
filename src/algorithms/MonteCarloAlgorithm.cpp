/*
 * MonteCarloAlgorithm.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "MonteCarloAlgorithm.h"

#include "../distributions/EmpiricalDistribution.h"
#include "../distributions/DeltaDistribution.h"
#include <stdexcept> // for std::out_of_range
#include <typeinfo>

namespace stochastic {

MonteCarloAlgorithm::MonteCarloAlgorithm(int samples)
{
	this->numberOfSamples = samples;
}

MonteCarloAlgorithm::~MonteCarloAlgorithm()
{
}

double MonteCarloAlgorithm::recursiveSampling(RandomVariable & arg1,
		RandomVariable & arg2, map<string, double> visited_ids)
{
	double sample1;
	double sample2;
	try
	{
		sample1 = visited_ids.at(arg1.getRandomVariableID());
	}
	catch (out_of_range ex)
	{
		if (typeid(arg1) == typeid(DeltaDistribution))
			sample1 = arg1.getDistribution()->nextSample();
		else if (graph->isTerminal(arg1))
			sample1 = arg1.getDistribution()->nextSample();
		else
		{
			RandomVariable p1 = graph->getParent1For(arg1);
			RandomVariable p2 = graph->getParent2For(arg1);
			sample1 = recursiveSampling(p1, p2, visited_ids);
		}
		visited_ids[arg1.getRandomVariableID()] = sample1;
	}
	try
	{
		sample2 = visited_ids.at(arg2.getRandomVariableID());
	}
	catch (std::out_of_range ex)
	{
		if (typeid(arg2) == typeid(DeltaDistribution))
			sample2 = arg2.getDistribution()->nextSample();
		else if (graph->isTerminal(arg2))
			sample2 = arg2.getDistribution()->nextSample();
		else
		{
			RandomVariable p1 = graph->getParent1For(arg2);
			RandomVariable p2 = graph->getParent2For(arg2);
			sample2 = recursiveSampling(p1, p2, visited_ids);
		}
		visited_ids[arg2.getRandomVariableID()] = sample2;
	}

	return sample1 + sample2;
}

RandomVariable MonteCarloAlgorithm::calculateSum(RandomVariable & rv1,
		RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(rv1, rv2, visited_ids));
	}
	return new EmpiricalDistribution(produced_data);
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
