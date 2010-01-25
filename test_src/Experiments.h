/*
 * Experiments.h
 *
 *  Created on: 20-Jul-2009
 *      Author: Dimitrios Milios
 */

#ifndef EXPERIMENTS_H_
#define EXPERIMENTS_H_

#include "DistanceMetrics.h"
#include "../src/stochastic.h"

using namespace stochastic;

void current();

void comparePUwithMC();
void comparePGwithMC();
void compareApproximations();

void dependencyMC();
void testApproximation(RandomVariable, ApproximationAlgorithm&);

void sumOfUniforms();
void minmaxTests();
void testKernel();

#endif /* EXPERIMENTS_H_ */
