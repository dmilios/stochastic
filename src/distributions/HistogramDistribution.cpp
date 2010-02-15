/*
 * HistogramDistribution.cpp
 *
 *  Created on: 15 Feb 2010
 *      Author: s0897368
 */

#include "HistogramDistribution.h"

#include "../utilities/FileParser.h"
#include "EmpiricalDistribution.h"
#include "Uniform.h"
#include <sstream>
#include <cmath>

namespace stochastic
{

HistogramDistribution::HistogramDistribution(const char * fileName)
{
	FileParser parser;
	std::vector<double> data = parser.parseDataFile(fileName);
	createHistogram(data);
}

HistogramDistribution::HistogramDistribution(std::vector<double> inputData)
{
	createHistogram(inputData);
}

HistogramDistribution::~HistogramDistribution()
{
}

// Convenience method for generating the mixture of uniforms
// that is going to be the histogram
void HistogramDistribution::createHistogram(std::vector<double> data)
{
	std::sort(data.begin(), data.end());
	EmpiricalDistribution helperDist(data);
	double q75 = helperDist.quantile(0.75);
	double q25 = helperDist.quantile(0.25);

	// Freedman–Diaconis' choice
	double binWidth = (q75 - q25) / pow(data.size(), 0.3333);

	// k = (max - min) / h, 	data is sorted in ascending order
	double maxx = data[data.size() - 1];
	double minx = data[0];
	int numberOfBins = (int) ceil((maxx - minx) / binWidth);

	std::vector<double> weights;
	std::vector<MixtureComponent *> components;
	long int i;
	for (i = 0; i < data.size(); i++)
	{
		// TODO: finish this...
	}

	mixtureOfUniforms = new MixtureModel(components, weights);

	this->name = "Hist: ";
	std::stringstream samples_s;
	samples_s << data.size();
	this->name.append(samples_s.str());
	this->name.append(" samples, ");
	std::stringstream bins_s;
	bins_s << numberOfBins;
	this->name.append(bins_s.str());
	this->name.append(" bins");
}

/*
 *
 * Distribution methods
 * */

const char * HistogramDistribution::getName()
{
	return this->name.c_str();
}

double HistogramDistribution::pdf(double x)
{
	return mixtureOfUniforms->pdf(x);
}

double HistogramDistribution::cdf(double x)
{
	return mixtureOfUniforms->cdf(x);
}

double HistogramDistribution::getLeftMargin()
{
	return mixtureOfUniforms->getLeftMargin();
}

double HistogramDistribution::getRightMargin()
{
	return mixtureOfUniforms->getRightMargin();
}

double HistogramDistribution::nextSample()
{
	return mixtureOfUniforms->nextSample();
}

} // namespace stochastic
