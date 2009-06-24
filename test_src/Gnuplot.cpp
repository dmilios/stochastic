/*
 * Gnuplot.cpp
 *
 *  Created on: 17-Jun-2009
 *      Author: Dimitrios Milios
 */

#include "Gnuplot.h"

#include <cstdio>
#include <sstream>

using namespace std;

int Gnuplot::accuracy = 1000;

Gnuplot::Gnuplot()
{
	options = " with lines lw 1";
}

Gnuplot::~Gnuplot()
{
}

void Gnuplot::setAccuracy(int n)
{
	accuracy = n;
}

void Gnuplot::addRV(stochastic::RandomVariable rv)
{
	string curveName;
	stochastic::Distribution * rvDist = rv.getDistribution();
	string rvName = rvDist->getName();
	vector <double> vx, vy;

	rv.pdfOutline(accuracy, vx, vy);
	curveName = "PDF ";
	curveName.append(rvName.c_str());
	addCurve(curveName.c_str(), vx, vy);

	vx.clear();
	vy.clear();
	rv.cdfOutline(accuracy, vx, vy);
	curveName = "CDF ";
	curveName.append(rvName.c_str());
	addCurve(curveName.c_str(), vx, vy);

//	vx.clear();
//	vy.clear();
//	rv.quantileOutline(accuracy, vx, vy);
//	curveName = "InverseCDF ";
//	curveName.append(rvName.c_str());
//	addCurve(curveName.c_str(), vx, vy);
}

void Gnuplot::addCurve(string name, vector <double> vx, vector <double> vy)
{
	FILE * curve;
	stringstream counter;
	string tmpFile = "tmp";

	names.push_back(name);
	counter << names.size();
	tmpFile.append(counter.str());
	tmpFiles.push_back(tmpFile);

	curve = fopen(tmpFile.c_str(), "w");

	unsigned int i;
	for (i = 0; i < vx.size(); i++)
	{
		fprintf(curve, "%f\t%f\n", vx[i], vy[i]);
		fflush(curve);
	}
	fclose(curve);
}

void Gnuplot::plotCurves()
{
	FILE * gnuplot;
	unsigned int i;

	gnuplot = popen("gnuplot", "w");

	fprintf(gnuplot, "plot ");
	fflush(gnuplot);
	for (i = 0; i < names.size() - 1; i++)
	{
		fprintf(gnuplot, "'%s' title '%s' %s, ", tmpFiles[i].c_str(), names[i].c_str(), options.c_str());
		fflush(gnuplot);
	}
	fprintf(gnuplot, "'%s' title '%s' %s \n", tmpFiles[i].c_str(), names[i].c_str(), options.c_str());
	fflush(gnuplot);

	printf("Press enter to continue...");
	fflush(stdout);
	getchar();

	fputs("exit \n", gnuplot);
	pclose(gnuplot);
}
