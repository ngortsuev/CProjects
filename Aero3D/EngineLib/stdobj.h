#pragma once

#ifndef stdobjH
#define stdobjH

#define _USE_MATH_DEFINES

#include <string.h>
#include <cmath>
#include "macros.h"
#include "objectgl.h"

using namespace std;

namespace EngineGL
{
	namespace ObjectGL
	{
//------------------------------------------------------------------------------
class DLLExport Box : public Object
{
protected:
public:
        float length;
        float width;
        float height;
        
        Box();
        Box(string name);
        Box(string name, ColorRGB *color, Vector3 *pos);
        Box(string name, float length, float width, float height, ColorRGB *color, Vector3 *pos);

        virtual void Draw();
        virtual void PrepareDraw();
        virtual void Rotate(float degree, float x, float y, float z);
        virtual void Translate(float x, float y, float z);
        virtual void Scale(float x, float y, float z);

        virtual void setLength(float length);
        virtual void setWidth(float width);
        virtual void setHeight(float height);

        virtual void Select();
        virtual void UnSelect();
};

//------------------------------------------------------------------------------
class DLLExport Sphere : public Object
{
public:
        float radius;
        Sphere();
        Sphere(string name);
        Sphere(string name, ColorRGB *color, Vector3 *pos);
        Sphere(string name, ColorRGB *color, Vector3 *pos, float radius);

        virtual void Draw();
        virtual void PrepareDraw();

        virtual void setRadius(float radius);

        virtual void Select();
        virtual void UnSelect();
};

//------------------------------------------------------------------------------
class DLLExport Text3D : public Object
{
protected:
        string textStr;
        float  deviation;
        float  extrusion;
        int    format;
public:
        Text3D();
        Text3D(string name, ColorRGB *color, Vector3 *pos);
        Text3D(string textStr, string name, ColorRGB *color, Vector3 *pos);
        virtual ~Text3D();
        virtual void Draw();
        virtual void Draw(string textStr);
        virtual void Draw(string textStr, Vector3 *pos);
        virtual void PrepareDraw();

        virtual void setText(string text);
        virtual void setDeviation(float deviation);
        virtual void setExtrusion(float extrusion);
        virtual void setFormat(int format);
};

//------------------------------------------------------------------------------
class DLLExport Mesh : public Object
{
public:
        Mesh();
        virtual ~Mesh();
        Vertex& getVertex(int index);
        GLPolygon& getPolygon(int index);
        Mapcoord& getMapcoord(int index);
        //virtual void Draw();
};
	};
};
#endif
