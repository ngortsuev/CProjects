#include "StdAfx.h"
#include "MatrixFile.h"

/**************************************************************************************************************
*																											  *
*										 abstract class MatrixFile 		                    				  *	
*																											  *		
**************************************************************************************************************/
//-------------------------------------------------------------------------------------------------------------
MatrixFile::MatrixFile(void)
{
	filename = "";
}

//-------------------------------------------------------------------------------------------------------------
MatrixFile::MatrixFile(const string filename)
{
	this->filename = filename;
}

//-------------------------------------------------------------------------------------------------------------
MatrixFile::~MatrixFile(void)
{
}

//-------------------------------------------------------------------------------------------------------------
string MatrixFile::getFilename()
{
	return filename;
}

//-------------------------------------------------------------------------------------------------------------
void MatrixFile::setFilename(const string filename)
{
	this->filename = filename;
}

/**************************************************************************************************************
*																											  *
*										 class MatrixFileFactory 		                    				  *	
*																											  *		
**************************************************************************************************************/
//-------------------------------------------------------------------------------------------------------------
MatrixFileFactory::MatrixFileFactory(void)
{	
}

//-------------------------------------------------------------------------------------------------------------
MatrixFileFactory::~MatrixFileFactory(void)
{
}

//-------------------------------------------------------------------------------------------------------------
MatrixFile* MatrixFileFactory::CreateMatrixFile(int type)
{
	switch(type)
	{
		case TXT: return new MatrixTxtFile();

		default:  return new MatrixTxtFile();
	}
}

//-------------------------------------------------------------------------------------------------------------
MatrixFile* MatrixFileFactory::CreateMatrixFile(int type, string filename)
{
	switch(type)
	{
		case TXT: return new MatrixTxtFile(filename);

		default:  return new MatrixTxtFile(filename);
	}
}

/**************************************************************************************************************
*																											  *
*										 class MatrixTxtFile    		                    				  *	
																											  *		
**************************************************************************************************************/
//-------------------------------------------------------------------------------------------------------------
MatrixTxtFile::MatrixTxtFile(void) : MatrixFile()
{	
}

//-------------------------------------------------------------------------------------------------------------
MatrixTxtFile::MatrixTxtFile(const string filename) : MatrixFile(filename)
{	
}

//-------------------------------------------------------------------------------------------------------------
MatrixTxtFile::~MatrixTxtFile(void)
{
}

//-------------------------------------------------------------------------------------------------------------
void MatrixTxtFile::read(Matrix *m)
{
	int i, j, k;
	char sym;
	char str[256];
	double value;

	i = 0;
	j = 0;

	memset(str, '0', 256);

	fstream file(filename.c_str(), ios::in);

	while( !file.eof() )
	{
		k = 0;

		sym = '0';

		while( sym != ' ' && sym != '\n' && !file.eof())
		{	
			sym = file.get();

			if( k < sizeof(str) )
				
				str[k] = sym;

			k++;
		}

		value = strtod(str, NULL);

		m->setCell(i, j, value);

		memset(str, '0', 256);
		
		j++;
		
		if( j == m->getColCount() ){ i++; j = 0;}
		if( i == m->getRowCount() )break;
	}		

	file.close();
}

//-------------------------------------------------------------------------------------------------------------
void MatrixTxtFile::write(Matrix *m)
{
	fstream file(filename.c_str(), ios::out);

	for(int i = 0; i < m->getRowCount(); i++)
	{
		for(int j = 0; j < m->getColCount()-1; j++)
	
			file<<m->getCell(i,j)<<' ';

		file<<m->getCell(i,m->getColCount()-1)<<'\n';
	}

	file.close();
}