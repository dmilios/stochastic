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

using namespace std;

class Gnuplot
{
private:
	vector <string> names;
	vector <string> tmpFiles;
	string options;

public:
	Gnuplot();
	virtual ~Gnuplot();

	void addCurve(string, vector <double>, vector <double>);
	void addCurve(string, vector <double>, vector <double>, string);
	void plotCurves();
};

#endif /* GNUPLOT_H_ */
