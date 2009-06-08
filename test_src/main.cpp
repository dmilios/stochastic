// =============================================================

/* 'stochastic' is a library
 * for performing operations between random variables
 *
 * main() is used for test purposes
 *
 */

// =============================================================


// load "stochastic" library
#include "../src/stochastic.h"

#include <stdio.h>


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
	printf("\nThe arguments were:\n");
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
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
	//gnulot_test();
	return printArguments(argc, argv);
}
