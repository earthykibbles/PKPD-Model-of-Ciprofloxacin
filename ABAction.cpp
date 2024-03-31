#include <iostream>
#include <vector>
#include "models/augmentinrk4.h"
#include "models/bacteriaexp.h"
#include "gnuplot-iostream.h"

int main()
{
	Gnuplot gp("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"");

	BacteriaExp bact;
	bact.k = 0.025;
	int i;
	double initialPop = 1300;

	AugmentinRK4 au4;
	au4.h = 1;
	au4.kb = 0.5/60;
	au4.ke = 0.4/60;
	au4.kt = 0.3/60;


	double xb0 = 1000;
	double xt0 = 0;

	std::vector<double> xbv;
	std::vector<double> xtv;
	std::vector<double> popv;

	for (i = 0; i < 3000; i++) {

		double nextPop = bact.f1(initialPop);

		//std::cout << nextPop << "\n";
		
		std::vector<double> x = au4.augmentinrk4(xb0, xt0);

		xb0 = x[0];
		xt0 = x[1];

		xbv.push_back(xb0);
		xtv.push_back(xt0);

		//std::cout << xb0 <<"\t"<<xt0<<"\t" << "\n";

		if (nextPop < 0) {
			initialPop = 0;
		}
		else {
			initialPop = nextPop - ((xt0 * 20) / 100);
		}
		popv.push_back(initialPop);
	}

	gp << "set title 'Graph Showing Ciprofloxacin action on K.Pneumoniae'\n";
	gp << "plot '-' with lines title 'xbv',"
		<< "'-' with lines title 'xtv',"
	<< "'-' with lines title 'popv'\n";

	gp.send(xbv);
	gp.send(xtv);
	gp.send(popv);

	std::cin.get();
}

