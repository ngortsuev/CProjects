#pragma once

#include "Macros.h"
#include "MathMesh.h"

class Generator
{
public:
	Generator(void);
	virtual ~Generator(void);
	virtual void generate() = 0;
};

//-------------------------------------------------------------------------------------------------------------
class MeshGenerator : public Generator
{
protected:
	MathMesh *mmesh;
public:
	MeshGenerator();
	virtual ~MeshGenerator();
	virtual void generate() = 0;
	virtual MathMesh* CreateMathMesh(int type) = 0;
};

//-------------------------------------------------------------------------------------------------------------
class UniformMeshGenerator : public MeshGenerator
{
public:
	UniformMeshGenerator();
	virtual ~UniformMeshGenerator();
	virtual void generate();
	virtual MathMesh* CreateMathMesh(int type);
};
