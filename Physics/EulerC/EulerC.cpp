#include <iostream>
#include "Euler.h"
#include "Kepler.h"
#include "Sho.h"
#include "RC.h"
#include "Beeman.h"
using namespace std;

void EulerForMotionObject() {
	cout << "Euler's algroritm:\n";
	Euler *euler = new Euler();
	euler->calculate();    

	// охлаждение кофе
	cout << "Euler's algroritm for cool coffee:\n";
	EulerCool* cool = new EulerCool();
	cool->calculate();
	cout << "End\n";

	// падение объекта
	cout << "Euler's algoritm for fall object:\n";
	EulerFall *eulerFall = new EulerFall(10, 0.1);	
	eulerFall->fall();
	cout << "End\n";

	// бросание объекта
	cout << "Euler's algoritm for throw object:\n";
	EulerThrow* eulerThrow = new EulerThrow();
	eulerThrow->throwObject();
	cout << "End\n";

	delete euler;
	delete cool;
	delete eulerFall;
	delete eulerThrow;
}

void CalculateForKeplerLaw() {
	cout << "Kepler's algoritm:\n";
	Kepler* kepler = new Kepler();
	kepler->orbit();
	cout << "End\n";

	cout << "Kepler's algoritm with impulse:\n";
	Kepler* kepler2 = new Kepler();
	kepler2->orbit_impulse();
	cout << "End\n";

	cout << "Two planets:\n";
	Planet2* planet2 = new Planet2();
	planet2->orbit();
	cout << "End\n";

	delete kepler;
	delete kepler2;
	delete planet2;
}

void CalculateHarmonicLaw() {
	Sho* sho = new Sho();
	
	sho->harmonic();

	delete sho;
}

void CalculateRC() {
	RC* rc = new RC();

	rc->calculate();

	delete rc;
}

void CalculateBeeman() {
	Beeman* beeman = new Beeman();

	beeman->calculate();
}

int main()
{
	//EulerForMotionObject();

	//CalculateForKeplerLaw();

	//CalculateHarmonicLaw();

	//CalculateRC();

	CalculateBeeman();
}