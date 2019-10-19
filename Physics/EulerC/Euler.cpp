#include "Euler.h"
#include <iostream>
using namespace std;

Euler::Euler() {
	init();
}

void Euler::init() {
	x = 1;
	xmax = 2;
	y = 1;
	dx = 0.1;
	n = (xmax - x) / dx;
}

void Euler::calculate() {
	double slope;
	double change;
	for (int i = 0; i < n; i++) {
		slope = 2 * x;
		change = slope * dx;
		y = y + change;
		x = x + dx;
		cout << x << " " << y << endl;
	}
}

//---------------------------------------------------------------------------------------
EulerCool::EulerCool() {
	init();
}

void EulerCool::init() {
	t = 0;
	tmax = 2;
	temperature = 83;
	root_temp = 22;
	r = 0.1;
	dt = 0.1;	
	ncalc = tmax / dt;
}

void EulerCool::calculate() {	
	double change;
	for (double i = 0; i < ncalc; i++) {
		change = -r * (temperature - root_temp);
		temperature = temperature + change * dt;
		t = t + dt;
		print(t, temperature);
	}
}

void EulerCool::print(double t, double temperature) {
	cout << t << " " << temperature << endl;
}

//---------------------------------------------------------------------------------------
EulerFall::EulerFall(double height, double dt) {
	this->height = height;
	this->dt = dt;
	init();
}

void EulerFall::init() {
	t = 0;
	y = 0;
	v = 0;
	g = 9.8;
	t_period = 0.1;
	ncalc = t_period / dt;
}

void EulerFall::calculate() {
	double accel;
	for (double i = 0; i < ncalc; i++) {
		y = y + v * dt;
		accel = g;
		v = v + accel * dt;
	}
	t = t + dt * ncalc;
}

void EulerFall::fall() {
	cout << "t\t " << "y\t " << "V\t " << "g\t " << "height\t " << endl;
	do {
		calculate();
		print();
	} while (y < height);
}

void EulerFall::print() {
	cout<< t << "\t " 
		<< y << "\t " 
		<< v << "\t " 
		<< g << "\t "
		<< height
		<< endl;
}

//---------------------------------------------------------------------------------------
EulerThrow::EulerThrow() {
	init();
}

void EulerThrow::init() {
	t = 0;
	dt = 0.1;
	height = 10;
	length = 10;
	x = 0;
	y = 0;
	v = 15;
	vx = 15;
	vy = 15;
	ax = 0;
	ay = 0;
	g = 9.8;
	A = 0.1;
	t_period = 0.1;
	ncalc = t_period / dt;
}

void EulerThrow::calculate() {
	double v2;
	for (double i = 0; i < ncalc; i++) {
		v2 = vx * vx + vy * vy;
		
		v = sqrt(v2);

		ax = -A * v * vx;
		ay = -g - A * v * vy;

		vx = vx + ax * dt;
		vy = vy + ay * dt;

		x = x + vx * dt;
		y = y + vy * dt;

	}
	t = t + dt * ncalc;
}

void EulerThrow::throwObject() {
	cout << "t\t " << "x\t " << "\t y\t " << endl;
	
	do {
		calculate();
		print();
	} while (y > 0);
}

void EulerThrow::print() {
	cout << t << " \t "
		 << x << " \t "
		 << y << " \t "		 
		 << endl;
}