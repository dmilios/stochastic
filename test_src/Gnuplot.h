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
#include "../src/algorithms/RandomVariableAlgorithm.h"

using namespace std;
using namespace stochastic;

enum CurveTypes
{
	PDF, CDF, INVERSE_CDF, EVOLUTION, OTHER
};

class Gnuplot
{
private:
	static int accuracy;
	static string defaultOptions;
	string * outputFile;
	string * texFile;
	vector<string> preamble; // a series of statements in the beginning of a plot

	vector<string> names;
	vector<string> curve_data;
	vector<CurveTypes> types;
	vector<string> options;

	void addCurve(CurveTypes, string, vector<double> , vector<double> );
	void addCurve(CurveTypes, string, vector<double> , vector<double> , string);
	void buildErrorCurves(int n, std::vector<double> &, std::vector<double> &);

public:
	Gnuplot();
	virtual ~Gnuplot();

	static void setAccuracy(int);

	void addRV(RandomVariable);
	void addErrorEvolution(int, RandomVariableAlgorithm *);

	void addtoPreamble(string);
	void plotBuffered(CurveTypes);
	void clearBuffer();
	void setOutputFile(const char *);
	void setTexFile(const char *);
};

#endif /* GNUPLOT_H_ */
