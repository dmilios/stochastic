/*
 * functions.h
 *
 *  Created on: 23-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef MATHFUNCTIONS_H_
#define MATHFUNCTIONS_H_

#include <cmath>

namespace stochastic
{

const double PI = 3.14159265;

//NOTE: Abromowitz and Stegun approximation for Error Function
inline double erf2(double x)
{
	static const double a1 =  0.254829592;
	static const double a2 = -0.284496736;
	static const double a3 =  1.421413741;
	static const double a4 = -1.453152027;
	static const double a5 =  1.061405429;
	static const double p  =  0.3275911;

	// Save the sign of x
	int sign = 1;
	if (x < 0)
		sign = -1;
	x = std::abs(x);

	// A&S formula 7.1.26
	double t = 1.0/(1.0 + p*x);
	double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

	return sign * y;
}

// Manhattan distance
inline double distancePDF(Distribution * arg1, Distribution * arg2)
{
	double result = 0;
	int accuracy = 1000;
	double start = arg1->getLeftMargin();
	double end = arg1->getRightMargin();
	if (arg2->getLeftMargin() < start)
		start = arg2->getLeftMargin();
	if (arg2->getRightMargin() > end)
		end = arg2->getRightMargin();

	double x = start;
	double step = (end - start) / accuracy;
	double fx_a, fx_b;
	int i;

	fx_a = std::abs(arg1->pdf(x) - arg2->pdf(x));
	for (i = 0; i < accuracy; i++)
	{
		fx_b = std::abs(arg1->pdf(x + step) - arg2->pdf(x + step));
		result += step * (fx_a + fx_b) / 2;
		fx_a = fx_b;
		x = x + step;
	}
	return result;
}

} // end stochastic

#endif /*MATHFUNCTIONS_H_ */
