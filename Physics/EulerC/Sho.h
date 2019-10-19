#pragma once
//Решение гармонического уравнения
class Sho
{
private:
	double pos;
	double vel;
	double accel;
	double w2;
	double t;
	double dt;
	double t_period;
	double ncalc;
public:
	Sho();
	void init();
	void calculate();
	void harmonic();
	void print();
};

