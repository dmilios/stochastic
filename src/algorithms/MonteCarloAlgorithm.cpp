/*
 * MonteCarloAlgorithm.cpp
 *
 *  Created on: 17-Oct-2009
 *      Author: Dimitrios Milios
 */

#include "MonteCarloAlgorithm.h"

#include "../distributions/EmpiricalDistribution.h"
#include "../distributions/HistogramDistribution.h"
#include "../distributions/DeltaDistribution.h"
#include <stdexcept> // for std::out_of_range
#include <typeinfo>

namespace stochastic
{

MonteCarloAlgorithm::MonteCarloAlgorithm(int samples)
{
	this->numberOfSamples = samples;
	this->discardSamplesFlag = 1;
}

/** First argument: number of samples to be drawn at each step
 * Second argument: a flag indicating if the samples should be discarded at each step
 * ('0' for not discarding the samples) */
MonteCarloAlgorithm::MonteCarloAlgorithm(int samples, int flag)
{
	this->numberOfSamples = samples;
	this->discardSamplesFlag = flag;
}

MonteCarloAlgorithm::~MonteCarloAlgorithm()
{
}

string MonteCarloAlgorithm::getName()
{
	return string("Monte Carlo");
}

double MonteCarloAlgorithm::recursiveSampling(OperationType operationType,
		RandomVariable & arg1, RandomVariable & arg2,
		map<string, double> & visited_ids)
{
	double sample1;
	double sample2;
	try
	{
		sample1 = visited_ids.at(arg1.getRandomVariableID());
	} catch (out_of_range ex)
	{
		if (typeid(arg1) == typeid(DeltaDistribution))
			sample1 = arg1.getDistribution()->nextSample();
		else if (graph->isTerminal(arg1))
			sample1 = arg1.getDistribution()->nextSample();
		else
		{
			RandomVariable p1 = graph->getParent1For(arg1);
			RandomVariable p2 = graph->getParent2For(arg1);
			OperationType type = graph->getOperationTypeFor(arg1);
			sample1 = recursiveSampling(type, p1, p2, visited_ids);
		}
		visited_ids[arg1.getRandomVariableID()] = sample1;
	}
	try
	{
		sample2 = visited_ids.at(arg2.getRandomVariableID());
	} catch (std::out_of_range ex)
	{
		if (typeid(arg2) == typeid(DeltaDistribution))
			sample2 = arg2.getDistribution()->nextSample();
		else if (graph->isTerminal(arg2))
			sample2 = arg2.getDistribution()->nextSample();
		else
		{
			RandomVariable p1 = graph->getParent1For(arg2);
			RandomVariable p2 = graph->getParent2For(arg2);
			OperationType type = graph->getOperationTypeFor(
					arg2);
			sample2 = recursiveSampling(type, p1, p2, visited_ids);
		}
		visited_ids[arg2.getRandomVariableID()] = sample2;
	}

	switch (operationType)
	{
	case SUM:
		return sample1 + sample2;
		break;
	case DIFFERENCE:
		return sample1 - sample2;
		break;
	case PRODUCT:
		return sample1 * sample2;
		break;
	case RATIO:
		if (sample2 == 0)
			sample2 = 0.0001;
		return sample1 / sample2;
		break;
	case MIN:
		return std::min<double>(sample1, sample2);
		break;
	case MAX:
		return std::max<double>(sample1, sample2);
		break;
	default:
		break;
	}
	throw 0; // this should never happen
}

RandomVariable MonteCarloAlgorithm::calculateSum(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(SUM, rv1,
				rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateDifference(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(DIFFERENCE,
				rv1, rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateProduct(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(PRODUCT, rv1,
				rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateRatio(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(RATIO, rv1,
				rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateMin(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(MIN, rv1,
				rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateMax(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(MAX, rv1,
				rv2, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

/*
 *
 *
 * Functions of one random variable
 *
 * */

 RandomVariable MonteCarloAlgorithm::calculateSum(
		 RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(SUM, rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateDifference(
		RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(DIFFERENCE,
				rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateDifference(
		double c_arg, RandomVariable & rv)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(DIFFERENCE,
				delta, rv, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateProduct(
		RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(PRODUCT, rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateRatio(
		RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(RATIO, rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateRatio(
		double c_arg, RandomVariable & rv)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(RATIO, delta, rv, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateMin(
		RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(MIN, rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

RandomVariable MonteCarloAlgorithm::calculateMax(
		RandomVariable & rv, double c_arg)
{
	using namespace std;
	vector<double> produced_data;

	int i;
	RandomVariable delta = new DeltaDistribution(c_arg);
	for (i = 0; i < numberOfSamples; i++)
	{
		map<string, double> visited_ids;
		produced_data.push_back(recursiveSampling(MAX, rv, delta, visited_ids));
	}
	if (discardSamplesFlag)
		return new HistogramDistribution(produced_data);
	return new EmpiricalDistribution(produced_data);
}

} // namespace stochastic
