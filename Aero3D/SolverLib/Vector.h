#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include "SolverLibMacros.h"

using namespace std;

/* Vector
   ����� ��������� �������������� ������
*/
class DLLExport Vector
{
protected:
	double *data;
	int size;
public:
	Vector();
	Vector(int size);
	Vector(int size, bool clear);
	Vector(const Vector &v);
    virtual ~Vector(void);

	//operator double*();

    Vector& operator=(double v);
    Vector& operator=(const Vector& v);

    Vector& operator++(int);
    Vector& operator--(int);

    Vector operator+(Vector& v);
    Vector operator-(Vector& v);
	Vector operator*(Vector& v);	
    Vector operator+(double value);
    Vector operator-(double value);
    Vector operator*(double value);
    Vector operator/(double value);

    Vector& operator+=(Vector& v);
    Vector& operator-=(Vector& v);
	Vector& operator*=(Vector& v);	
    Vector& operator+=(double value);
    Vector& operator-=(double value);
    Vector& operator*=(double value);
    Vector& operator/=(double value);
	
    bool operator==(Vector& v);
    bool operator!=(Vector& v);
	bool operator==(double value);
	bool operator!=(double value);

	double& operator[] (int i); //��������� �������� �������
	double  operator[] (int i) const;  //��������� �������� �������

	bool isNull();  //�������� �� ������� ��������
	bool isUnit();  //�������� �� ��������� ������
	bool isIsotropic(); //�������� �� ���������� ������

	int    getSize(); //��������� ������� �������
	double getNorm(); //��������� ����� �������
	double getData(int i);

	double Sum();  //����� ��������� �������
	double Multiply(); //������������ ��������� �������
	double Max();       //������������ ������� �������  		
	double Min();	   //����������� ������� �������
	double Middle();

	void setNull();
	void setUnit();
	void setSize(int size);
	void setData(int i, double data);

	void readFromFile(const string filename);
	void writeToFile(const string filename);

	void print();
	void println();
};
