#include "StdAfx.h"
#include "VectorFile.h"

/**************************************************************************************************************
*																											  *
*										 abstract class VectorFile 		                    				  *	
*																											  *		
**************************************************************************************************************/
VectorFile::VectorFile(void)
{
	filename = "";
}

//-------------------------------------------------------------------------------------------------------------
VectorFile::VectorFile(const string filename)
{
	this->filename = filename;
}

//-------------------------------------------------------------------------------------------------------------
VectorFile::~VectorFile(void)
{
}

//-------------------------------------------------------------------------------------------------------------
string VectorFile::getFilename()
{
	return filename;
}

//-------------------------------------------------------------------------------------------------------------
void VectorFile::setFilename(const string filename)
{
	this->filename = filename;
}

/**************************************************************************************************************
*																											  *
*										 class VectorFileFactory			  		                    	  *	
*																											  *		
**************************************************************************************************************/
VectorFileFactory::VectorFileFactory()
{
}

//-------------------------------------------------------------------------------------------------------------
VectorFileFactory::~VectorFileFactory()
{
}

//-------------------------------------------------------------------------------------------------------------
VectorFile* VectorFileFactory::CreateVectorFile(int type)
{
	switch(type)
	{
		case TXT: return new VectorTxtFile();
		default: return new VectorTxtFile();
	}
}

//-------------------------------------------------------------------------------------------------------------
VectorFile* VectorFileFactory::CreateVectorFile(int type, const string filename)
{
	switch(type)
	{
		case TXT: return new VectorTxtFile(filename);

		default: return new VectorTxtFile(filename);
	}
}

/**************************************************************************************************************
*																											  *
*										 class VectorTxtFile	  		                    				  *	
*																											  *		
**************************************************************************************************************/
VectorTxtFile::VectorTxtFile() : VectorFile()
{
}

//-------------------------------------------------------------------------------------------------------------
VectorTxtFile::VectorTxtFile(const std::string filename) : VectorFile(filename)
{
}

//-------------------------------------------------------------------------------------------------------------
VectorTxtFile::~VectorTxtFile()
{
}

//-------------------------------------------------------------------------------------------------------------
void VectorTxtFile::read(Vector &v)
{		
	int i = 0;

	char str[255];

	memset(str, 0, 255);

	fstream file(filename.c_str(), ios::in);

	while( !file.eof() )
	{
		file.getline(str, sizeof(str), ' ');

		v[i] = atof(str);

		memset(str, 0, 255);

		i++;

		if( i == v.getSize() )break;
	}	

	file.close();
}

//-------------------------------------------------------------------------------------------------------------
void VectorTxtFile::write(Vector &v)
{	
	fstream file(filename.c_str(), ios::out);

	for(int i = 0; i < v.getSize(); i++)
	
		file<<v[i]<<' ';

	file.close();
}


