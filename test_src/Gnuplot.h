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

class Gnuplot
{
private:
	static int accuracy;
	vector <string> names;
	vector <string> tmpFiles;
	string options;

public:
	Gnuplot();
	virtual ~Gnuplot();

	static void setAccuracy(int);

	void addRV(stochastic::RandomVariable);
	void addCurve(string, vector <double>, vector <double>);
	void plotCurves();
};

#endif /* GNUPLOT_H_ */
