/*
 * SumOfUniforms.h
 *
 *  Created on: 26-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef SUMOFUNIFORMS_H_
#define SUMOFUNIFORMS_H_

#include "../distributions/MixtureComponent.h"

namespace stochastic {

class SumOfUniforms : public stochastic::MixtureComponent
{
private:
	double a1, b1;
	double a2, b2;

	// cache results for efficiency
	double range1, range2;
	double a12, b12;
	// the constants needed for the integrals
	double c1;
	double c2;
	double c3;

	int case_flag; // possible values 0, 1, 2

public:
	SumOfUniforms(double, double, double, double);
	virtual ~SumOfUniforms();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // end stochastic

#endif /* SUMOFUNIFORMS_H_ */
