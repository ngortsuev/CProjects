#include "StdAfx.h"
#include "Matrix.h"
#include "MatrixFile.h"


//-------------------------------------------------------------------------------------------------------------
Matrix::Matrix()
{
	data = NULL;
}

//-------------------------------------------------------------------------------------------------------------
Matrix::Matrix(int _rows, int _cols)
{		
	allocateMemory(_rows, _cols);
}

//-------------------------------------------------------------------------------------------------------------
Matrix::Matrix(int _rows, int _cols, bool clear)
{		
	allocateMemory(_rows, _cols);

	if( clear )clearMemory();
}

//-------------------------------------------------------------------------------------------------------------
Matrix::Matrix(Matrix &m)
{
	if( &m != NULL )
	{
		allocateMemory(m.rows, m.cols);		

		this->copy(m.data);
	}
}

//-------------------------------------------------------------------------------------------------------------
Matrix::~Matrix(void)
{
	if( data != NULL )freeMemory();
}

//---------------------------------------��������� ������ ��� ��������� ������ ������--------------------------
void Matrix::allocateMemory(int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;

	if( rows != 0 && cols != 0)
	{
		data = new double*[rows];
		
		for(int i = 0; i < rows; i++) 
		
			data[i] = new double[cols];		
	}
}

//---------------------------------------������������ ������---------------------------------------------------
void Matrix::freeMemory()
{
	for(int i = 0; i < rows; i++)

		delete[] data[i];

	delete[] data;
}

//---------------------------------------������� ������--------------------------------------------------------
void Matrix::clearMemory()
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] = 0;
}

//---------------------------------------����������� �������---------------------------------------------------
void Matrix::copy(double **src)
{
	if( src != NULL && data != NULL )
	{
		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				data[i][j] = src[i][j];
	}
}

/**************************************************************************************************************
*																											  *
*										 operators	=			  		                    				  *	
*																											  *		
**************************************************************************************************************/
Matrix& Matrix::operator=(double value)
{
	if( data != NULL)

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				data[i][j] = value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator=(const Matrix& m)
{
	if( &m != NULL || &m != this)
	{
		if( data != NULL )freeMemory();
		
		allocateMemory(m.rows, m.cols);
		
		copy(m.data);
	}

	return *this;
}

/**************************************************************************************************************
*																											  *
*										 operators	++, --		  		                    				  *	
*																											  *		
**************************************************************************************************************/
Matrix& Matrix::operator++(int)
{
	if( data != NULL )

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				data[i][j]++;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator--(int)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j]--;

	return *this;
}

/**************************************************************************************************************
*																											  *
*										 operators	+, -, *, /  		                    				  *	
*																											  *		
**************************************************************************************************************/
Matrix Matrix::operator+(Matrix& m)
{
	if( rows == m.rows && cols == m.cols )
	{	
		Matrix temp(rows, cols);

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				temp.data[i][j] = data[i][j] + m.data[i][j];

		return temp;
	}	
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator-(Matrix& m)
{
	if( rows == m.rows && cols == m.cols )
	{	
		Matrix temp(rows, cols);

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				temp.data[i][j] = data[i][j] - m.data[i][j];

		return temp;
	}	
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator*(Matrix& m)
{
	if( cols == m.rows )
	{	
		double value = 0;

		Matrix temp(rows, m.cols);

		for(int i = 0; i < temp.rows; i++)

			for(int j = 0; j < temp.cols; j++)
			{
				for(int k = 0; k < cols; k++)
				{
					value += data[i][k]*m.data[k][j];
				}

				temp.data[i][j] = value;

				value = 0;
			}

		return temp;
	}	
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator+(double value)
{
	Matrix temp(rows, cols);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[i][j] = data[i][j] + value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator-(double value)
{
	Matrix temp(rows, cols);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[i][j] = data[i][j] - value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator*(double value)
{
	Matrix temp(rows, cols);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[i][j] = data[i][j] * value;

	return temp;
}

//-------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator/(double value)
{
	Matrix temp(rows, cols);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[i][j] = data[i][j] / value;

	return temp;
}

/**************************************************************************************************************
*																											  *
*										 operators	+=, -=, *=, /=		                    				  *	
*																											  *		
**************************************************************************************************************/
Matrix& Matrix::operator+=(Matrix& m)
{
	if( rows == m.rows && cols == m.cols )	
	{
		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				data[i][j] += m.data[i][j];
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator-=(Matrix& m)
{
	if( rows == m.rows && cols == m.cols )	
	{
		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				data[i][j] -= m.data[i][j];
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator*=(Matrix& m)
{
	return (*this = *this * m);	
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator+=(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] += value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator-=(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] -= value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator*=(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] *= value;

	return *this;
}

//-------------------------------------------------------------------------------------------------------------
Matrix& Matrix::operator/=(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] /= value;

	return *this;
}

/**************************************************************************************************************
*																											  *
*										 operators	[], (), ==, !=		                    				  *	
*																											  *		
**************************************************************************************************************/
double* Matrix::operator [] (int i)
{
	if( i >= 0 && i < rows )return data[i];
}

//-------------------------------------------------------------------------------------------------------------
double& Matrix::operator () (int i, int j)
{
	if( i >= 0 && i < rows )
		if( j >= 0 && j < cols)return data[i][j];
}

//-------------------------------------------------------------------------------------------------------------
double Matrix::operator () (int i, int j) const
{
	if( i >= 0 && i < rows )
		if( j >= 0 && j < cols)return data[i][j];
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::operator==(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( data[i][j] != value )return false;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::operator!=(double value)
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( data[i][j] != value )return true;

	return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::operator==(Matrix& m)
{
	if( rows != m.rows || cols != m.cols) return false;

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( data[i][j] != m.data[i][j] )return false;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::operator!=(Matrix& m)
{
	if( rows != m.rows || cols != m.cols) return true;

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( data[i][j] != m.data[i][j] )return true;

	return false;
}

/**************************************************************************************************************
*																											  *
*										       Is Procedures	                    						  *	
*																											  *		
**************************************************************************************************************/
bool Matrix::isNull()
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( data[i][j] != 0 )return false;

	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::isIdentity()
{
	if( rows != cols )return false;

	for(int i = 0; i < rows; i++)
	{
		if( data[i][i] != 1 )return false;

		for(int j = 0; j < cols; j++)
		{
			if( i != j )
			{
				if( data[i][j] != 0 )return false;
			}
		}			
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::isQuadratic()
{
	if( rows == cols )
	
		return true;

	else return false;
}

//-------------------------------------------------------------------------------------------------------------
bool Matrix::isNullDet()
{
	if( getDeterminant() == 0 )
		
		return true;

	else return false;
}

/**************************************************************************************************************
*																											  *
*										         Get Procedures                 							  *	
*																											  *		
**************************************************************************************************************/
//---------------------------------------��������� ������� ��������� �������-----------------------------------
//----��� �����-���� �������������� ��������
Vector Matrix::getMainDiagonal()
{
	int size = __min(rows,cols);

	Vector diagonal(size);

	for(int i = 0; i < size; i++)diagonal[i] = data[i][i];

	return diagonal;	
}

//---------------------------------------��������� ������ ��������� �������------------------------------------
//----��� �����-���� �������������� ��������
Vector Matrix::getSecondaryDiagonal()
{
	int size = __min(rows,cols);

	Vector diagonal(size);

	for(int i = 0; i < rows; i++)diagonal[i] = data[(rows-1) - i][i];

	return diagonal;	
}

/**************************************************************************************************************
*																											  *
*										��������� ��������� ����� �������         							  *	
*																											  *		
**************************************************************************************************************/
//---------------------------------------����������������� �������---------------------------------------------
Matrix Matrix::getTransposedMatrix()
{
	Matrix temp(cols, rows);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[j][i] = data[i][j];

	return temp;	
}

//---------------------------------------������������ �������--------------------------------------------------
Matrix Matrix::getDiagonalMatrix()
{
	Matrix diagonal(rows, cols);

	return diagonal;
}

//---------------------------------------����������� �������---------------------------------------------------
Matrix Matrix::getAdjointMatrix()
{
	Matrix adjoint(rows, cols);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			adjoint.data[i][j] = getAlgebrComplement(i,j,1);

	return adjoint;
}

//---------------------------------------������� �������-------------------------------------------------------
Matrix Matrix::getInverseMatrix()
{
	double det = getDeterminant();

	if( det != 0 )
	{
		Matrix m = getAdjointMatrix();

		m.setTransposition();		

		return m / det;
	}
}

//---------------------------------------����������� �������---------------------------------------------------
Matrix Matrix::getTriangularMatrix()
{
	Matrix triang(*this);

	int n = rows;

	double divValue;

	for(int k = 0; k < n-1; k++)
	{
		for( int i = k+1; i < n; i++)
		{
			if( triang.data[k][k] != 0 )
			{ 
				divValue = triang.data[i][k] / triang.data[k][k];
			}
			else divValue = 1;

			triang.data[i][k] = 0;

			for(int j = k+1; j < n; j++)
			{
				triang.data[i][j] = triang.data[i][j] - divValue * triang.data[k][j];
			}
		}		
	}
	return triang;	
}

/**************************************************************************************************************
*																											  *
*										��������� ��������� ������������� �������							  *	
*																											  *		
**************************************************************************************************************/
//---------------------------------------����� �������---------------------------------------------------------
double Matrix::getNorm()
{
	double value = 0;
	
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			value += pow(data[i][j], 2);

	return sqrt(value);
}

//---------------------------------------����������� �������----------------------------------------------------------------------
double Matrix::getDeterminant()
{
	double det = 1;

	Matrix m = getTriangularMatrix();

	for(int i = 0; i < m.rows; i++) det *= m.data[i][i];

	return det;
}

//---------------------------------------����� �������---------------------------------------------------------
double Matrix::getMinor(int numRow, int numCol, int order)
{
	Matrix minor(rows-order, cols-order);

	if( order > 0 )
		
		if( numRow >= 0 && numRow < rows)
		{
			if( numCol >= 0 && numCol < cols)
			{
				for(int i = 0; i < numRow; i++)

					for(int j = 0; j < numCol; j++)
	
						minor[i][j] = data[i][j];

				for(int i = numRow+order; i < rows; i++)

					for(int j = 0; j < numCol; j++)

						minor[i-order][j] = data[i][j];

				for(int i = 0; i < numRow; i++)

					for(int j = numCol+order; j < cols; j++)

						minor[i][j-order] = data[i][j];

				for(int i = numRow+order; i < rows; i++)

					for(int j = numCol+order; j < cols; j++)

						minor[i-order][j-order] = data[i][j];	
			}
		}

	//cout<<"Minor:"<<" row="<<numRow<<" col="<<numCol<<" order="<<order<<endl;

	//minor.println();

	return minor.getDeterminant();	
}

//---------------------------------------�������������� ���������� �������---------------------------------------------------------
double Matrix::getAlgebrComplement(int numRow, int numCol, int order)
{
	double base = -1;

	double deg = pow(base, numRow+numCol);

	return (deg * getMinor(numRow, numCol, order));
}

//---------------------------------------���� �������----------------------------------------------------------
int Matrix::getRang()
{
	int rang;
	Vector v;
	Matrix m;

	rang = rows;

	m = getTriangularMatrix();

	for(int i = 0; i < rows; i++)
	{
		v = m.getRow(i);

		if( v == 0 )rang--;
	}

	return rang;
}


//---------------------------------------��������� ���-�� ����� �������----------------------------------------
int Matrix::getRowCount()
{
	return rows;
}

//---------------------------------------��������� ���-�� �������� �������-------------------------------------
int Matrix::getColCount()
{
	return cols;
}

//---------------------------------------��������� ������ � ������� i------------------------------------------
Vector Matrix::getRow(int i)
{
	if( i >=0 && i < rows)
	{
		Vector temp(cols);

		for(int j = 0; j < cols; j++)temp[j] = data[i][j];

		return temp;
	}
	else return NULL;
}

//---------------------------------------��������� ������� ������� j-------------------------------------------
Vector Matrix::getCol(int j)
{
	if( j >=0 && j < cols)
	{
		Vector temp(rows);

		for(int i = 0; i < rows; i++)temp[i] = data[i][j];

		return temp;
	}
	else return NULL;
}

//-------------------------------------------------------------------------------------------------------------
double Matrix::getCell(int i, int j)
{
	if( i >=0 && i < rows )

		if( j >= 0 && j < cols )

			return data[i][j];

	return NULL;
}

/**************************************************************************************************************
*																											  *		
*										       Set Procedures												  *		
*																											  *
**************************************************************************************************************/
void Matrix::setNull()
{
	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			data[i][j] = 0;
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::setIdentity()
{
	for(int i = 0; i < rows; i++)
	
		for(int j = 0; j < cols; j++)
		{
			data[i][j] = 0;		

			if( i == j )data[i][j] = 1;
		}
	
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::setTransposition()
{
	Matrix temp(cols, rows);

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			temp.data[j][i] = data[i][j];

	*this = temp;
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::setCell(int i, int j, double value)
{
	if( i >=0 && i < rows)

		if( j >=0 && j < cols)

			data[i][j] = value;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//---------------------------------------C���� ��������� �������-----------------------------------------------
double Matrix::Sum()		
{
	double sumValue = 0;

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			sumValue += data[i][j];

	return sumValue;
}

//---------------------------------------������������ ��������� �������----------------------------------------
double Matrix::Multiply()  
{
	double mulValue = 1;

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			mulValue *= data[i][j];	

	return mulValue;
}

//---------------------------------------������������ ������� �������------------------------------------------
double Matrix::Max()
{
	double maxValue = data[0][0];

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( maxValue < data[i][j] )maxValue = data[i][j];

	return maxValue;
}

//---------------------------------------����������� ������� �������-------------------------------------------
double Matrix::Min()	    
{
	double minValue = data[0][0];

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			if( minValue > data[i][j] )minValue = data[i][j];

	return minValue;
}

//---------------------------------------������� �������� ��������� �������------------------------------------
double Matrix::Middle()	
{
	double sumValue = 0;

	for(int i = 0; i < rows; i++)

		for(int j = 0; j < cols; j++)

			sumValue += data[i][j];

	return (sumValue/(rows*cols));
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::readFromFile(const string filename)
{
	MatrixFile *file = (new MatrixFileFactory())->CreateMatrixFile(TXT,filename);

	file->read(this);

	delete file;
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::writeToFile(const string filename)
{
	MatrixFile *file = (new MatrixFileFactory())->CreateMatrixFile(TXT, filename);

	file->write(this);

	delete file;
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::print()
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)

			cout<<data[i][j]<<" ";

		cout<<endl;
	}
}

//-------------------------------------------------------------------------------------------------------------
void Matrix::println()
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)

			cout<<data[i][j]<<" ";

		cout<<endl;
	}

	cout<<endl;
}