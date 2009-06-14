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

void pdf_test(std::vector <double> vx, std::vector <double> vy)
{
	FILE * pdf;
	pdf = fopen("pdf.dat", "w");

	unsigned int i;
	for (i = 0; i < vx.size(); i++)
	{
		fprintf(pdf, "%f\t%f\n", vx[i], vy[i]);
		fflush(pdf);
	}
	fclose(pdf);


	FILE * gnuplot;
	gnuplot = popen("gnuplot", "w");

	fprintf(gnuplot, "plot 'pdf.dat' with lines lw 1\n");
	fflush(gnuplot);

	printf("Press enter to continue...");
	fflush(stdout);
	getchar();

	fputs("exit \n", gnuplot);
	pclose(gnuplot);
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
	Gaussian g;
	Uniform u;
	Linear l(0, 1, 1);
	Exponential e;
	MixtureModel m;
	ApproximatedDistribution a;
	RandomVariable r1, r2(new Gaussian());

	int accuracy = 1000;
	std::vector <double> vx;
	std::vector <double> vy;
	r2.pdfOutline(accuracy, vx, vy);

	pdf_test(vx, vy);
	r2.produceFileOfSamples(10);

	return printArguments(argc, argv);
}
