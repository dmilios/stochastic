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
	string * outputFile;
	string * texFile;

	vector <string> names;
	vector <string> tmpFiles;
	vector <CurveTypes> types;
	vector <string> options;

public:
	Gnuplot();
	virtual ~Gnuplot();

	static void setAccuracy(int);

	void addRV(stochastic::RandomVariable);
	void addCurve(CurveTypes, string, vector <double>, vector <double>);
	void plotBuffered(CurveTypes);
	void clearBuffer();
	void setOutputFile(const char *);
	void setTexFile(const char *);
};

#endif /* GNUPLOT_H_ */
