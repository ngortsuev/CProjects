#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include "Vector.h"
#include "SolverLibMacros.h"

#define TXT 0
#define XML 1

using namespace std;

//---------------------------------------class VectorFile------------------------------------------------------
/* abstract class VectorFile

   read/write data in Vector
*/
class DLLExport VectorFile
{
protected:
	string filename;	
public:
	VectorFile(void);
	VectorFile(const string filename);
	virtual ~VectorFile(void);
	
	string getFilename();
	void   setFilename(const string filename);
	
	virtual void read(Vector &v) = 0;
	virtual void write(Vector &v) = 0;

	//virtual void createFile();
	//virtual void deleteFile();
	//virtual int  getVectorCount();
	//virtual void readVectors(Vector **v);
};

//---------------------------------------class VectorFileFactory-----------------------------------------------
class DLLExport VectorFileFactory
{
public:
	VectorFileFactory();
	virtual ~VectorFileFactory();

	virtual VectorFile* CreateVectorFile(int type);
	virtual VectorFile* CreateVectorFile(int type, const string filename);
};

//---------------------------------------class VectorTxtFile---------------------------------------------------
class DLLExport VectorTxtFile : public VectorFile
{
public:
	VectorTxtFile();
	VectorTxtFile(const string filename);
	virtual ~VectorTxtFile();

	virtual void read(Vector &v);
	virtual void write(Vector &v);
};
