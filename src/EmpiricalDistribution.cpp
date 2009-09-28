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
#include <sstream>
#include "mathFunctions.h"

namespace stochastic {

EmpiricalDistribution::EmpiricalDistribution(const char * fileName)
{
	FileParser parser;
	data = parser.parseDataFile(fileName);
	std::sort(data.begin(), data.end());

	this->name = "emp_";
	this->name.append(fileName);

	// initially: no cached margins
	cacheLeftMargin = 0;
	cacheRightMargin = 0;
}

EmpiricalDistribution::EmpiricalDistribution(std::vector<double> inputData)
{
	data = inputData;
	std::sort(data.begin(), data.end());

	std::stringstream samples_s;
	samples_s << data.size();
	this->name = samples_s.str();
	this->name.append(" samples");

	// initially: no cached margins
	cacheLeftMargin = 0;
	cacheRightMargin = 0;
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

	unsigned int n = this->data.size();
	double h = (getRightMargin()- getLeftMargin()) / sqrt(n);

	h = (quantile(0.75)- quantile(0.25)) / pow(n, 0.3333);


	double sum = 0;
	unsigned int i;
	for (i = 0; i < n; i++)
		sum += (1 / sqrt(2 * PI)) * exp(-pow(x - data[i], 2) / (2 * pow(h, 2)));
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
	if (cacheLeftMargin)
		return * cacheLeftMargin;

	// discard the first 0.1%
	unsigned int i = 0;
	for (i = 0; i < data.size(); i++)
		if (cdf(data[i]) > 0.001)
		{
			cacheLeftMargin = new double;
			* cacheLeftMargin = data[i];
			return * cacheLeftMargin;
		}
	return data[0]; // data is sorted in ascending order
}

double EmpiricalDistribution::getRightMargin()
{
	if (cacheRightMargin)
		return * cacheRightMargin;

	// discard the last 0.1%
	unsigned int i = 0;
	for (i = data.size() - 1; i > 0; i--)
		if (cdf(data[i]) < 1 - 0.001)
		{
			cacheRightMargin = new double;
			* cacheRightMargin = data[i];
			return * cacheRightMargin;
		}
	return data[data.size() - 1]; // data is sorted in ascending order
}

double EmpiricalDistribution::nextSample()
{
	return quantile(this->generator.nextDouble());
}

} // namespace stochastic
