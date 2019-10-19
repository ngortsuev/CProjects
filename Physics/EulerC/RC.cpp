#include "RC.h"
#include <iostream>
using namespace std;

RC::RC() {
	init();
}

void RC::init() {
	v0 = 1;
	f = 5;
	w = 2 * 3.14 * f;
	R = 2;
	C = 5;
	dt = 0.1;
	tau = R * C;
	T = 1 / f;
	if (T > tau)
		tmax = 2 * T;
	else
		tmax = 2 * tau;
}

void RC::calculate() {
	V;
	Q = 0;
	t = 0;

	cout << "t" << "\t" << "I\t" << "Q\t" << endl;

	do {
		t = t + dt;
		
		I = (v0 * cos(w * t)) / R - Q / tau;

		Q = Q + I * dt;

		cout << t << "\t" << I << "\t" << Q << endl;

	} while (t <= tmax);
}

void RC::print() {
}