#include "StdAfx.h"
#include "Vector.h"
#include "VectorFile.h"


//-------------------------------------------------------------------------------------------------------------
Vector::Vector()
{
	data = NULL;
}

//-------------------------------------------------------------------------------------------------------------
Vector::Vector(int size)
{
	this->size = size;

	data = new double[size];
}

//-------------------------------------------------------------------------------------------------------------
Vector::Vector(int size, bool clear)
{
	this->size = size;

	data = new double[size];

	if( clear )for(int i = 0; i < size; i++)data[i] = 0;
}

//-------------------------------------------------------------------------------------------------------------
Vector::Vector(const Vector& v)
{
	size = v.size;

	data = new double[size];

	for(int i =0; i < size; i++)data[i] = v.data[i];
}

//-------------------------------------------------------------------------------------------------------------
Vector::~Vector(void)
{
	if( data != NULL )delete[] data;
}

//-------------------------------------------------------------------------------------------------------------
/*
Vector::operator double*()
{
	return data;
}
*/

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator=(double v)
{
	for(int i = 0; i < size; i++) data[i] = v;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator=(const Vector& v)
{
	size = v.size;

	if( data != NULL )delete[] data;

	data = new double[size];

	for(int i = 0; i < size; i++) data[i] = v.data[i];

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator++(int)
{
	for(int i = 0; i < size; i++) data[i]++;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator--(int)
{
	for(int i = 0; i < size; i++) data[i]--;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator+(Vector& v)
{
	if( size == v.size )
	{
		Vector temp(size);

		for(int i = 0; i < size; i++) temp.data[i] = data[i] + v.data[i];

		return temp;
	}
	else return NULL;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator-(Vector& v)
{
	if( size == v.size )
	{
		Vector temp(size);

		for(int i = 0; i < size; i++) temp.data[i] = data[i] - v.data[i];

		return temp;
	}
	else return NULL;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator*(Vector& v)
{
	if( size == v.size )
	{
		Vector temp(size);

		for(int i = 0; i < size; i++) temp.data[i] = data[i] * v.data[i];

		return temp;
	}
	else return NULL;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator+(double value)
{
	Vector temp(size);

	for(int i = 0; i < size; i++) temp.data[i] = data[i] + value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator-(double value)
{
	Vector temp(size);

	for(int i = 0; i < size; i++) temp.data[i] = data[i] - value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator*(double value)
{
	Vector temp(size);

	for(int i = 0; i < size; i++) temp.data[i] = data[i] * value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Vector Vector::operator/(double value)
{
	Vector temp(size);

	for(int i = 0; i < size; i++) temp.data[i] = data[i] / value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator+=(Vector& v)
{
	if( size == v.size)
	
		for(int i = 0; i < size; i++) data[i] += v.data[i];

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator-=(Vector& v)
{
	if( size == v.size)

		for(int i = 0; i < size; i++) data[i] -= v.data[i];

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator*=(Vector& v)
{
	if( size == v.size)
	
		for(int i = 0; i < size; i++) data[i] *= v.data[i];
		
	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator+=(double value)
{	
	for(int i = 0; i < size; i++) data[i] += value;

	return *this;	
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator-=(double value)
{
	for(int i = 0; i < size; i++) data[i] -= value;

	return *this;	
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator*=(double value)
{
	for(int i = 0; i < size; i++) data[i] *= value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Vector& Vector::operator/=(double value)
{
	for(int i = 0; i < size; i++) data[i] /= value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
bool Vector::operator==(Vector& v)
{
	if( size == v.size)
	{
			for(int i = 0; i < size; i++) 

				if( data[i] != v.data[i] )return false;
			
			return true;
	}
	else return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Vector::operator!=(Vector& v)
{
	if( size == v.size)
	{
			for(int i = 0; i < size; i++) 

				if( data[i] != v.data[i] )return true;
			
			return false;
	}
	else return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Vector::operator==(double value)
{
	for(int i = 0; i < size; i++) 

		if( data[i] != value )return false;
			
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Vector::operator!=(double value)
{
	for(int i = 0; i < size; i++) 

		if( data[i] != value )return true;
			
	return false;
}

//---------------------------------------установка элемента вектора--------------------------------------------
double& Vector::operator[] (int i) 
{
	if( i >=0 && i < size )return data[i];	
}

//---------------------------------------получение элемента вектора--------------------------------------------
double Vector::operator[] (int i) const  
{
	if( i >=0 && i < size )return data[i];
}

//---------------------------------------проверка на нулевые элементы------------------------------------------
bool Vector::isNull()  
{
	for(int i = 0; i < size; i++) 

		if( data[i] != 0 ) return false;

	return true;
}

//---------------------------------------проверка на единичный вектор------------------------------------------
bool Vector::isUnit()  
{
	for(int i = 0; i < size; i++) 

		if( data[i] != 1 ) return false;

	return true;
}

//---------------------------------------проверка на изотропный вектор-----------------------------------------
bool Vector::isIsotropic()  
{
	double value = 0;

	for(int i = 0; i < size; i++) 

		value += pow(data[i], 2);

	if( value == 0) return true;
	else return false;
}

//---------------------------------------получение размера вектора---------------------------------------------
int Vector::getSize() 
{
	return size;
}

//---------------------------------------получение нормы вектора-----------------------------------------------
double Vector::getNorm() 
{
	double value = 0;

	for(int i = 0; i < size; i++)

		value += pow(data[i], 2);

	return sqrt(value);
}

//-------------------------------------------------------------------------------------------------------------
double Vector::getData(int i)
{
	if( i >= 0 && i < size )return data[i];	
}

//---------------------------------------Сумма элементов вектора-----------------------------------------------
double Vector::Sum() 
{
	double value = 0;

	for(int i = 0; i < size; i++)

		value += data[i];

	return value;
}

//---------------------------------------Произведение элементоа вектора----------------------------------------
double Vector::Multiply() 
{
	double value = 1;

	for(int i = 0; i < size; i++)

		value *= data[i];

	return value;
}

//---------------------------------------Получение максимального элемента вектора------------------------------
double Vector::Max()
{
	double maxValue = data[0];

	for(int i = 1; i < size; i++)
			
		if( maxValue < data[i] )maxValue = data[i];
	
	return maxValue;
}

//---------------------------------------Получение минимального элемента вектора------------------------------
double Vector::Min()
{
	double minValue = data[0];

	for(int i = 1; i < size; i++)
			
		if( minValue > data[i] )minValue = data[i];
	
	return minValue;
}

//---------------------------------------Получение среднего значения элемента вектора--------------------------
double Vector::Middle()
{
	double middleValue = 0;

	for(int i = 0; i < size; i++)
			
		middleValue += data[i];
	
	return middleValue/size;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//------------------------------------------    Set Procedures    ---------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

//---------------------------------------Обнуление вектора-----------------------------------------------------
void Vector::setNull()
{
	for(int i = 0; i < size; i++)data[i] = 0;
}

//---------------------------------------Установка единичного вектора------------------------------------------
void Vector::setUnit()
{
	for(int i = 0; i < size; i++)data[i] = 1;
}

//---------------------------------------Установка размера вектора---------------------------------------------
void Vector::setSize(int newSize)
{
	if( size != newSize )
	{
		
		if( size < newSize) 
		{
			Vector temp(size);

			for(int i = 0; i < size; i++) temp.data[i] = data[i];

			delete[] data;

			data = new double[newSize];

			for(int i = 0; i < size; i++) data[i] = temp.data[i];

			for(int i = size; i < newSize; i++) data[i] = 0;
		}

		if( size > newSize )
		{
			Vector temp(newSize);

			for(int i = 0; i < newSize; i++) temp.data[i] = data[i];

			delete[] data;

			data = new double[newSize];

			for(int i = 0; i < newSize; i++) data[i] = temp.data[i];			
		}

		size = newSize;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Vector::setData(int i, double value)
{
	if( i >=0 && i < size )data[i] = value;
}

//-------------------------------------------------------------------------------------------------------------
void Vector::readFromFile(const string filename)
{
	VectorFile *file = (new VectorFileFactory())->CreateVectorFile(TXT, filename);

	file->read(*this);

	delete file;
}

//-------------------------------------------------------------------------------------------------------------
void Vector::writeToFile(const string filename)
{
	VectorFile *file = (new VectorFileFactory())->CreateVectorFile(TXT, filename);

	file->write(*this);

	delete file;
}

//-------------------------------------------------------------------------------------------------------------
void Vector::print()
{
	for(int i = 0; i < size; i++)cout<<data[i]<<" ";
}

//-------------------------------------------------------------------------------------------------------------
void Vector::println()
{
	for(int i = 0; i < size; i++)cout<<data[i]<<" ";

	cout<<endl;
}