/*
 * MonteCarloOperations.cpp
 *
 *  Created on: 24-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "MonteCarloOperations.h"

#include "EmpiricalDistribution.h"
#include <vector>
#include <algorithm>

namespace stochastic {

int MonteCarloOperations::numberOfSamples = 10000;

void MonteCarloOperations::setNumberOfSamples(int n)
{
	numberOfSamples = n;
}

/*
 *
 * --- Standard Binary Operations: '+', '-', '*', '/'
 */

RandomVariable MonteCarloOperations::add(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(s1[i] + s2[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::subtract(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(s1[i] - s2[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::multiply(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(s1[i] * s2[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::divide(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
	{
		if (!s2[i])
			s2[i] = 0.0000001;
		produced_data.push_back(s1[i] / s2[i]);
	}
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

/*
 *
 * --- Binary Operations: min, max
 */

RandomVariable MonteCarloOperations::min(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::min<double>(s1[i], s2[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::max(RandomVariable arg1,
		RandomVariable arg2)
{
	std::vector<double> s1 = arg1.getDistribution()->sample(numberOfSamples);
	std::vector<double> s2 = arg2.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::max<double>(s1[i], s2[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

} // namespace stochastic
