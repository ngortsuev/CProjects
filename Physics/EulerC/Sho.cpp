#include "Sho.h"
#include <iostream>
using namespace std;
Sho::Sho() {
	init();
}

void Sho::init() {
	t = 0;
	pos = 10;
	vel = 0;
	accel = 0;
	w2 = 9;
	t_period = 0.05;
	dt = 0.1;
	ncalc = t_period / dt;
}

void Sho::calculate() {
	for (double i = 0; i < ncalc; i++) {
		accel = -w2 * pos;
		vel = vel + accel * dt;
		pos = pos + vel * dt;
	}
}

void Sho::harmonic() {
	cout << "Harmonics Oscillations. Sho:" << endl;
	
	cout << "pos\t " << "vel\t " << "accel\t " << endl;

	for (int i = 0; i < 5; i++)
	{
		calculate();
		print();

		t = t + ncalc * dt;
	}
	cout << "t: " << t << endl;
}

void Sho::print() {
	cout << pos << "\t" << vel << "\t" << accel << endl;
}