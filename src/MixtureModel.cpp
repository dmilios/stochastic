/*
 * MixtureModel.cpp
 *
 *  Created on: 08-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "MixtureModel.h"

namespace stochastic {

MixtureModel::MixtureModel()
{
}

MixtureModel::~MixtureModel()
{
}

const char * MixtureModel::getName()
{
	return "mm";
}

double MixtureModel::pdf(double x)
{
	return 0;
}

double MixtureModel::getLeftMargin()
{
	return 0;
}

double MixtureModel::getRightMargin()
{
	return 0;
}

double MixtureModel::nextSample()
{
	return 0;
}

} // namespace stochastic
