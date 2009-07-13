/*
 * EmpiricalDistribution.h
 *
 *  Created on: 24-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef EMPIRICALDISTRIBUTION_H_
#define EMPIRICALDISTRIBUTION_H_

#include "Distribution.h"
#include <string>
#include <vector>
#include <fstream>

namespace stochastic {

class EmpiricalDistribution : public stochastic::Distribution
{
private:
	std::string name;
	std::vector<double> data;
	double maxProbability;  // helps to construct an envelope distribution

public:
	EmpiricalDistribution(const char *);
	EmpiricalDistribution(std::vector<double>);
	virtual ~EmpiricalDistribution();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* EMPIRICALDISTRIBUTION_H_ */
