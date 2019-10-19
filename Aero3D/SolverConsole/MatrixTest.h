#pragma once

#include "Vector.h"
#include "Matrix.h"

class MatrixTest
{
public:
	MatrixTest(void);
	virtual ~MatrixTest(void);

	int MatrixConstructorTest(bool print);
	int MatrixConstructorTest2(bool print);
	int MatrixCopyConstructorTest(bool print);

	int isNullTest(bool print);		
	int isIdentityTest(bool print);	
	int isQuadraticTest(bool print); 
	int isNullDetTest(bool print);	

	int getMainDiagonalTest(bool print);		
	int getSecondaryDiagonalTest(bool print);	
	
	int getTransposedMatrixTest(bool print);		
	int getDiagonalMatrixTest(bool print);			
	int getAdjointMatrixTest(bool print);			
	int getInverseMatrixTest(bool print);			
	int getTriangularMatrixTest(bool print);		

	int getNormTest(bool print);												
	int getDeterminantTest(bool print);										
	int getMinorTest(bool print);
	int getAlgebrComplementTest(bool print);
	int getRangTest(bool print);			

	int getRowCountTest(bool print);
	int getColCountTest(bool print);

	int getRowTest(bool print);
	int getColTest(bool print);
	int getCellTest(bool print);
		
	int setNullTest(bool print);
	int setIdentityTest(bool print); 
	int setTranspositionTest(bool print);
	int setCellTest(bool print);

	int SumTest(bool print);	
	int MultiplyTest(bool print);
	int MaxTest(bool print);
	int MinTest(bool print);
	int MiddleTest(bool print);

	int readFromFileTest(bool print);
	int readFromFileTest2(bool print);
	int readFromFileTest3(bool print);
	int writeToFileTest(bool print);
	int writeToFileTest2(bool print);
	int writeToFileTest3(bool print);

	int operatorTest(bool print);
};
