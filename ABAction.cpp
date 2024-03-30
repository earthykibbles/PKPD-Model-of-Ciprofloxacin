#include <iostream>
#include <vector>
#include "models/augmentinrk4.h"
#include "models/bacteriaexp.h"
#include "gnuplot-iostream.h"

int main()
{
	Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

	BacteriaExp bact;
	bact.k = 0.3;
	int i;
	double initialPop = 1000;

	AugmentinRK4 au4;
	au4.h = 1;
	au4.kb = 0.5;
	au4.ke = 0.4;
	au4.kt = 0.3;


	double xb0 = 100;
	double xt0 = 0;

	std::vector<double> xbv;
	std::vector<double> xtv;

	for (i = 0; i < 100; i++) {
		double nextPop = bact.f1(initialPop);

		//std::cout << nextPop << "\n";
		
		std::vector<double> x = au4.augmentinrk4(xb0, xt0);

		xb0 = x[0];
		xt0 = x[1];

		xbv.push_back(xb0);
		xtv.push_back(xt0);

		//std::cout << xb0 <<"\t"<<xt0<<"\t" << "\n";

		initialPop = nextPop - ((xt0 * 20) / 100);
	}

	gp << "set title 'Graph of Two Random Lines'\n";
	gp << "plot '-' with lines title 'xbv',"
		<< "'-' with lines title 'xtv'\n";

	gp.send(xbv);
	gp.send(xtv);

	std::cin.get();
}

