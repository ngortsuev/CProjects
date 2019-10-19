#pragma once

#include <string>
#include "Vector.h"
#include "Matrix.h"
#include "SolverLibMacros.h"

#define DS_GAUSS 0
#define DS_LU 1

using namespace std;

//---------------------------------------Абстракный класс для решения СЛУ--------------------------------------
class DLLExport Solver
{
protected:
	Matrix A;
	Vector b;
public:
	Solver(void);
	Solver(Matrix &A, Vector &b);
	virtual ~Solver(void);

	virtual Matrix getMatrixA();
	virtual Vector getVectorB();

	virtual void setMatrixA(Matrix &m);
	virtual void setVectorB(Vector &v);
	
	virtual Vector solve() = 0;
};

//---------------------------------------Фабрика классов, реализующие прямые методы решения СЛУ----------------
class DLLExport SolverFactory
{
public:
	SolverFactory();
	virtual ~SolverFactory();

	Solver* CreateDirectSolver(int type);
};

//---------------------------------------Метод Гаусса-----------------------------------------------------------
class DLLExport GaussSolver : public Solver
{
protected:
	void   forwardTrace();
	Vector reverseTrace();
public:
	GaussSolver();
	virtual ~GaussSolver();

	virtual Vector solve();
};
