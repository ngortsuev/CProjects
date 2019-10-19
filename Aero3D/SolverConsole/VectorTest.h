#pragma once

#include "Vector.h"

class VectorTest
{
protected:
	void *linkFunc;
public:
	VectorTest(void);
	virtual ~VectorTest(void);
	int VectorConstructorTest(bool print);
	int VectorCopyConstructorTest(bool print);
	int isNullTest(bool print);
	int isUnitTest(bool print);
	int isIsotropicTest(bool print);
	int getDataTest(bool print);
	int getNormTest(bool print);
	int getSizeTest(bool print);
	int setDataTest(bool print);
	int setNullTest(bool print);
	int setSizeTest(bool print);
	int setUnitTest(bool print);
	int MaxTest(bool print);
	int MinTest(bool print);
	int MiddleTest(bool print);
	int MultiplyTest(bool print);
	int SumTest(bool print);

	int readTest(bool print);
	int readTest2(bool print);
	int readTest3(bool print);
	int writeTest(bool print);
	int writeTest2(bool print);
	int operatorTest(bool print);
};
