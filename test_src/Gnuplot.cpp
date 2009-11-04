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

string Gnuplot::defaultOptions = " with lines";

Gnuplot::Gnuplot()
{
	outputFile = 0;
	texFile = 0;
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
	curveName = " ";
	curveName.append(rvName.c_str());
	addCurve(PDF, curveName.c_str(), vx, vy);

	vx.clear();
	vy.clear();
	rv.cdfOutline(accuracy, vx, vy);
	curveName = " ";
	curveName.append(rvName.c_str());
	addCurve(CDF, curveName.c_str(), vx, vy);

	vx.clear();
	vy.clear();
	rv.quantileOutline(accuracy, vx, vy);
	curveName = " ";
	curveName.append(rvName.c_str());
	addCurve(INVERSE_CDF, curveName.c_str(), vx, vy);
}

void Gnuplot::addCurve(CurveTypes type, string name, vector <double> vx, vector <double> vy)
{
	addCurve(type, name, vx, vy, defaultOptions);
}

void Gnuplot::addCurve(CurveTypes type, string name,
		vector<double> vx, vector<double> vy, string current_options)
{
	stringstream data;

	types.push_back(type);
	names.push_back(name);
	options.push_back(current_options);

	unsigned int i;
	for (i = 0; i < vx.size(); i++)
		data << vx[i] << '\t' << vy[i] << endl;
	curve_data.push_back(data.str());
}

void Gnuplot::addtoPreamble(string statement)
{
	preamble.push_back(statement);
}

void Gnuplot::plotBuffered(CurveTypes type)
{
	FILE * gnuplot;
	unsigned int i;
	int first_entered_flag = 0;
	//int entered_counter = 0;

	gnuplot = popen("gnuplot", "w");

	if (texFile)
		fprintf(gnuplot, "set terminal latex\nset output \"%s.tex\"\n",
			texFile->c_str());

	for (i = 0; i < preamble.size(); i++)
		fprintf(gnuplot, "%s\n", preamble[i].c_str());

	fprintf(gnuplot, "plot ");
	for (i = 0; i < names.size(); i++)
	{
		if (type == types[i])
		{
			if (first_entered_flag)
				fprintf(gnuplot, ", ");
			else
				first_entered_flag = 1;
			fprintf(gnuplot, "'-' title '%s' %s", names[i].c_str(),
				options[i].c_str());

			//entered_counter++;
			//entered_counter = entered_counter % options.size();
		}
	}
	fprintf(gnuplot, "\n");
	for(i = 0; i < curve_data.size(); i++)
		if (type == types[i])
			fprintf(gnuplot, "%se\n", curve_data[i].c_str());

	if(outputFile)
	{
		fprintf(gnuplot, "shell\n");
		fprintf(gnuplot, "xwd -out %s.png\n", outputFile->c_str());
		fprintf(gnuplot, "xwdtopnm %s.png | pnmtopng > foo.png\n",
				outputFile->c_str());
		printf("Click the output window to continue...\n");
	}

	if (!texFile)
	{
		fflush(gnuplot);
		printf("Press enter to continue...");
		fflush(stdout);
		getchar();
	}

	fprintf(gnuplot, "exit\n");
	pclose(gnuplot);
	outputFile = 0;
}

void Gnuplot::clearBuffer()
{
	names.clear();
	curve_data.clear();
	types.clear();
	options.clear();
	preamble.clear();
}

// should be called before plotBuffered()
void Gnuplot::setOutputFile(const char * filename)
{
	outputFile = new string(filename);
}

void Gnuplot::setTexFile(const char * filename)
{
	texFile = new string(filename);
}
