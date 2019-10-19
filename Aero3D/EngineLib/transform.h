#pragma once

#ifndef transformH
#define transformH

#include "Macros.h"
#include "color.h"
#include "vector.h"
#include "axis.h"

using namespace EngineGL::ObjectGL;
using namespace EngineGL::MathGL;

namespace EngineGL
{
	namespace TransformGL
	{
//--------------------------------SCENERotate-----------------------------------
class DLLExport SCENERotate
{
};

//--------------------------------SELObject-------------------------------------
class DLLExport SELObject
{
protected:
        float length;
        float width;
        float height;
        float size;
        Vector3 pos;
        Axis *axis;

        virtual void DrawAngle(Vector3 &pos);
public:
        SELObject(float x, float y, float z);
        SELObject(float x, float y, float z, float length, float width, float height, float size);
        SELObject(Vector3 *pos, float length, float width, float height, float size);
        SELObject(Vector3 *pos, Vector3 *param, float size);
        virtual ~SELObject();
        virtual void Draw();

        virtual void setLength(float length);
        virtual void setWidth(float width);
        virtual void setHeight(float height);
};

//--------------------------------ROTObject-------------------------------------
class DLLExport ROTObject
{
public:
        //ROTObject(float x, float y, float z);
        //virtual ~ROTObject();
        //virtual void Draw();

        //virtual void setRadius(float radius);
};

//--------------------------------SCALEObject-----------------------------------
class DLLExport SCALEObject
{
};

	}; //namespace TransformGL

}; //namespace EngineGL
#endif
