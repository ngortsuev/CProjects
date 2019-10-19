#pragma once

#include <cmath>
#include <cstdlib>
#include <string>
#include "Vector.h"
#include "SolverLibMacros.h"

using namespace std;

/* Matrix
   ����� ��������� ������� (�������� �������)
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

	bool isNull();		//�������� �� ��������� ���� ���� ��������� �������
	bool isIdentity();	//�������� �� ��������� ��������� �������
	bool isQuadratic(); //�������� �� ������������ ������� (���-�� ����� == ���-�� ��������)
	bool isNullDet();	//�������� �� ��������� ���� ������������ (������������) �������

	Vector getMainDiagonal();		//��������� ������� ��������� �������
	Vector getSecondaryDiagonal();	//��������� ������ ��������� �������
	
	Matrix getTransposedMatrix();			//����������������� �������
	Matrix getDiagonalMatrix();				//������������ �������
	Matrix getAdjointMatrix();				//����������� (�������� ��� ��������������)
	Matrix getInverseMatrix();				//�������� �������
	Matrix getTriangularMatrix();			//����������� �������

	double getNorm();												//�����
	double getDeterminant();										//������������
	double getMinor(int numRow, int numCol, int order);				//�����
	double getAlgebrComplement(int numRow, int numCol, int order);	//�������������� ����������
	int    getRang();												//���� �������	

	int    getRowCount();
	int    getColCount();

	Vector getRow(int i);
	Vector getCol(int j);
	double getCell(int i, int j);
		
	void setNull();
	void setIdentity(); 
	void setTransposition();
	void setCell(int i, int j, double value);

	double Sum();		//����� ��������� �������
	double Multiply();  //������������ ��������� �������
	double Max();       //������������ ������� ������� 		
	double Min();	    //����������� ������� �������
	double Middle();	//������� �������� ��������� �������

	void readFromFile(const string filename);
	void writeToFile(const string filename);

	void print();	
	void println();	
};
