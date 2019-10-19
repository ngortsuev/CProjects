#include "StdAfx.h"
#include "Solver.h"

//-------------------------------------------------------------------------------------------------------------
Solver::Solver(void)
{
}

Solver::Solver(Matrix &A, Vector &b)
{
	this->A = A;
	this->b = b;
}

//-------------------------------------------------------------------------------------------------------------
Solver::~Solver(void)
{
}

Matrix Solver::getMatrixA()
{
	return A;
}

Vector Solver::getVectorB()
{
	return b;
}

//-------------------------------------------------------------------------------------------------------------
void Solver::setMatrixA(Matrix &m)
{
	this->A = m;
}

//-------------------------------------------------------------------------------------------------------------
void Solver::setVectorB(Vector &v)
{
	this->b = v;
}

//-------------------------------------------------------------------------------------------------------------
SolverFactory::SolverFactory()
{
}

//-------------------------------------------------------------------------------------------------------------
SolverFactory::~SolverFactory()
{
}

//-------------------------------------------------------------------------------------------------------------
Solver* SolverFactory::CreateDirectSolver(int type)
{
	switch(type)
	{
		case DS_GAUSS: return new GaussSolver();
		
		default: return new GaussSolver();
	}
}

//-------------------------------------------------------------------------------------------------------------
GaussSolver::GaussSolver()
{
}

//-------------------------------------------------------------------------------------------------------------
GaussSolver::~GaussSolver()
{
}

//---------------------------------------Прямой ход метода Гаусса----------------------------------------------
void GaussSolver::forwardTrace()
{
	int n = A.getRowCount();

	double divValue;

	for(int k = 0; k < n-1; k++)
	{
		for( int i = k+1; i < n; i++)
		{
			if( A[k][k] != 0 )
			{
				divValue = A[i][k] / A[k][k];
			}
			else divValue = 1;

			A[i][k] = 0;

			for(int j = k+1; j < n; j++)
			{
				A[i][j] = A[i][j] - divValue * A[k][j];				
			}

			b[i] = b[i] - divValue * b[k];
		}
	}
}

//---------------------------------------Обратный ход метода Гаусса--------------------------------------------
Vector GaussSolver::reverseTrace()
{
	int n = A.getRowCount() - 1;

	double sumValue = 0;

	Vector solution(A.getRowCount());

	for( int k = n; k >= 0; k--)
	{	
		sumValue = 0;

		for(int j = k+1; j <= n; j++)
		{
			sumValue += A[k][j]*solution[j];
		}
		
		if( A[k][k] != 0 ) 
		{
			solution[k] = (b[k] - sumValue)/A[k][k];
		}
		else solution[k] = 0;
	}

	return solution;
}

//-------------------------------------------------------------------------------------------------------------
Vector GaussSolver::solve()
{		
	forwardTrace();
		
	return reverseTrace();
}

