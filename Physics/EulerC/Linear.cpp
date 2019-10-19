#include "Linear.h"
#include <iostream>
using namespace std;

Linear::Linear() {

}

Linear::~Linear() {

}

void Linear::init() {
	ndim = 10;
	n = 3;
	a[0][0] = 10;
	a[1][0] = -3;
	a[2][0] = 5;
	a[0][1] = -7;
	a[1][1] = 2;
	a[2][1] = -1;
	a[0][2] = 0;
	a[1][2] = 6;
	a[2][2] = 5;
}

void Linear::decomp() {

}

void Linear::solve() {

}

void Linear::calc_example() {

}

void Linear::print() {

}
