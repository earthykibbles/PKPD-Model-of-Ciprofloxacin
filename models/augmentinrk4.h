#include <iostream>
#include <vector>
#include <list>


class AugmentinRK4 {
public:
	float kb, ke, kt;

	float h;

	double k1b, k2b, k3b, k4b;
	double k1t, k2t, k3t, k4t;

	double xbn, xtn;

	double f1(double xb, double xt) {
		return -1 * (ke + kb) * xb + kt * xt;
	}

	double f2(double xb, double xt) {
		return (kb * xb) - (kt * xt);
	}


	std::vector<double> augmentinrk4(double xb0, double xt0) {
		k1b = f1(xb0 * h, xt0 * h);
		k1t = f2(xb0 * h, xt0 * h);

		k2b = f1((xb0 + 0.5 * k1b * h), (xt0 + (0.5 * k1t * h)));
		k2t = f2((xb0 + 0.5 * k1b * h), (xt0 + (0.5 * k1t * h)));

		k3b = f1((xb0 + 0.5 * k2b * h), (xt0 + (0.5 * k2t * h)));
		k3t = f2((xb0 + 0.5 * k2b * h), (xt0 + (0.5 * k2t * h)));

		k4b = f1((xb0 + (k3b * h)), (xt0 + (k3t * h)));
		k4t = f2((xb0 + (k3b * h)), (xt0 + (k3t * h)));

		xbn = xb0 + ((k1b + (2 * k2b) + (2 * k3b) + k4b) / 6);
		xtn = xt0 + ((k1t + (2 * k2t) + (2 * k3t) + k4t) / 6);

		return {xbn, xtn};
	}
};