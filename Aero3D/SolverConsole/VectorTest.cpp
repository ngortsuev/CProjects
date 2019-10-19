#include "StdAfx.h"
#include "VectorTest.h"

VectorTest::VectorTest(void)
{	
}

VectorTest::~VectorTest(void)
{
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::VectorConstructorTest(bool print)
{
	try
	{		
		Vector v(5); //TestMethod

		if( print )v.println();

		if( v.getSize() == 5 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::VectorCopyConstructorTest(bool print)
{
	int size = 5;

	try
	{
		Vector v1(size); v1 = 1;

		Vector v2(v1); //TestMethod

		if( print )
		{
			v1.println();

			v2.println();
		}

		if( v1 == v2 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::isNullTest(bool print)
{
	try
	{
		Vector v(10); v = 0;

		if( print )v.println();

		if( v.isNull() )return 1; //TestMethod
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::isUnitTest(bool print)
{
	try
	{
		Vector v(10); v = 1;

		if( print )v.println();

		if( v.isUnit() )return 1; //TestMethod
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::isIsotropicTest(bool print)
{
	try
	{
		Vector v(10); v = 0;

		if( print )v.println();

		if( v.isIsotropic() )return 1; //TestMethod
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::getDataTest(bool print)
{
	try
	{
		Vector v(5); 
		
		for(int i = 0; i < 5; i++) v[i] = i;

		if( print )v.println();

		for(int i = 0; i < 5; i++) if( v.getData(i) != i )return 0; //TestMethod

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::getNormTest(bool print)
{
	try
	{
		Vector v(4);

		v = 1;

		if( v.getNorm() == 2 )return 1; //TestMethod
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::getSizeTest(bool print)
{	
	int oldsize = 5;
	int newsize = 14;

	try
	{
		Vector v(oldsize);

		v = 2;
	
		v.setSize(newsize); 

		if( print )
		{
			cout<<"Method getSizeTest"<<endl;
			
			cout<<" Vector=";

			v.println();			
		}
		
		if( newsize == v.getSize() )return 1; //TestMethod
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::setDataTest(bool print)
{
	try
	{
		Vector v(10);
		
		for(int i = 0; i < 10; i++) v.setData(i, 4); //TestMethod

		if( print )
		{
			cout<<"Method setDataTest"<<endl;
			
			cout<<" Vector=";

			v.println();			
		}

		for(int i = 0; i < 10; i++) if (v[i] != 4)return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::setNullTest(bool print)
{
	try
	{
		Vector v(100);

		v.setNull(); //TestMethod

		if( print )
		{
			cout<<"Method setNullTest"<<endl;
			
			cout<<" Vector=";

			v.println();			
		}

		if( v.isNull() )return 1;
		else return false;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::setSizeTest(bool print)
{
	int oldsize = 10;
	int newsize = 8;
	try
	{
		Vector v(oldsize);

		v = 2;

		v.setSize(newsize); //TestMethod

		if( print )
		{
			cout<<"Method setSizeTest"<<endl;
			
			cout<<" Vector=";

			v.println();			
		}

		if( v.getSize() == newsize)return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::setUnitTest(bool print)
{
	int size = 10;

	try
	{
		Vector v(size);

		v.setUnit(); //TestMethod

		if( print )
		{
			cout<<"Method setUnitTest"<<endl;
			
			cout<<" Vector=";

			v.println();			
		}

		if( v.isUnit() )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::MaxTest(bool print)
{
	int size = 5;

	try
	{
		Vector v(size);

		for(int i = 0; i < size; i++)v[i] = i;

		if( print )
		{
			cout<<"Method MaxTest"<<endl;
			
			cout<<" Vector=";

			v.println();

			cout<<" Max="<<v.Max()<<endl;
		}

		if( v.Max() == size - 1 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::MinTest(bool print)
{
	int size  = 5;

	try
	{
		Vector v(size);

		for(int i = 0; i < size; i++)v[i] = i;

		if( print )
		{
			cout<<"Method MinTest"<<endl;
			
			cout<<" Vector=";

			v.println();

			cout<<" Min="<<v.Min()<<endl;
		}

		if( v.Min() == 0 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::MiddleTest(bool print)
{
	int size = 4;

	try
	{
		Vector v(size);

		for(int i = 0; i < size; i++)v[i] = i+1;

		if( print )
		{
			cout<<"Method MiddleTest"<<endl;

			cout<<" Vector=";
			
			v.println();

			cout<<" Middle="<<v.Middle()<<endl;
		}

		if( v.Middle() == 2.5 )return 1;
		else return 0;		
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::MultiplyTest(bool print)
{
	int size = 4;

	try
	{
		Vector v(size);

		for(int i = 0; i < size; i++)v[i] = i+1;

		if( print )
		{
			cout<<"Method MultiplyTest"<<endl;

			cout<<" Vector=";
			
			v.println();

			cout<<" Multiply="<<v.Multiply()<<endl;
		}

		if( v.Multiply() == 24 )return 1;
		else return 0;		
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::SumTest(bool print)
{
	int size = 4;

	try
	{
		Vector v(size);

		for(int i = 0; i < size; i++)v[i] = i+1;
		
		if( print )
		{
			cout<<"Method SumTest"<<endl;

			cout<<" Vector=";
			
			v.println();

			cout<<" Sum="<<v.Sum()<<endl;
		}

		if( v.Sum() == 10 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::readTest(bool print)
{
	int size = 4;

	try
	{	
		Vector v(size);

		v = 1;

		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\read\\v001.txt");

		if( print )
		{
			cout<<"Method readTest"<<endl;

			cout<<" Vector=";
			
			v.println();			
		}

		if( v == 0 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::readTest2(bool print)
{
	int size = 4;

	try
	{	
		Vector v(size);

		v = 0;

		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\read\\v002.txt");

		if( print )
		{
			cout<<"Method readTest"<<endl;

			cout<<" Vector=";
			
			v.println();			
		}

		if( v == 1 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::readTest3(bool print)
{
	int size = 4;

	try
	{	
		Vector v1(size);
		Vector v2(size);

		v1 = 0;

		for(int i = 0; i < size; i++) v2[i] = i+1;

		v1.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\read\\v003.txt");

		if( print )
		{
			cout<<"Method readTest"<<endl;

			cout<<" Vector=";
			
			v1.println();			
		}

		if( v1 == v2 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}
//-------------------------------------------------------------------------------------------------------------
int VectorTest::writeTest(bool print)
{
	int size = 4;

	try
	{
		Vector v(size);

		v = 0;

		v.writeToFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\write\\v001.txt");

		v = 1;

		v.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\write\\v001.txt");

		if( print )
		{
			cout<<"Method writeTest"<<endl;

			cout<<" Vector=";
			
			v.println();			
		}

		if( v == 0 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::writeTest2(bool print)
{
	int size = 4;

	try
	{
		Vector v1(size);
		Vector v2(size);

		v1 = 0;
		v2 = 0;

		for(int i = 0; i < size; i++) v1[i] = i+1;

		v1.writeToFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\write\\v002.txt");

		v2.readFromFile("E:\\Labs\\Development\\Projects\\Graphics\\3D\\Aero3D\\_data\\vector\\write\\v002.txt");

		if( print )
		{
			cout<<"Method writeTest2"<<endl;

			cout<<" Vector1="; v1.println();			
			cout<<" Vector2="; v2.println();			
		}

		if( v1 == v2 )return 1;
		else return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
int VectorTest::operatorTest(bool print)
{
	int size = 4;
	try
	{
		Vector v(size);
				
		for(int i = 0; i < size; i++)v.setData(i, 0);
		
		//test operators !=, ==
		if( v != 0 )return 0;
		if( v == 1 )return 0;

		//test operator = 
		v = 1;	for(int i = 0; i < size; i++)if( v.getData(i) == 0 )return 0;

		//test operator ++
		v++; if( v != 2 )return 0;

		//test operator --
		v--; if( v != 1 )return 0;

		//test operator +, -, *, / (double value)
		v = v + 1; if( v != 2 )return 0;
		v = v - 1; if( v != 1 )return 0;
		v = v * 2; if( v != 2 )return 0;
		v = v / 2; if( v != 1 )return 0;

		//test operator +=, -=, *=, /= (double value)
		v += 1; if( v != 2 )return 0;
		v -= 1; if( v != 1 )return 0;
		v *= 2; if( v != 2 )return 0;
		v /= 2; if( v != 1 )return 0;

		//test operator +, -, * (Vector &v)
		Vector v2(v);
		
		v = v + v2; if( v != 2 )return 0;
		v = v - v2; if( v != 1 )return 0; 
		
		v = 2;	v2 = 2;

		v = v * v2; if( v != 4 )return 0;

		//test operator +=, -=, *= (Vector &v)
		v = 1;	v2 = 1;
		v += v2; if( v != 2 )return 0;
		v -= v2; if( v != 1 )return 0; 
		
		v = 2;
		v2 = 2;

		v *= v2; if( v != 4 )return 0;

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}