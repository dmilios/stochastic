/*
 * EmpiricalDistribution.cpp
 *
 *  Created on: 24-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "EmpiricalDistribution.h"

#include "FileParser.h"
#include <algorithm>

namespace stochastic {

EmpiricalDistribution::EmpiricalDistribution(const char * fileName)
{
	FileParser parser;
	data = parser.parseDataFile(fileName);
	std::sort(data.begin(), data.end());

	this->name = "emp_";
	this->name.append(fileName);

	// compute maxProbability which will be used in rejection sampling
	int accuracy = 100, i;
	double currProbability;
	double dx = (getRightMargin() - getLeftMargin()) / accuracy;
	double x = getLeftMargin();
	for (i = 0; i < accuracy; i++)
	{
		currProbability = (cdf(x + dx) - cdf(x)) / dx;
		if (currProbability > maxProbability)
			maxProbability = currProbability;
		x += dx;
	}
}

EmpiricalDistribution::EmpiricalDistribution(std::vector<double> inputData)
{
	data = inputData;
	std::sort(data.begin(), data.end());

	this->name = "emp";

	// compute maxProbability which will be used in rejection sampling
	int accuracy = 100, i;
	double currProbability;
	double dx = (getRightMargin() - getLeftMargin()) / accuracy;
	double x = getLeftMargin();
	for (i = 0; i < accuracy; i++)
	{
		currProbability = (cdf(x + dx) - cdf(x)) / dx;
		if (currProbability > maxProbability)
			maxProbability = currProbability;
		x += dx;
	}
}

EmpiricalDistribution::~EmpiricalDistribution()
{
}

const char * EmpiricalDistribution::getName()
{
	return name.c_str();
}

double EmpiricalDistribution::pdf(double x)
{
	if (x < getLeftMargin() || x > getRightMargin())
		return 0;

	int accuracy = 100;
	double dx = (getRightMargin() - getLeftMargin()) / accuracy;
	return (cdf(x + dx) - cdf(x)) / dx;
}

double EmpiricalDistribution::cdf(double x)
{
	unsigned int i;
	for (i = 0; i < data.size(); i++)
		if (data[i] > x)
			return (double) i / (double) data.size();
	return 1;
}

double EmpiricalDistribution::getLeftMargin()
{
	return data[0]; // data is sorted in ascending order
}

double EmpiricalDistribution::getRightMargin()
{
	return data[data.size() - 1]; // data is sorted in ascending order
}

double EmpiricalDistribution::nextSample()
{
	return rejectionSampling(maxProbability, getLeftMargin(), getRightMargin());
}

} // namespace stochastic
