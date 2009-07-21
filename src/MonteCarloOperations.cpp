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

RandomVariable MonteCarloOperations::sum(RandomVariable arg1,
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

RandomVariable MonteCarloOperations::difference(RandomVariable arg1,
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

RandomVariable MonteCarloOperations::product(RandomVariable arg1,
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

RandomVariable MonteCarloOperations::ratio(RandomVariable arg1,
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

/*
 *
 *
 *
 * Functions of ONE random variable
 *
 *
 * */

RandomVariable MonteCarloOperations::sum(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(c_arg + s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::difference(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(c_arg - s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::product(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(c_arg * s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::ratio(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
	{
		if (!s[i])
			s[i] = 0.0000001;
		produced_data.push_back(c_arg / s[i]);
	}
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::min(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::min<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::max(double c_arg, RandomVariable rv_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::max<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::sum(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(c_arg + s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::difference(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(s[i] - c_arg);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::product(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(c_arg * s[i]);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::ratio(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	if (!c_arg)
		c_arg = 0.0000001;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(s[i] / c_arg);
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::min(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::min<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

RandomVariable MonteCarloOperations::max(RandomVariable rv_arg, double c_arg)
{
	std::vector<double> s = rv_arg.getDistribution()->sample(numberOfSamples);
	int i;
	std::vector<double> produced_data;
	for (i = 0; i < numberOfSamples; i++)
		produced_data.push_back(std::max<double>(c_arg, s[i]));
	return RandomVariable(new EmpiricalDistribution(produced_data));
}

} // namespace stochastic
