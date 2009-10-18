/*
 * ApproximatedDistribution.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "ApproximationAlgorithm.h"

#include "../utilities/exceptions.h"

#include <iostream>
#include <vector>

#include "../RandomVariable.h"
#include "../distributions/MixtureModel.h"
#include "../distributions/DeltaDistribution.h"
#include "../intermediateResults/InverseRV_Distribution.h"
#include "../intermediateResults/MinOfDistributions.h"
#include "../intermediateResults/MaxOfDistributions.h"

namespace stochastic {

ApproximationAlgorithm::~ApproximationAlgorithm()
{
}

Distribution * ApproximationAlgorithm::approximate(Distribution * target)
{
	if (needsApproximation(target))
		return performApproximation(target);
	return target;
}

/*
 * returns two vectors that define the intervals
 * containing the support of input distribution
 * and the support itself
 *
 * It will be needed for the approximations
 */
double ApproximationAlgorithm::retrieveSupport(Distribution * distribution,
		std::vector<double> & supportInterval_lmargins,
		std::vector<double> & supportInterval_rmargins)
{
	double weight;
	double start = distribution->getLeftMargin();
	double end = distribution->getRightMargin();
	double support = end - start;
	double step = support / (double) numberOfComponents;
	int i;
	double x = start;

	// check for support so as to revise the step
	int flag_inSupport = 0;
	for (i = 0; i < numberOfComponents; i++)
	{
		weight = distribution->pdf(x);
		if (weight)
		{
			if (!flag_inSupport)
			{
				flag_inSupport = 1;
				supportInterval_lmargins.push_back(x);
			}
		}
		else
		{
			if (flag_inSupport)
			{
				flag_inSupport = 0;
				supportInterval_rmargins.push_back(x);
			}
			support -= step;
		}
		x += step;
	}
	if (supportInterval_lmargins.size() > supportInterval_rmargins.size())
		supportInterval_rmargins.push_back(distribution->getRightMargin());
	return support;
}

/*
 *
 *
 * Implementation of pure virtual RandomVariableAlgorithm methods
 *
 * */

RandomVariable ApproximationAlgorithm::calculateSum(RandomVariable & rv1,
		RandomVariable & rv2)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;
	vector<double> resultWeights;

	Distribution * arg1 = approximate(rv1.getDistribution());
	Distribution * arg2 = approximate(rv2.getDistribution());

	vector<MixtureComponent *> components1;
	vector<MixtureComponent *> components2;
	components1 = ((MixtureModel *) arg1)->getComponents();
	components2 = ((MixtureModel *) arg2)->getComponents();
	vector<double> weights1;
	vector<double> weights2;
	weights1 = ((MixtureModel *) arg1)->getWeights();
	weights2 = ((MixtureModel *) arg2)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i, j;

	for (i = 0; i < components1.size(); i++)
		for (j = 0; j < components2.size(); j++)
		{
			currentResult = sumOfComponents(components1[i], components2[j]);
			resultComponents.push_back(currentResult);
			resultWeights.push_back(weights1[i] * weights2[j]);
		}
	return approximate(new MixtureModel(resultComponents, resultWeights));
}

RandomVariable ApproximationAlgorithm::calculateDifference(
		RandomVariable & rv1, RandomVariable & rv2)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;
	vector<double> resultWeights;

	Distribution * arg1 = approximate(rv1.getDistribution());
	Distribution * arg2 = approximate(rv2.getDistribution());

	vector<MixtureComponent *> components1;
	vector<MixtureComponent *> components2;
	components1 = ((MixtureModel *) arg1)->getComponents();
	components2 = ((MixtureModel *) arg2)->getComponents();
	vector<double> weights1;
	vector<double> weights2;
	weights1 = ((MixtureModel *) arg1)->getWeights();
	weights2 = ((MixtureModel *) arg2)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i, j;

	for (i = 0; i < components1.size(); i++)
		for (j = 0; j < components2.size(); j++)
		{
			currentResult = differenceOfComponents(components1[i],
					components2[j]);
			resultComponents.push_back(currentResult);
			resultWeights.push_back(weights1[i] * weights2[j]);
		}
	return approximate(new MixtureModel(resultComponents, resultWeights));
}

RandomVariable ApproximationAlgorithm::calculateProduct(RandomVariable & rv1,
		RandomVariable & rv2)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;
	vector<double> resultWeights;

	Distribution * arg1 = approximate(rv1.getDistribution());
	Distribution * arg2 = approximate(rv2.getDistribution());

	vector<MixtureComponent *> components1;
	vector<MixtureComponent *> components2;
	components1 = ((MixtureModel *) arg1)->getComponents();
	components2 = ((MixtureModel *) arg2)->getComponents();
	vector<double> weights1;
	vector<double> weights2;
	weights1 = ((MixtureModel *) arg1)->getWeights();
	weights2 = ((MixtureModel *) arg2)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i, j;

	for (i = 0; i < components1.size(); i++)
		for (j = 0; j < components2.size(); j++)
		{
			currentResult = productOfComponents(components1[i], components2[j]);
			resultComponents.push_back(currentResult);
			resultWeights.push_back(weights1[i] * weights2[j]);
		}
	return approximate(new MixtureModel(resultComponents, resultWeights));
}

RandomVariable ApproximationAlgorithm::calculateRatio(RandomVariable & rv1,
		RandomVariable & rv2)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;
	vector<double> resultWeights;

	Distribution * arg1 = approximate(rv1.getDistribution());
	Distribution * arg2 = approximate(rv2.getDistribution());

	vector<MixtureComponent *> components1;
	vector<MixtureComponent *> components2;
	components1 = ((MixtureModel *) arg1)->getComponents();
	components2 = ((MixtureModel *) arg2)->getComponents();
	vector<double> weights1;
	vector<double> weights2;
	weights1 = ((MixtureModel *) arg1)->getWeights();
	weights2 = ((MixtureModel *) arg2)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i, j;

	for (i = 0; i < components1.size(); i++)
		for (j = 0; j < components2.size(); j++)
		{
			currentResult = ratioOfComponents(components1[i], components2[j]);
			resultComponents.push_back(currentResult);
			resultWeights.push_back(weights1[i] * weights2[j]);
		}
	return approximate(new MixtureModel(resultComponents, resultWeights));
}

RandomVariable ApproximationAlgorithm::calculateMin(RandomVariable & rv1,
		RandomVariable & rv2)
{
	Distribution * arg1 = rv1.getDistribution();
	Distribution * arg2 = rv2.getDistribution();
	return approximate(new MinOfDistributions(arg1, arg2));
}

RandomVariable ApproximationAlgorithm::calculateMax(RandomVariable & rv1,
		RandomVariable & rv2)
{
	Distribution * arg1 = rv1.getDistribution();
	Distribution * arg2 = rv2.getDistribution();
	return approximate(new MaxOfDistributions(arg1, arg2));
}

/*
 *
 *
 * Functions of ONE random variable
 *
 * */

RandomVariable ApproximationAlgorithm::calculateSum(RandomVariable & rv,
		double c_arg)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = approximate(rv.getDistribution());

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = sumOfComponents(components1[i], c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateDifference(RandomVariable & rv,
		double c_arg)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = approximate(rv.getDistribution());

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = sumOfComponents(components1[i], -c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateDifference(double c_arg,
		RandomVariable & rv)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = approximate(rv.getDistribution());

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = differenceOfComponents(c_arg, components1[i]);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateProduct(RandomVariable & rv,
		double c_arg)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = approximate(rv.getDistribution());

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = productOfComponents(components1[i], c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateRatio(RandomVariable & rv,
		double c_arg)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = approximate(rv.getDistribution());

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = productOfComponents(components1[i], 1 / c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateRatio(double c_arg,
		RandomVariable & rv)
{
	using namespace std;
	vector<MixtureComponent *> resultComponents;

	Distribution * d_arg = new InverseRV_Distribution(rv.getDistribution());
	d_arg = approximate(d_arg);

	vector<MixtureComponent *> components1;
	components1 = ((MixtureModel *) d_arg)->getComponents();
	vector<double> weights1;
	weights1 = ((MixtureModel *) d_arg)->getWeights();
	MixtureComponent * currentResult;
	unsigned int i;

	for (i = 0; i < components1.size(); i++)
	{
		currentResult = productOfComponents(components1[i], c_arg);
		resultComponents.push_back(currentResult);
	}
	return new MixtureModel(resultComponents, weights1);
}

RandomVariable ApproximationAlgorithm::calculateMin(RandomVariable & rv,
		double c_arg)
{
	Distribution * rawResult = new MinOfDistributions(rv.getDistribution(),
			new DeltaDistribution(c_arg));
	return approximate(rawResult);
}

RandomVariable ApproximationAlgorithm::calculateMax(RandomVariable & rv,
		double c_arg)
{
	Distribution * rawResult = new MaxOfDistributions(rv.getDistribution(),
			new DeltaDistribution(c_arg));
	return approximate(rawResult);
}

} // namespace stochastic
