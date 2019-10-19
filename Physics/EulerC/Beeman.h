#pragma once
class Beeman
{
private:
	double x, v, a;
	double anew, aold;
	double dt,dt2;
	double tmax, nmax;
	double KE, Q, PE, etot, ecum, e2cum;
	double n, ebar, sigma2;

public:	
	void init();
	void energy();
	void alg_verlet();
	void alg_beeman();
	double f_x();
	void calculate();
	void print();	
};

