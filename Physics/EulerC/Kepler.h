#pragma once
class Kepler
{
private:
	double n;
	double x;
	double y;
	double r;
	double aspect_ratio;
	double GM;
	double t_period;
	double dt;
	double ncalc;
	double pos[2] = { 0, 0 };
	double vel[2] = { 0, 0 };
	double accel[2] = { 0, 0 };
	double radius;
	double impulse[2] = { 0,0 };
	double magnitude;
public:
	Kepler();	
	void init();
	void calculate();
	void calculate_impulse();
	void orbit();
	void orbit_impulse();
	void print();
};

class Planet2 {
private:
	double n;
	double x;
	double y;
	double r;
	double aspect_ratio;
	double GM;
	double t_period;
	double dt;
	double ncalc;
	double pos[2][2];
	double vel[2][2];
	double accel;
	double radius;
	double impulse[2];
	double magnitude;
public:
	Planet2();
	void init();
	void calculate();	
	void orbit();	
	void print();
};

