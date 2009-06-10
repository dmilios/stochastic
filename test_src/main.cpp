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

#include "../src/ApproximationComponent.h"

void gnulot_test()
{
	FILE *gnuplot;
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
	Linear l;
	Exponential e;
	MixtureModel m;
	ApproximatedDistribution a;
	RandomVariable r1, r2;

	std::vector <double> ss = u.sample(10000);
	unsigned int i;
	for (i = 0; i < ss.size(); i++)
		std::cout << ss[i] << '\n';

	//gnulot_test();

	return printArguments(argc, argv);
}
