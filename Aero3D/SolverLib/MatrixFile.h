#pragma once

#include <fstream>
#include <string>
//#include <cmath>
#include <cstdlib>
#include "Matrix.h"
#include "SolverLibMacros.h"

#define TXT 0
#define XML 1

using namespace std;

//---------------------------------------class MatrixFile------------------------------------------------------
class DLLExport MatrixFile
{
protected:
	string filename;
public:
	MatrixFile(void);
	MatrixFile(const string filename);
	virtual ~MatrixFile(void);

	string getFilename();
	void setFilename(const string filename);

	virtual void read(Matrix *m) = 0;
	virtual void write(Matrix *m) = 0;
};

//---------------------------------------class MatrixFileFactory-----------------------------------------------
class DLLExport MatrixFileFactory
{
public:
	MatrixFileFactory(void);
	virtual ~MatrixFileFactory(void);
	virtual MatrixFile* CreateMatrixFile(int type);
	virtual MatrixFile* CreateMatrixFile(int type, const string filename);
};

//---------------------------------------class MatrixTxtFile---------------------------------------------------
class DLLExport MatrixTxtFile : public MatrixFile
{
public:
	MatrixTxtFile(void);
	MatrixTxtFile(const string filename);
	virtual ~MatrixTxtFile(void);

	virtual void read(Matrix *m);
	virtual void write(Matrix *m);
};
