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
	FILE * curve;
	stringstream counter;
	string tmpFile = "tmp";

	types.push_back(type);
	names.push_back(name);
	counter << names.size();
	tmpFile.append(counter.str());
	tmpFiles.push_back(tmpFile);
	options.push_back(defaultOptions);

	curve = fopen(tmpFile.c_str(), "w");

	unsigned int i;
	for (i = 0; i < vx.size(); i++)
	{
		fprintf(curve, "%f\t%f\n", vx[i], vy[i]);
		fflush(curve);
	}
	fclose(curve);
}

void Gnuplot::addCurve(CurveTypes type, string name,
		vector<double> vx, vector<double> vy, string current_options)
{
	FILE * curve;
	stringstream counter;
	string tmpFile = "tmp";

	types.push_back(type);
	names.push_back(name);
	counter << names.size();
	tmpFile.append(counter.str());
	tmpFiles.push_back(tmpFile);
	options.push_back(current_options);

	curve = fopen(tmpFile.c_str(), "w");

	unsigned int i;
	for (i = 0; i < vx.size(); i++)
	{
		fprintf(curve, "%f\t%f\n", vx[i], vy[i]);
		fflush(curve);
	}
	fclose(curve);
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
	{
		fprintf(gnuplot, "set terminal latex\n");
		fflush(gnuplot);

		fprintf(gnuplot, "set output \"%s.tex\"\n", texFile->c_str());
		fflush(gnuplot);
	}

	for (i = 0; i < preamble.size(); i++)
	{
		fprintf(gnuplot, "%s\n", preamble[i].c_str());
		fflush(gnuplot);
	}

	fprintf(gnuplot, "plot ");
	fflush(gnuplot);
	for (i = 0; i < names.size(); i++)
	{
		if (type == types[i])
		{
			if (first_entered_flag)
			{
				fprintf(gnuplot, ", ");
				fflush(gnuplot);
			}
			else
				first_entered_flag = 1;
			fprintf(gnuplot, "'%s' title '%s' %s", tmpFiles[i].c_str(),
					names[i].c_str(), options[i].c_str());
			fflush(gnuplot);

			//entered_counter++;
			//entered_counter = entered_counter % options.size();
		}
	}
	fprintf(gnuplot, "\n");
	fflush(gnuplot);

	if(outputFile)
	{
		fprintf(gnuplot, "shell\n");
		fflush(gnuplot);
		fprintf(gnuplot, "xwd -out %s.png\n", outputFile->c_str());
		fflush(gnuplot);

		fprintf(gnuplot, "xwdtopnm %s.png | pnmtopng > foo.png\n",
				outputFile->c_str());
		fflush(gnuplot);
		printf("Click the output window to continue...\n");
		fflush(stdout);

		fprintf(gnuplot, "exit\n");
		fflush(gnuplot);
	}

	if (!texFile)
	{
		printf("Press enter to continue...");
		fflush(stdout);
		getchar();
	}

	fprintf(gnuplot, "exit\n");
	fflush(stdout);
	pclose(gnuplot);
	outputFile = 0;
}

void Gnuplot::clearBuffer()
{
	names.clear();
	tmpFiles.clear();
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
