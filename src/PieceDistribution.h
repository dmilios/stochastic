/*
 * PieceDistribution.h
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 *
 *  This class serves as an "interface", so as to
 *  group the distributions that can be parts of mixture models.
 *
 *  The derived classes inherit the "weight"
 *  and they are forced to implement the pure virtual methods
 */

#ifndef PIECEDISTRIBUTION_H_
#define PIECEDISTRIBUTION_H_

namespace stochastic {

class PieceDistribution {
protected:
	double weight;

public:
	virtual double getWeight() = 0;
	virtual void setWeight(double) = 0;
};

} // namespace stochastic

#endif /* PIECEDISTRIBUTION_H_ */
