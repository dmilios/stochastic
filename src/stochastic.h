/*
 * stochastic.h
 *
 *  Created on: 05-Jun-2009
 *      Author: Dimitrios Milios
 *
 *  Includes all the definitions of "stochastic" library
 *  (only this one has to be included, so as to use the library)
 */

#ifndef STOCHASTIC_H_
#define STOCHASTIC_H_

#include "RandomVariable.h"
#include "distributions/Distribution.h"

#include "algorithms/MonteCarloAlgorithm.h"
#include "algorithms/ApproximationAlgorithm.h"
#include "algorithms/PiecewiseGaussian.h"
#include "algorithms/PiecewiseUniform.h"
#include "algorithms/ProbabilisticDiscretization.h"

#include "distributions/MixtureModel.h"
#include "distributions/Gaussian.h"
#include "distributions/Uniform.h"
#include "distributions/ChiSquare.h"
#include "distributions/Cauchy.h"
#include "distributions/Exponential.h"
#include "distributions/EmpiricalDistribution.h"
#include "distributions/DeltaDistribution.h"

#include "intermediateResults/MinOfDistributions.h"
#include "intermediateResults/MaxOfDistributions.h"
#include "intermediateResults/SumOfUniforms.h"
#include "intermediateResults/InverseRV_Distribution.h"

#include "algorithms/PG_EM.h"

#endif /* STOCHASTIC_H_ */
