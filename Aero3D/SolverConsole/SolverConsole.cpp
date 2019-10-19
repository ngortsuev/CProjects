// SolverConsole.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "VectorTest.h"
#include "MatrixTest.h"
#include "SolverTest.h"

using namespace std;

//-------------------------------------------------------------------------------------------------------------
void printResult(int &numberTest, string methodName, int resultTest)
{
	if( resultTest )
	
		cout<<numberTest<<": "<<methodName<<" OK"<<endl;

	else cout<<numberTest<<": "<<methodName<<" FAILE"<<endl;

	numberTest++;
}

//-------------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	bool print = false;
	
	int numberTest;

	VectorTest vectorTest;
	MatrixTest matrixTest;
	SolverTest solverTest;

	//-------------------------------------------Test of class Vector---------------------------------------------
	numberTest = 1;
	
	cout<<"-------Test of class Vector-------"<<endl;

	printResult(numberTest, "VectorConstructorTest -----", vectorTest.VectorConstructorTest(print) );
	printResult(numberTest, "VectorCopyConstructorTest -", vectorTest.VectorCopyConstructorTest(print) );
	
	printResult(numberTest, "isNullTest ----------------", vectorTest.isNullTest(print) );
	printResult(numberTest, "isUnitTest ----------------", vectorTest.isUnitTest(print) );
	printResult(numberTest, "isIsotropicTest -----------", vectorTest.isIsotropicTest(print) );
	
	printResult(numberTest, "getDataTest ---------------", vectorTest.getDataTest(print) );
	printResult(numberTest, "getNormTest ---------------", vectorTest.getNormTest(print) );
	printResult(numberTest, "getSizeTest ---------------", vectorTest.getSizeTest(print) );

	printResult(numberTest, "setDataTest ---------------", vectorTest.setDataTest(print) );
	printResult(numberTest, "setNullTest --------------", vectorTest.setNullTest(print) );
	printResult(numberTest, "setSizeTest --------------", vectorTest.setSizeTest(print) );
	printResult(numberTest, "setUnitTest --------------", vectorTest.setUnitTest(print) );

	printResult(numberTest, "MaxTest ------------------", vectorTest.MaxTest(print));
	printResult(numberTest, "MinTest ------------------", vectorTest.MinTest(print));
	printResult(numberTest, "MiddleTest ---------------", vectorTest.MiddleTest(print));
	printResult(numberTest, "MultiplyTest -------------", vectorTest.MultiplyTest(print));
	printResult(numberTest, "SumTest ------------------", vectorTest.SumTest(print));

	printResult(numberTest, "readTest -----------------", vectorTest.readTest(print));
	printResult(numberTest, "readTest2 ----------------", vectorTest.readTest2(print));
	printResult(numberTest, "readTest3 ----------------", vectorTest.readTest3(print));

	printResult(numberTest, "writeTest ----------------", vectorTest.writeTest(print));
	printResult(numberTest, "writeTest2 ---------------", vectorTest.writeTest2(print));

	printResult(numberTest, "operatorTest -------------", vectorTest.operatorTest(print));

	cout<<"-----End test of class Vector-----"<<endl<<endl;
	
	//-------------------------------------------Test of class Matrix---------------------------------------------
	numberTest = 1;

	cout<<"-------Test of class Matrix-------"<<endl;

	printResult(numberTest, "MatrixConstructorTest -----", matrixTest.MatrixConstructorTest(print) );
	printResult(numberTest, "MatrixConstructorTest2 ----", matrixTest.MatrixConstructorTest2(print) );
	printResult(numberTest, "MatrixCopyConstructorTest -", matrixTest.MatrixCopyConstructorTest(print) );

	printResult(numberTest, "isNullTest ----------------", matrixTest.isNullTest(print) );
	printResult(numberTest, "isIdentityTest ------------", matrixTest.isIdentityTest(print) );
	printResult(numberTest, "isQuadraticTest -----------", matrixTest.isQuadraticTest(print) );
	printResult(numberTest, "isNullDetTest -------------", matrixTest.isNullDetTest(print) );

	printResult(numberTest, "getMainDiagonalTest -------", matrixTest.getMainDiagonalTest(print) );
	printResult(numberTest, "getSecondaryDiagonalTest --", matrixTest.getSecondaryDiagonalTest(print) );

	printResult(numberTest, "getTransposedMatrixTest --", matrixTest.getTransposedMatrixTest(print) );

//	printResult(numberTest, "getDiagonalMatrixTest ----", matrixTest.getDiagonalMatrixTest(print) );
	printResult(numberTest, "getAdjointMatrixTest -----", matrixTest.getAdjointMatrixTest(print) );
	printResult(numberTest, "getInverseMatrixTest -----", matrixTest.getInverseMatrixTest(print) );

	printResult(numberTest, "getTriangularMatrixTest --", matrixTest.getTriangularMatrixTest(print) );

	printResult(numberTest, "getNormTest --------------", matrixTest.getNormTest(print) );
	printResult(numberTest, "getDeterminantTest -------", matrixTest.getDeterminantTest(print) );
	printResult(numberTest, "getMinorTest -------------", matrixTest.getMinorTest(print) );

	printResult(numberTest, "getAlgebrComplementTest --", matrixTest.getAlgebrComplementTest(print) );
	printResult(numberTest, "getRangTest --------------", matrixTest.getRangTest(print) );

	printResult(numberTest, "getRowCountTest ----------", matrixTest.getRowCountTest(print) );
	printResult(numberTest, "getColCountTest ----------", matrixTest.getColCountTest(print) );

	printResult(numberTest, "getRowTest ---------------", matrixTest.getRowTest(print) );
	printResult(numberTest, "getColTest ---------------", matrixTest.getColTest(print) );
	printResult(numberTest, "getCellTest --------------", matrixTest.getCellTest(print) );

	printResult(numberTest, "setNullTest --------------", matrixTest.setNullTest(print) );
	printResult(numberTest, "setIdentityTest ----------", matrixTest.setIdentityTest(print) );
	printResult(numberTest, "setTranspositionTest -----", matrixTest.setTranspositionTest(print) );
	printResult(numberTest, "setCellTest --------------", matrixTest.setCellTest(print) );

	printResult(numberTest, "SumTest ------------------", matrixTest.SumTest(print) );
	printResult(numberTest, "MultiplyTest -------------", matrixTest.MultiplyTest(print) );
	printResult(numberTest, "MaxTest ------------------", matrixTest.MaxTest(print) );
	printResult(numberTest, "MinTest ------------------", matrixTest.MinTest(print) );
	printResult(numberTest, "MiddleTest ---------------", matrixTest.MiddleTest(print) );

	printResult(numberTest, "readFromFileTest ---------", matrixTest.readFromFileTest(print) );
	printResult(numberTest, "readFromFileTest2 --------", matrixTest.readFromFileTest2(print) );
	printResult(numberTest, "readFromFileTest3 --------", matrixTest.readFromFileTest3(print) );

	printResult(numberTest, "writeToFileTest ----------", matrixTest.writeToFileTest(print) );
	printResult(numberTest, "writeToFileTest2 ---------", matrixTest.writeToFileTest2(print) );
	printResult(numberTest, "writeToFileTest3 ---------", matrixTest.writeToFileTest3(print) );

	printResult(numberTest, "operatorTest -------------", matrixTest.operatorTest(print) );

	cout<<"-----End test of class Matrix-----"<<endl<<endl;

	//-------------------------------------------Test of class GaussSolver-------------------------------------
	numberTest = 1;
	
	cout<<"----Test of class GaussSolver-----"<<endl;

	printResult(numberTest, "setMatrixATest ------------", solverTest.setMatrixATest(print) );
	printResult(numberTest, "setVectorBTest ------------", solverTest.setVectorBTest(print) );
	printResult(numberTest, "solveTest1 ----------------", solverTest.solveTest1(print) );
	printResult(numberTest, "solveTest2 ----------------", solverTest.solveTest2(print) );
	printResult(numberTest, "solveTest3 ----------------", solverTest.solveTest3(print) );
	printResult(numberTest, "solveTest4 ----------------", solverTest.solveTest4(print) );
	printResult(numberTest, "solveTest5 ----------------", solverTest.solveTest5(print) );
	printResult(numberTest, "solveTest6 ----------------", solverTest.solveTest6(print) );
	printResult(numberTest, "solveTest7 ----------------", solverTest.solveTest7(print) );

	cout<<"---End test of class GaussSolver--"<<endl;

	_getch();

	return 0;
}


