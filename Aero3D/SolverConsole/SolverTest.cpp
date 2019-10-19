#include "StdAfx.h"
#include "SolverTest.h"

//-------------------------------------------------------------------------------------------------------------
SolverTest::SolverTest(void)
{
}

//-------------------------------------------------------------------------------------------------------------
SolverTest::~SolverTest(void)
{
}

int SolverTest::getRowCount(int index, int filecount)
{
	int result;
	int pos;
	char str[256];

	result = 0;

	memset(str, '0', sizeof(str));

	fstream file("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\system.txt");

	file.seekg((index-1) * 5);
	
	file.getline(str, sizeof(str), ':');

	pos = atoi(str);

	if( index == pos )
	{
		file.seekg(2);

		file.getline(str, sizeof(str), ';');

		result = atoi(str);
	}

	file.close();

	return result;
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::setMatrixATest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(cols);

		GaussSolver solver;

		solver.setMatrixA(m);

		return 1;
	}
	catch(...)
	{
		return 0;
	}	
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::setVectorBTest(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(cols, clear);

		GaussSolver solver;

		solver.setVectorB(v);

		return 1;
	}
	catch(...)
	{
		return 0;
	}	
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest1(bool print)
{
	int rows = 4;
	int cols = 4;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m016.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v016.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != 0 )return 0;
		if( s[1] != 2 )return 0;
		if( s[2] != 5/3 )return 0;
		if( s[3] != -4/3 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest2(bool print)
{
	int rows = 5;
	int cols = 5;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m017.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v017.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != 1 )return 0;
		if( s[1] != 0 )return 0;
		if( s[2] != 0 )return 0;
		if( s[3] != 0 )return 0;
		if( s[4] != -2 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest3(bool print)
{
	int rows = 2;
	int cols = 2;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m008.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v008.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != 6.3333333333999979 )return 0;
		if( s[1] != 9.0000000000999965 )return 0;
	
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest4(bool print)
{
	int rows = 2;
	int cols = 2;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m009.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v009.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != 1.4 )return 0;
		if( s[1] != 0.2 )return 0;
	
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest5(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m010.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v010.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != (double)7/(double)9 )return 0;
		if( s[1] != (double)4/(double)9 )return 0;
		if( s[2] != (double)-1/(double)9 )return 0;
	
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest6(bool print)
{
	int rows = 3;
	int cols = 3;
	bool clear = true;

	try
	{
		Matrix m(rows, cols, clear);
		Vector v(rows, clear);
		Vector s(cols, clear);
		GaussSolver solver;

		m.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\m011.txt");
		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\v011.txt");

		solver.setMatrixA(m);
		
		solver.setVectorB(v);

		s = solver.solve();

		if( print )
		{
			cout<<"---Before operation---"<<endl;
			cout<<"Matrix A:"<<endl; m.println();
			cout<<"Vector B:"<<endl; v.println();
			
			cout<<"Triangular Matrix:"<<endl; m.getTriangularMatrix().println();

			cout<<"---After operation---"<<endl;
			cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
			cout<<"Vector B:"<<endl; solver.getVectorB().println();
			
			cout<<endl<<"Solution:"<<endl; s.println();
		}

		if( s[0] != (double)7/(double)9 )return 0;
		if( s[1] != 0 )return 0;
		if( s[2] != (double)-1/(double)3 )return 0;
	
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int SolverTest::solveTest7(bool print)
{
	int size;
	bool clear = true;
	char str[2];
	int filecount = 3;
	string dir = "E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\system\\";
	string m_filename;
	string v_filename;
	string s_filename;

	int result;

	try
	{
		Matrix *fmatrixA; //матрица A системы уравнений (берется из файлов с именем mXXX.txt)
		Vector *fvectorB; //вектор-столбец В системы уравнений (берется из файлов с именем vXXX.txt)
		Vector *fsolution;       //ответ для проверки (берется из файлов с именем sXXX.txt)
		Vector *solution;  //решение, полученное в результате выполнения процедуры solve()
		GaussSolver solver;

		result = 1;

		for(int i = 1; i <= filecount; i++)
		{
			_itoa(i, str, 10);

			if( i < 10 )
			{
				m_filename = dir + "m00" + string(str) + ".txt";
				v_filename = dir + "v00" + string(str) + ".txt";
				s_filename = dir + "s00" + string(str) + ".txt";
			}
			else
			{
				m_filename = dir + "m0" + string(str) + ".txt";
				v_filename = dir + "v0" + string(str) + ".txt";
				s_filename = dir + "s0" + string(str) + ".txt";
			}
			
			size = getRowCount(i, filecount);

			fmatrixA = new Matrix(size, size, clear);
			fvectorB = new Vector(size);
			fsolution = new Vector(size);
			solution = new Vector(size);

			fmatrixA->readFromFile(m_filename);
			fvectorB->readFromFile(v_filename);
			fsolution->readFromFile(s_filename);

			solver.setMatrixA(*fmatrixA);
		
			solver.setVectorB(*fvectorB);

			*solution = solver.solve();

			if( print )
			{
				cout<<"---Before operation---"<<endl;
				cout<<"Matrix A:"<<endl; fmatrixA->println();
				cout<<"Vector B:"<<endl; fvectorB->println();
				cout<<endl<<"Solution (from file):"<<endl; fsolution->println();
			
				cout<<"Triangular Matrix:"<<endl; fmatrixA->getTriangularMatrix().println();

				cout<<"---After operation---"<<endl;
				cout<<"Matrix A:"<<endl; solver.getMatrixA().println();
				cout<<"Vector B:"<<endl; solver.getVectorB().println();
				cout<<endl<<"Solution:"<<endl; solution->println();
			}

			for(int j = 0; j < size; j++)
			{
				if( fabs(fsolution->getData(j) - solution->getData(j)) > 0.000001 )
				{
					if( print )cout<<endl<<"System (from file) "<<str<<"--FAILE"<<endl;

					result = 0;

					break;
				}
			}

			if( print && result )cout<<endl<<"System (from file) "<<str<<"--OK"<<endl;			

			delete fmatrixA;
			delete fvectorB;
			delete fsolution;
			delete solution;
		}
		
		return result;
	}
	catch(...)
	{
		return 0;
	}
}
