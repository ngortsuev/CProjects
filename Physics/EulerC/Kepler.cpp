#include "Kepler.h"
#include <iostream>
#include <math.h>
using namespace std;

Kepler::Kepler() {
	init();
}

void Kepler::init() {
	n = 0;
	GM = 4.0 * 3.14 * 3.14;
	aspect_ratio = 1.5;
	radius = 0.1;
	t_period = 0.1;
	dt = 0.01;
	ncalc = t_period / dt;
	pos[0] = 1;
	pos[1] = 1;
	vel[0] = 1;
	
	r = 2 * pos[1];	
	
	x = aspect_ratio * r;

	impulse[0] = 0;
	impulse[1] = 0;
}

void Kepler::calculate() {
	for (double i = 0; i < ncalc; i++) {
		r = sqrt(pos[0] * pos[0] + pos[1] * pos[1]);

		for (int j = 0; j < 2; j++) {
			accel[j] = -GM * pos[j] / (r * r * r) ;
			vel[j] = vel[j] + accel[j] * dt;
			pos[j] = pos[j] + vel[j] * dt;
		}
	}
}

void Kepler::calculate_impulse() {
	for (double i = 0; i < ncalc; i++) {
		impulse[1] = 0;

		r = sqrt(pos[0] * pos[0] + pos[1] * pos[1]);
		magnitude = (GM / (r * r));
		magnitude = 10 * magnitude;
		impulse[1] = magnitude * dt;		//вертикальный импульс

		for (int j = 0; j < 2; j++) {
			//impulse[j] = magnitude * pos[j] / r;	//радиальный импульс

			/* тангенсальный импульс
			impulse[0] = -magnitude * pos[1] / 2;
			impulse[1] = magnitude * pos[2]/2
			*/
			accel[j] = -GM * pos[j] / (r * r * r) + impulse[j];
			vel[j] = vel[j] + accel[j] * dt;
			pos[j] = pos[j] + vel[j] * dt;
		}
	}
}

void Kepler::orbit() {
	calculate();
	print();
}

void Kepler::orbit_impulse() {

}

void Kepler::print() {	
	cout << pos[0] << " \t " << pos[1] << endl;
	cout << vel[0] << " \t " << vel[1] << endl;
	cout << accel[0] << " \t " << accel[1] << endl;
	
	cout << endl;
}

//---------------------------------------------------------------------------------------
Planet2::Planet2() {
	init();
}

void Planet2::init() {
	n = 0;
	GM = 4.0 * 3.14 * 3.14;
	aspect_ratio = 1.5;
	radius = 0.1;
	t_period = 0.1;
	dt = 0.001;
	ncalc = t_period / dt;
	
	// first planet
	pos[0][0] = 1;
	pos[0][1] = 0;
	vel[0][0] = 0;
	vel[0][1] = sqrt(GM / pos[0][0]);

	// second planet
	pos[1][0] = 2;
	pos[1][1] = 0;
	vel[1][0] = 0;
	vel[1][1] = sqrt(GM / pos[1][0]);

	r = 2 * pos[1][0];

	x = aspect_ratio * r;

	impulse[0] = 0;
	impulse[1] = 0;
}

void Planet2::calculate() {
	double dx, dy, dr;
	double a[2][2], r[2], r3;
	double dist2;

	for (double i = 0; i < ncalc; i++) {
		dx = pos[1][0] - pos[0][0];
		dy = pos[1][1] - pos[0][1];
		dr = sqrt(dx * dx + dy * dy);

		accel = GM / (dr * dr * dr);
		a[0][0] = -0.01 * accel * dx;
		a[0][1] = -0.01 * accel * dy;
		a[1][0] = -0.001 * a[0][0];
		a[1][1] = -0.001 * a[0][1];

		for (int iplanet = 0; iplanet < 2; iplanet++) {
			
			dist2 = pos[iplanet][0] * pos[iplanet][0];
			dist2 = dist2 + pos[iplanet][1] * pos[iplanet][1];

			r[iplanet] = sqrt(dist2);

			for (int j = 0; j < 2; j++) {

				r3 = r[iplanet] * r[iplanet] * r[iplanet];

				accel = -GM * pos[iplanet][j] / r3;
				accel = accel + a[iplanet][j];
				vel[iplanet][j] = vel[iplanet][j] + accel * dt;
				pos[iplanet][j] = pos[iplanet][j] + vel[iplanet][j] * dt;
			}
		}
	}
}

void Planet2::orbit() {
	calculate();
	print();
}

void Planet2::print() {
	cout << "pos1" << " \t " << "pos2" << " \t " << "vel1" << " \t " << "vel2"<<endl;
	for (int i = 0; i < 2; i++) {
		cout << "Planet " << i << ":" << endl;
		cout << pos[i][0] << " \t " << pos[i][1] << "\t" << vel[i][0] << " \t " << vel[i][1] << endl;		
	}
}