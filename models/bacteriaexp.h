
// Simple bacteria dynamics without carrying capacity limitations

class BacteriaExp {
public:
	double k;
	
	double f1(double p) {
		return p + (k * p);
	}
};