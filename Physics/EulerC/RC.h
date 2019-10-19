#pragma once
// Вычисление падения напряжения
class RC
{
private:
	double v0;	// амплитуда внешнего напряжения
	double f;   // частота внешнего напряжения
	double w;	// угловая частота
	double t;
	double tau;
	double tmax;
	double T;
	double R, C, V, Q, I;
	double dt;
public:
	RC();
	void init();
	void calculate();
	void print();
};

