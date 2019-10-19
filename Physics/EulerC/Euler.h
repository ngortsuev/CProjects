#pragma once
class Euler
{
private:
	double x;
	double xmax;
	double y;
	double dx;
	double n;
	
public:
	Euler();
	void init();
	void calculate();
};

class EulerCool 
{
private:
	double t;
	double temperature;
	double root_temp;
	double r;
	double dt;
	double tmax;
	double ncalc;

public:
	EulerCool();
	void init();
	void calculate();
	void print(double t, double temperature);
};

class EulerFall {
private:
	double t;			// начальный момент времени
	double dt;			// прирощение по времени
	double y;			// начальное значение координат
	double height;		// начальная высота тела над Землей
	double v;			// начальная скорость
	double g;			// ускорение свободного падения
	double t_period;	// секунды
	double ncalc;		// вычисляемый период расчетов
public:
	EulerFall(double height, double dt);
	void init();
	void calculate();
	void fall();
	void print();
};

class EulerThrow {
private:
	double t;			// начальный момент времени
	double dt;			// прирощение по времени
	double x;
	double y;			// начальное значение координат
	double height;		// начальная высота тела над Землей
	double length;
	double v;			// начальная скорость
	double vx;
	double vy;
	double ax;
	double ay;
	double g;			// ускорение свободного падения
	double A;
	double t_period;	// секунды
	double ncalc;		// вычисляемый период расчетов
public:
	EulerThrow();
	void init();
	void calculate();
	void throwObject();
	void print();
};

