#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include "SolverLibMacros.h"

using namespace std;

/* Vector
   Класс реализует математический вектор
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

	double& operator[] (int i); //установка элемента вектора
	double  operator[] (int i) const;  //получение элемента вектора

	bool isNull();  //проверка на нулевые элементы
	bool isUnit();  //проверка на единичный вектор
	bool isIsotropic(); //проверка на изотропный вектор

	int    getSize(); //получение размера вектора
	double getNorm(); //получение нормы вектора
	double getData(int i);

	double Sum();  //сумма элементов вектора
	double Multiply(); //произведение элементов вектора
	double Max();       //максимальный элемент вектора  		
	double Min();	   //минимальный элемент вектора
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
