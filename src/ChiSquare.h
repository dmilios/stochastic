/*
 * ChiSquare.h
 *
 *  Created on: 13-Aug-2009
 *      Author: Dimitrios Milios
 */

#ifndef CHI_SQUARE_H_
#define CHI_SQUARE_H_

#include "MixtureComponent.h"

namespace stochastic {

class ChiSquare : public stochastic::MixtureComponent
{
private:
	// Beware: the parameter of chi_square is integer, not double
	int k;

public:
	ChiSquare();
	ChiSquare(int);
	virtual ~ChiSquare();

	const char * getName();
	double pdf(double);
	double cdf(double);
	double getLeftMargin();
	double getRightMargin();
	double nextSample();
};

} // namespace stochastic

#endif /* CHI_SQUARE_H_ */
