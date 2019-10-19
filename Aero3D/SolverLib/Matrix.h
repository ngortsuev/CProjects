#pragma once

#include <cmath>
#include <cstdlib>
#include <string>
#include "Vector.h"
#include "SolverLibMacros.h"

using namespace std;

/* Matrix
   Класс реализует матрицу (линейная алгебра)
*/
class DLLExport Matrix
{
protected:
	double **data;
	int rows, cols;

	void allocateMemory(int rows, int cols);	
	void freeMemory();
	void clearMemory();
	void copy(double **src);

public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, bool clear);
	Matrix(Matrix &m);
	virtual ~Matrix(void);		

	Matrix& operator=(double value);
	Matrix& operator=(const Matrix& m);

	Matrix& operator++(int);
	Matrix& operator--(int);

	Matrix operator+(Matrix& m);
	Matrix operator-(Matrix& m);
	Matrix operator*(Matrix& m);
	Matrix operator+(double value);
	Matrix operator-(double value);
	Matrix operator*(double value);
	Matrix operator/(double value);	

	Matrix& operator+=(Matrix& m);
	Matrix& operator-=(Matrix& m);
	Matrix& operator*=(Matrix& m);
	Matrix& operator+=(double value);
	Matrix& operator-=(double value);
	Matrix& operator*=(double value);
	Matrix& operator/=(double value);

	double* operator[] (int i);
	
	double& operator() (int i, int j);
	double  operator() (int i, int j) const;
	
	bool operator==(double value);
	bool operator!=(double value);
	bool operator==(Matrix& m);
	bool operator!=(Matrix& m);

	bool isNull();		//проверка на равенство нулю всех элементов матрицы
	bool isIdentity();	//проверка на равенство единичной матрице
	bool isQuadratic(); //проверка на квадратность матрицы (кол-во строк == кол-ву столбцов)
	bool isNullDet();	//проверка на равенство нулю определителя (детерминанта) матрицы

	Vector getMainDiagonal();		//получение главной диагонали матрицы
	Vector getSecondaryDiagonal();	//получение второй диагонали матрицы
	
	Matrix getTransposedMatrix();			//транспонированная матрица
	Matrix getDiagonalMatrix();				//диагональная матрица
	Matrix getAdjointMatrix();				//сопряженная (взаимная или присоединенная)
	Matrix getInverseMatrix();				//обратная матрица
	Matrix getTriangularMatrix();			//треугольная матрица

	double getNorm();												//норма
	double getDeterminant();										//определитель
	double getMinor(int numRow, int numCol, int order);				//минор
	double getAlgebrComplement(int numRow, int numCol, int order);	//алгебраическое дополнение
	int    getRang();												//ранг матрицы	

	int    getRowCount();
	int    getColCount();

	Vector getRow(int i);
	Vector getCol(int j);
	double getCell(int i, int j);
		
	void setNull();
	void setIdentity(); 
	void setTransposition();
	void setCell(int i, int j, double value);

	double Sum();		//сумма элементов матрицы
	double Multiply();  //произведение элементов матрицы
	double Max();       //максимальный элемент матрицы 		
	double Min();	    //минимальный элемент матрицы
	double Middle();	//среднее значение элементов матрицы

	void readFromFile(const string filename);
	void writeToFile(const string filename);

	void print();	
	void println();	
};
