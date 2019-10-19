#pragma once
class Linear
{
private:
	double a[10][10], b[10], work[10];
	double cond, condp1;
	int ipvt[10];
	int i, j, n, ndim;
public:
	Linear();
	~Linear();
	void init();
	void decomp();
	void solve();
	void print();
	void calc_example();
};

