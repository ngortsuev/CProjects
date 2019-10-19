#include "StdAfx.h"
#include "Generator.h"

Generator::Generator(void)
{
}

Generator::~Generator(void)
{
}

//-------------------------------------------------------------------------------------------------------------
MeshGenerator::MeshGenerator(void)
{
}

MeshGenerator::~MeshGenerator(void)
{
}

//-------------------------------------------------------------------------------------------------------------
UniformMeshGenerator::UniformMeshGenerator(void)
{
}

UniformMeshGenerator::~UniformMeshGenerator(void)
{
}

void UniformMeshGenerator::generate()
{
}

MathMesh* UniformMeshGenerator::CreateMathMesh(int type)
{
	switch(type)
	{
		case 0: mmesh = new MathMesh(); generate(); break;		
	}

	return mmesh;
}