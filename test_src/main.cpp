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
	stochastic::Gaussian g;
	stochastic::Uniform u;
	stochastic::Exponential e;
	stochastic::MixtureModel m;
	stochastic::Linear l;
	stochastic::ApproximatedDistribution a;

	stochastic::RandomVariable r1(&g), r2(&u);
	r1 = r2 + r1;
	stochastic::min(r2, r2);

	//gnulot_test();

	return printArguments(argc, argv);
}
