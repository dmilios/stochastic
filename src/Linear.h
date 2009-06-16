/*
 * Linear.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef LINEAR_H_
#define LINEAR_H_

#include "Distribution.h"
#include "ApproximationComponent.h"

namespace stochastic {

/**
 * @brief Linear Distribution of the form: 'y = slope * x + c'
 * 'alpha' and 'beta' define the interval
 * where the distribution is defined
 * */
class Linear : public stochastic::ApproximationComponent
{
private:
	double alpha;
	double beta;
	double slope;
	double c;

public:
	Linear(double, double, double);
	virtual ~Linear();

	// overload virtual methods of Distribution
	const char * getName();
	double pdf(double);
	double cdf(double);
	double nextSample();
	double getLeftMargin();
	double getRightMargin();

	// overload virtual methods of ApproximationComponent
	ApproximationComponent * add(ApproximationComponent *);
	ApproximationComponent * subtract(ApproximationComponent *);
	ApproximationComponent * multiply(ApproximationComponent *);
	ApproximationComponent * divide(ApproximationComponent *);
	ApproximationComponent * min(ApproximationComponent *);
	ApproximationComponent * max(ApproximationComponent *);
};

} // namespace stochastic

#endif /* LINEAR_H_ */
