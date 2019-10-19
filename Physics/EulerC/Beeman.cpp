#include "Beeman.h"
#include <iostream>
#include <math.h>
using namespace std;

void Beeman::init() {
	x = 2;
	v = 0;
	aold = f_x();
	dt = 0.1;
	dt2 = dt * dt;
	tmax = 10;
	nmax = tmax / dt2;
}

void Beeman::energy() {
	KE = 0.5 * v * v;
	Q = exp(-x);
	PE = Q * (Q - 2);
	etot = KE + PE;
	ecum = ecum + etot;
	e2cum = e2cum + etot * etot;
}

void Beeman::alg_verlet() {
	x = x + v * dt + 0.5 * aold * dt2;
	a = f_x();
	v = v + 0.5 * (a + aold) * dt;
}

void Beeman::alg_beeman() {
	x = x + v * dt + (4 * a - aold) * dt2 / 6;
	anew = f_x();
	v = v + (2 * anew + 5 * a - aold) * dt / 6;
	aold = a;
	a = anew;
}

double Beeman::f_x() {
	double e = exp(-x);
	return 2 * e * (e - 1);
}

void Beeman::calculate() {
	init();
	energy();
	alg_verlet();
	energy();
	
	n = 1;

	do {
		n++;
		alg_beeman();
		energy();
	} 
	while (n < nmax);

	print();
}

void Beeman::print() {
	n++;
	ebar = ecum / n;
	
	cout << "Middle energy: " << ebar << endl;
	
	sigma2 = e2cum / n - ebar * ebar;

	cout << "Sigma: " << sqrt(sigma2) << endl;
}