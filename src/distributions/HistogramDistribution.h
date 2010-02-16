/*
 * HistogramDistribution.h
 *
 *  Created on: 15 Feb 2010
 *      Author: s0897368
 */

#ifndef HISTOGRAMDISTRIBUTION_H_
#define HISTOGRAMDISTRIBUTION_H_

#include "MixtureModel.h"
#include <vector>
#include <string>

namespace stochastic
{

class HistogramDistribution : public Distribution
{
private:
	std::string name;
	MixtureModel * mixtureOfUniforms;
	void createHistogram(std::vector<double>);

public:
	HistogramDistribution(const char *);
	HistogramDistribution(std::vector<double>);
	virtual ~HistogramDistribution();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* HISTOGRAMDISTRIBUTION_H_ */
