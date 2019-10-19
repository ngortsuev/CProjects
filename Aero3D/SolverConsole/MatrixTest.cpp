#include "StdAfx.h"
#include "MatrixTest.h"

//-------------------------------------------------------------------------------------------------------------
MatrixTest::MatrixTest(void)
{
}

//-------------------------------------------------------------------------------------------------------------
MatrixTest::~MatrixTest(void)
{
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MatrixConstructorTest(bool print)
{
	try
	{
		Matrix m(3,3);
		
		if( print )m.println();

		if( m.getRowCount() == 3 && m.getColCount() == 3 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MatrixConstructorTest2(bool print)
{
	try
	{
		Matrix m(3,3, true);
		
		if( print )m.println();

		if( m.getRowCount() == 3 && m.getColCount() == 3 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MatrixCopyConstructorTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);
		
		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				m1.setCell(i,j, 1);

		Matrix m2(m1);
		
		if( print )
		{
			m1.println();
			m2.println();
		}

		if( m1 == m2)return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::isNullTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )m.println();

		if( m.isNull() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::isIdentityTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		for( int i = 0; i < rows; i++)m.setCell(i, i, 1);

		if( print )m.println();
		
		if( m.isIdentity() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::isQuadraticTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )m.println();

		if( m.isQuadratic() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//------------------------------------------------------------------------------------------------------------- 
int MatrixTest::isNullDetTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )m.println();

		if( m.isNullDet() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getMainDiagonalTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		Vector v = m.getMainDiagonal();

		if( print )
		{
			cout<<"Matrix:"<<endl; m.println();

			cout<<"Vector:"; v.println();
		}

		if( v != 0 )return 0;

		for(int i = 0; i < rows; i++)m.setCell(i, i, 1);

		v = m.getMainDiagonal();

		if( print )
		{
			cout<<"Matrix:"<<endl; m.println();
			cout<<"Vector:"; v.println();
		}

		if( v == 1)return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getSecondaryDiagonalTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		Vector v = m.getSecondaryDiagonal();

		if( print )
		{
			cout<<"Matrix:"<<endl; m.println();

			cout<<"Vector:"; v.println();
		}

		if( v != 0 )return 0;

		for(int i = 0; i < rows; i++)m.setCell(rows-i-1, i, 1);

		v = m.getSecondaryDiagonal();

		if( print )
		{
			cout<<"Matrix:"<<endl; m.println();

			cout<<"Vector:"; v.println();
		}

		if( v == 1)return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getTransposedMatrixTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);

		for(int j = 0; j < cols; j++)m1.setCell(0,j,1);

		Matrix m2 = m1.getTransposedMatrix();

		if( print )
		{
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Transposed matrix:"<<endl; m2.println();
		}

		for(int i = 0; i < rows; i++)
		{
			if( m2.getCell(i,0) != 1 )return 0;
		}

		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		m2 = m1.getTransposedMatrix();

		if( print )
		{
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Transposed matrix:"<<endl; m2.println();
		}

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				if( m1.getCell(i,j) != m2.getCell(j,i) )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getDiagonalMatrixTest(bool print)
{
	try
	{
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getAdjointMatrixTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);
		
		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m006.txt");

		Matrix m2 = m1.getAdjointMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1.println();
			cout<<"Adjoint matrix:"<<endl; m2.println();
		}

		if( m2.getCell(0,0) != -1 )return 0;
		if( m2.getCell(0,1) != -1 )return 0;
		if( m2.getCell(0,2) != 1 )return 0;

		if( m2.getCell(1,0) != 4 )return 0;
		if( m2.getCell(1,1) != 5 )return 0;
		if( m2.getCell(1,2) != -6 )return 0;

		if( m2.getCell(2,0) != 3 )return 0;
		if( m2.getCell(2,1) != 3 )return 0;
		if( m2.getCell(2,2) != -4 )return 0;
		
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getInverseMatrixTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);
		
		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m006.txt");

		Matrix m2 = m1.getInverseMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1.println();
			cout<<"Inverse matrix:"<<endl; m2.println();
		}

		if( m2.getCell(0,0) != 1 )return 0;
		if( m2.getCell(0,1) != -4 )return 0;
		if( m2.getCell(0,2) != -3 )return 0;

		if( m2.getCell(1,0) != 1 )return 0;
		if( m2.getCell(1,1) != -5 )return 0;
		if( m2.getCell(1,2) != -3 )return 0;

		if( m2.getCell(2,0) != -1 )return 0;
		if( m2.getCell(2,1) != 6 )return 0;
		if( m2.getCell(2,2) != 4 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getTriangularMatrixTest(bool print)
{
	int rows = 2;
	int cols = 2;
	bool clear = true;

	try
	{
		Matrix *m1 = new Matrix(rows,cols,clear);

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m007.txt");

		Matrix m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m008.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m009.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		delete m1;

		m1 = new Matrix(3,3,clear);

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m010.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m011.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		delete m1;

		m1 = new Matrix(4,4, clear);

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m012.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		} 

		delete m1;

		m1 = new Matrix(5,5, clear);

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m013.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m014.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		delete m1;

		m1 = new Matrix(4,4, clear);

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m015.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		m1->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m016.txt");

		m2 = m1->getTriangularMatrix();

		if( print )
		{
			cout<<"Matrix :"<<endl; m1->println();
			cout<<"Triangular matrix :"<<endl; m2.println();
		}

		delete m1;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getNormTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Norm value:"<<m.getNorm()<<endl;
		}

		if( m.getNorm() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Norm value:"<<m.getNorm()<<endl;
		}

		if( m.getNorm() != 2 )return 0;

		m = 1;

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Norm value:"<<m.getNorm()<<endl;
		}

		if( m.getNorm() != 4 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getDeterminantTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	double det = 0;

	try
	{
		Matrix *m = new Matrix(4, 4, clear);

		m->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m004.txt");

		det = m->getDeterminant();

		if( print )
		{
			cout<<"Matrix :"<<endl; m->println();
			cout<<"Determinant="<<det<<endl;
		}

		if( det != 301 )return 0;

		delete m;

		m = new Matrix(3,3, clear);

		m->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m005.txt");

		det = floor(m->getDeterminant());

		if( print )
		{
			cout<<"Matrix :"<<endl; m->println();
			cout<<"Determinant="<<det<<endl;
		}

		if( det != -7 )return 0;

		delete m;

		m = new Matrix(4,4, clear);

		m->readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m016.txt");

		det = m->getDeterminant();

		if( print )
		{
			cout<<"Matrix :"<<endl; m->println();
			cout<<"Determinant="<<det<<endl;
		}

		if( det != -153 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getMinorTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		double minor = m.getMinor(0,0,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		if( minor != 0 )return 0;

		m.setIdentity();

		minor = m.getMinor(0,0,1);
		
		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		if( minor != 1 )return 0;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		minor = m.getMinor(0,0,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(0,0,2);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(0,0,3);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(0,1,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(0,2,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(0,3,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(1,0,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(1,1,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(1,2,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(1,3,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(2,0,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(3,0,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}

		minor = m.getMinor(3,1,1);

		if( print )
		{
			cout<<"Matrix :"<<endl; m.println();
			cout<<"Minor value:"<<minor<<endl;
		}
		
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getAlgebrComplementTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	double algebr;

	try
	{
		Matrix m(rows, cols, clear);

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m006.txt");

		if( print )
		{
			cout<<"Matrix:"<<endl; 
			m.println();
		}

		algebr = m.getAlgebrComplement(0,0,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != -1 )return 0;

		algebr = m.getAlgebrComplement(0,1,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != -1 )return 0;

		algebr = m.getAlgebrComplement(0,2,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != 1 )return 0;

		algebr = m.getAlgebrComplement(1,0,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != 4 )return 0;

		algebr = m.getAlgebrComplement(1,1,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != 5 )return 0;

		algebr = m.getAlgebrComplement(1,2,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != -6 )return 0;

		algebr = m.getAlgebrComplement(2,0,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != 3 )return 0;

		algebr = m.getAlgebrComplement(2,1,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != 3 )return 0;

		algebr = m.getAlgebrComplement(2,2,1);
		if( print )cout<<"Algebr complement="<<algebr<<endl;
		if( algebr != -4 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getRangTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;
	double rang;

	try
	{
		Matrix m1(4, 4, clear);
		Matrix m2(5, 5, clear);

		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m012.txt");
		rang = m1.getRang();
		if( print )
		{
			cout<<"Matrix :"<<endl; m1.println();
			cout<<"Rang="<<rang<<endl;
		}
		if( rang != 2 )return 0;

		m2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m013.txt");
		rang = m2.getRang();
		if( print )
		{
			cout<<"Matrix :"<<endl; m2.println();
			cout<<"Rang="<<rang<<endl;
		}
		if( rang != 3 )return 0;

		m2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m014.txt");
		rang = m2.getRang();
		if( print )
		{
			cout<<"Matrix :"<<endl; m2.println();
			cout<<"Rang="<<rang<<endl;
		}
		if( rang != 5 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getRowCountTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( m.getRowCount() == rows )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getColCountTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( m.getColCount() == cols )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getRowTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		Vector v = m.getRow(0);

		if( v != 0 )return 0;

		m = 1;

		v = m.getRow(0);

		if( v != 1 )return 0;

		m.setIdentity();

		v = m.getRow(0);

		if( v[0] != 1 )return 0;

		for(int i = 1; i < cols; i++) if(v[i] != 0 )return 0;

		v = m.getRow(1);

		if( v[0] != 0 )return 0;
		if( v[1] != 1 )return 0;

		for(int i = 2; i < cols; i++)if( v[i] != 0 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getColTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		Vector v = m.getCol(0);

		if( v != 0 )return 0;

		m.setIdentity();

		v = m.getCol(0);

		if( v[0] != 1 )return 0;

		for(int i = 1; i < rows; i++)if( v[i] != 0 )return 0;

		v = m.getCol(1);

		if( v[0] != 0 )return 0;
		if( v[1] != 1 )return 0;

		for(int i = 2; i < rows; i++)if( v[i] != 0 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::getCellTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( m.getCell(0,0) != 0 )return 0;

		m.setIdentity();

		if( m.getCell(0,0) != 1 )return 0;
		if( m.getCell(0,1) != 0 )return 0;

		m = 1;

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				if( m.getCell(i,j) != 1 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::setNullTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m = 1;

		m.setNull();

		if( m == 0 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::setIdentityTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m.setIdentity();

		if( m.isIdentity() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::setTranspositionTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				m.setCell(i,j,i);

		if( print )
		{
			cout<<"Matrix (Before transposition):"<<endl;
			m.println();			
		}

		m.setTransposition();

		if( print )
		{
			cout<<"Matrix (After transposition):"<<endl;
			m.println();			
		}

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				if( m.getCell(i,j) != j )return 0;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		if( print )
		{
			cout<<"Matrix (Before transposition):"<<endl;
			m.println();			
		}	

		m.setTransposition();

		if( print )
		{
			cout<<"Matrix (After transposition):"<<endl;
			m.println();			
		}

		if( m.getCell(0,0) != 1 )return 0;
		if( m.getCell(1,0) != -1 )return 0;
		if( m.getCell(2,0) != 1 )return 0;
		if( m.getCell(3,0) != -2 )return 0;
		
		if( m.getCell(0,1) != 1 )return 0;
		if( m.getCell(1,1) != 3 )return 0;
		if( m.getCell(2,1) != -1 )return 0;
		if( m.getCell(3,1) != 3 )return 0;
		
		if( m.getCell(0,2) != -1 )return 0;
		if( m.getCell(1,2) != -1 )return 0;
		if( m.getCell(2,2) != 4 )return 0;
		if( m.getCell(3,2) != 3 )return 0;

		if( m.getCell(0,3) != -3 )return 0;
		if( m.getCell(1,3) != 0 )return 0;
		if( m.getCell(2,3) != -8 )return 0;
		if( m.getCell(3,3) != -14 )return 0;


		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::setCellTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix (Before operation)"<<endl; 
			m.println();			
		}

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				m.setCell(i,j, 1);

		if( print )
		{
			cout<<"Matrix (After operation)"<<endl; 
			m.println();			
		}

		if( m == 1 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::SumTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Sum value:"<<m.Sum()<<endl;
		}

		if( m.Sum() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Sum value:"<<m.Sum()<<endl;
		}

		if( m.Sum() != 4 )return 0;

		m = 1;

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Sum value:"<<m.Sum()<<endl;
		}

		if( m.Sum() != 16)return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MultiplyTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Multiply value:"<<m.Multiply()<<endl;
		}

		if( m.Multiply() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Multiply value:"<<m.Multiply()<<endl;
		}

		if( m.Multiply() != 0 )return 0;

		m = 1;

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Multiply value:"<<m.Multiply()<<endl;
		}

		if( m.Multiply() != 1 )return 0;

		m = 2;

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Multiply value:"<<m.Multiply()<<endl;
		}

		if( m.Multiply() != pow(2.0,16.0) )return 0;

		m = 3;

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Multiply value:"<<m.Multiply()<<endl;
		}

		if( m.Multiply() != pow(3.0, 16.0) )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MaxTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Max value:"<<m.Max()<<endl;
		}

		if( m.Max() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Max value:"<<m.Max()<<endl;
		}

		if( m.Max() != 1 )return 1;

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				m.setCell(i,j,i+j);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Max value:"<<m.Max()<<endl;
		}

		if( m.Max() != rows+cols-2 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MinTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		
		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Min value:"<<m.Min()<<endl;
		}

		if( m.Min() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Min value:"<<m.Min()<<endl;
		}

		if( m.Min() != 0 )return 0;

		for(int i = 0; i < rows; i++)

			for(int j = 0; j < cols; j++)

				m.setCell(i,j,i+j+1);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Min value:"<<m.Min()<<endl;
		}

		if( m.Min() != 1 )return 0;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Min value:"<<m.Min()<<endl;
		}

		if( m.Min() != -14 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::MiddleTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Middle value:"<<m.Middle()<<endl;
		}

		if( m.Middle() != 0 )return 0;

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Middle value:"<<m.Middle()<<endl;
		}

		if( m.Middle() != 0.25 )return 0;

		m = 1;

		if( print )
		{
			cout<<"Matrix"<<endl; m.println();
			cout<<"Middle value:"<<m.Middle()<<endl;
		}

		if( m.Middle() != 1)return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::readFromFileTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m = 1;

		if( print )
		{
			cout<<"----readFromFileTest----"<<endl;

			cout<<"Matrix (Before read):"<<endl; m.println();
		}

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m001.txt");

		if( print )
		{
			cout<<"Matrix (After read):"<<endl; m.println();
		}

		if( m.isNull() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::readFromFileTest2(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m = 1;

		if( print )
		{
			cout<<"Matrix (Before read):"<<endl; m.println();
		}

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m002.txt");

		if( print )
		{
			cout<<"Matrix (After read):"<<endl; m.println();
		}

		if( m.isIdentity() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::readFromFileTest3(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m = 1;

		if( print )
		{
			cout<<"Matrix (Before read):"<<endl; m.println();
		}

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		if( print )
		{
			cout<<"Matrix (After read):"<<endl; m.println();
		}

		if( m.getCell(0,0) != 1 )return 0;
		if( m.getCell(0,1) != -1 )return 0;
		if( m.getCell(0,2) != 1 )return 0;
		if( m.getCell(0,3) != -2 )return 0;
		
		if( m.getCell(1,0) != 1 )return 0;
		if( m.getCell(1,1) != 3 )return 0;
		if( m.getCell(1,2) != -1 )return 0;
		if( m.getCell(1,3) != 3 )return 0;
		
		if( m.getCell(2,0) != -1 )return 0;
		if( m.getCell(2,1) != -1 )return 0;
		if( m.getCell(2,2) != 4 )return 0;
		if( m.getCell(2,3) != 3 )return 0;

		if( m.getCell(3,0) != -3 )return 0;
		if( m.getCell(3,1) != 0 )return 0;
		if( m.getCell(3,2) != -8 )return 0;
		if( m.getCell(3,3) != -14 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::writeToFileTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m = 1;

		if( print )
		{
			cout<<"Matrix (Before write-read):"<<endl;

			m.println();
		}

		m.writeToFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m001.txt");

		m = 0;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m001.txt");

		if( print )
		{
			cout<<"Matrix (After write-read):"<<endl;

			m.println();
		}

		if( m == 1 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::writeToFileTest2(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);

		m.setIdentity();

		if( print )
		{
			cout<<"Matrix (Before write-read):"<<endl;

			m.println();
		}

		m.writeToFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m002.txt");

		m = 0;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m002.txt");

		if( print )
		{
			cout<<"Matrix (After write-read):"<<endl;

			m.println();
		}

		if( m.isIdentity() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::writeToFileTest3(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);
		Matrix m2(m1);
		
		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m003.txt");

		m1.writeToFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m003.txt");

		m2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\write\\m003.txt");

		if( print )
		{
			cout<<"Matrix 1 (read-write):"<<endl;	m1.println();
			cout<<"Matrix 2 (read):"<<endl;	m2.println();
		}

		if( m1 == m2 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int MatrixTest::operatorTest(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m1(rows, cols, clear);
		Matrix m2(rows, cols, clear);

		m1 = 1;
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				if( m1.getCell(i,j) != 1 )return 0;
		
		m2 = m1;
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < cols; j++)
				if( m2.getCell(i,j) != 1 )return 0;		

		m1++;
		if( m1 != 2 )return 0;

		m1--;
		if( m1 != 1 )return 0;

		m1 = m1 + m2;
		if( m1 != 2 )return 0;

		m1 = m1 - m2;
		if( m1 != 1 )return 0;

		//-----------------------------
		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m010.txt");
		m2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m011.txt");
		if( print )
		{
			cout<<"Before operation"<<endl;
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Matrix 2:"<<endl; m2.println();
		}
		m1 = m1 * m2;
		m2.setIdentity();
		m2 = m2 * 9;
		if( print )
		{
			cout<<"After operation"<<endl;
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Matrix 2:"<<endl; m2.println();
		}
		if( m1 != m2 )return 0;
		m1 = 1;
		m2 = 1;

		//-----------------------------
		m1 = m1 + 1;
		if( m1 != 2 )return 0;

		m1 = m1 - 1;
		if( m1 != 1 )return 0;

		m1 = m1 * 2;
		if( m1 != 2 )return 0;

		m1 = m1 / 2;
		if( m1 != 1 )return 0;

		// +=, -=, *=, /=
		m1 += m2;
		if( m1 != 2 )return 0;

		m1 -= m2;
		if( m1 != 1 )return 0;

		//------------------------------
		m1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m010.txt");
		m2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\matrix\\read\\m011.txt");
		if( print )
		{
			cout<<"Before operation"<<endl;
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Matrix 2:"<<endl; m2.println();
		}
		m1 *= m2;
		m2.setIdentity();
		m2 = m2 * 9;
		if( print )
		{
			cout<<"After operation"<<endl;
			cout<<"Matrix 1:"<<endl; m1.println();
			cout<<"Matrix 2:"<<endl; m2.println();
		}
		if( m1 != m2 )return 0;
		m1 = 1;
		m2 = 1;

		//------------------------------
		m1 += 1;
		if( m1 != 2 )return 0;

		m1 -= 1;
		if( m1 != 1 )return 0;

		m1 *= 2;
		if( m1 != 2 )return 0;

		m1 /= 2;
		if( m1 != 1 )return 0;

		if( m1[0][0] != 1 )return 0;
		if( m1[0][1] != 1 )return 0;
		if( m1[1][0] != 1 )return 0;
		if( m1[1][1] != 1 )return 0;

		if( m1(0,0) != 1 )return 0;
		if( m1(0,1) != 1 )return 0;
		if( m1(1,0) != 1 )return 0;
		if( m1(1,1) != 1 )return 0;

		m1 = 1;
		m2 = 1;

		if( m1 != m2 )return 0;

		m2 = 2;
		if( m1 == m2 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

