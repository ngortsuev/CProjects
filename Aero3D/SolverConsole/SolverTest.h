#pragma once

#include <string>
#include <fstream>
#include "Solver.h"

using namespace std;

class SolverTest
{
public:
	SolverTest(void);
	~SolverTest(void);
	int getRowCount(int index, int filecount);

	int setMatrixATest(bool print);
	int setVectorBTest(bool print);
	int solveTest1(bool print);
	int solveTest2(bool print);
	int solveTest3(bool print);
	int solveTest4(bool print);
	int solveTest5(bool print);
	int solveTest6(bool print);
	int solveTest7(bool print);
};
