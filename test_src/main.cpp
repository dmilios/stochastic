// =============================================================

/* 'stochastic' is a library
 * for performing operations between random variables
 *
 * main() is used for test purposes
 *
 *
 *      Author: Dimitrios Milios
 */

// =============================================================


// load "stochastic" library
#include "../src/stochastic.h"

#include <cstdio>
#include <iostream>

void gnulot_test()
{
	FILE * gnuplot;
	gnuplot = popen("gnuplot", "w");

	int x = 1;
	fprintf(gnuplot, "plot %d\n", x);
	fflush(gnuplot);

	printf("Press enter to continue...");
	fflush(stdout);
	getchar();

	fputs("exit \n", gnuplot);
	pclose(gnuplot);
}

void octave_test(std::vector <double> v)
{
	FILE * octave;
	octave = fopen("samples.txt", "w");

	fprintf(octave, "# name: x \n");
	fflush(octave);
	fprintf(octave, "# type: matrix \n");
	fflush(octave);
	fprintf(octave, "# rows: %d \n", (int)v.size());
	fflush(octave);
	fprintf(octave, "# columns: 1 \n");
	fflush(octave);

	unsigned int i;
	for (i = 0; i < v.size(); i++)
	{
		fprintf(octave, "%f \n", v[i]);
		fflush(octave);
	}

	fclose(octave);
}

int printArguments(int argc, char *argv[])
{
	int i;
	std::cout << "\nThe arguments were:\n";
	for (i = 0; i < argc; i++)
		std::cout << argv[i]<< "\n" ;
	return 0;
}

int main(int argc, char *argv[])
{
	using namespace stochastic;
	Gaussian g(0, 1);
	Uniform u;
	Linear l;
	Exponential e;
	MixtureModel m;
	ApproximatedDistribution a;
	RandomVariable r1, r2;

	std::vector <double> ss = g.sample(10000);
	octave_test(ss);
	//gnulot_test();

	return printArguments(argc, argv);
}
