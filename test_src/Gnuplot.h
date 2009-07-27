/*
 * Gnuplot.h
 *
 *  Created on: 17-Jun-2009
 *      Author: Dimitrios Milios
 */

#ifndef GNUPLOT_H_
#define GNUPLOT_H_

#include <vector>
#include <string>
#include "../src/stochastic.h"

using namespace std;

enum CurveTypes
{
	PDF,
	CDF,
	INVERSE_CDF,
	OTHER
};

class Gnuplot
{
private:
	static int accuracy;
	vector <string> names;
	vector <string> tmpFiles;
	vector <CurveTypes> types;
	string options;

public:
	Gnuplot();
	virtual ~Gnuplot();

	static void setAccuracy(int);

	void addRV(stochastic::RandomVariable);
	void addCurve(CurveTypes, string, vector <double>, vector <double>);
	void plotBuffered(CurveTypes);
	void clearBuffer();
};

#endif /* GNUPLOT_H_ */
