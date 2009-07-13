/*
 * EmpiricalDistribution.cpp
 *
 *  Created on: 24-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "EmpiricalDistribution.h"

#include "FileParser.h"
#include <algorithm>
#include <cmath>

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


//	int accuracy = 100;
//	double dx = (getRightMargin() - getLeftMargin()) / accuracy;
//	return (cdf(x + dx) - cdf(x)) / dx;


	double h = 0.1;
	unsigned int n = this->data.size();

	double sum = 0;
	unsigned int i;
	for (i = 0; i < n; i++)
		sum += (1 / sqrt(2 * 3.14)) * exp(-pow(x - data[i], 2) / (2 * pow(h, 2)));
	return sum / (n * h);
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
	static int * buffer = 0;
	if (buffer)
		return data[* buffer];

	// discard the first 1%
	unsigned int i = 0;
	for (i = 0; i < data.size(); i++)
		if (cdf(data[i]) > 0.01)
		{
			buffer = new int;
			* buffer = i;
			return data[i];
		}
	return data[0]; // data is sorted in ascending order
}

double EmpiricalDistribution::getRightMargin()
{
	static int * buffer = 0;
	if (buffer)
		return data[* buffer];

	// discard the last 1%
	unsigned int i = 0;
	for (i = data.size() - 1; i > 0; i--)
		if (cdf(data[i]) < 0.99)
		{
			buffer = new int;
			* buffer = i;
			return data[i];
		}
	return data[data.size() - 1]; // data is sorted in ascending order
}

double EmpiricalDistribution::nextSample()
{
	return rejectionSampling(maxProbability, getLeftMargin(), getRightMargin());
}

} // namespace stochastic
