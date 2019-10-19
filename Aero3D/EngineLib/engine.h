#pragma once

#ifndef engineH
#define engineH
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "macros.h"
#include "color.h"
#include "vector.h"
#include "matrix.h"
#include "axis.h"
#include "grid.h"
#include "objectgl.h"
#define id_timer 0

using namespace std;

namespace EngineGL
{
	namespace ObjectGL
	{
class Scene;
//--------------------------------Context---------------------------------------
class DLLExport Context
{
protected:
        HANDLE handle;
        HDC hdc;
        HGLRC hrc;
        LOGFONT font;
public:
        Context(HANDLE handle);

        virtual ~Context();
        virtual void setPixelFormat();
        virtual void setViewport(int Width,int Height);
        virtual void setProjection(Matrix4 *matrix);
        virtual void setOrtho(double left, double right, double bottom, double top, double znear, double zfar);
        virtual void setFrustum(double left, double right, double bottom, double top, double znear, double zfar);
        virtual void setPerspective(double angley, double aspect, double znear, double zfar);
        virtual void setFont(LOGFONT &font);

        virtual HANDLE getHandle();
        virtual HDC    getDC();

        virtual void Select();
        virtual void SwapBuffers();
        virtual void Invalidate();
};

//--------------------------------OpenGL----------------------------------------
class DLLExport OpenGL
{
protected:
        vector<Context*>   *contexts;
        vector<Scene*>   *scenes;
public:
        static Context *SelectedContext;
        static Scene   *SelectedScene;
        OpenGL();
        virtual ~OpenGL();
        int  CreateContext(HANDLE Handle);
        int  CreateScene();

        Context* SelectContext(int index);
        Scene*   SelectScene(int index);

        static Context* getSelContext(){ return SelectedContext; };
        static Scene* getSelScene(){ return SelectedScene; };
};

//--------------------------------Scene-----------------------------------------
class DLLExport Scene : public Object
{
protected:
        vector<Object*> *objects;
        bool draw_axis;
        bool draw_grid;
public:
        Axis *axis;
        Grid *grid;
        
        Scene();
        Scene(string name);
        virtual ~Scene();

        virtual void Clear();
        virtual void Draw();

        virtual void AddObject(Object *object);
        virtual void DeleteObject(int index);
        virtual int  FindObject(Object *object);
        virtual Object* SelectObject(int x, int y);

        virtual void Rotate(float degree, float x, float y, float z);
        virtual void Translate(float x, float y, float z);
        virtual void Scale(float x, float y, float z);

        int getCount();
        Object* getObject(int i);

        //axis & grid in scene
        void setAxis(bool draw);
        void setGrid(bool draw);
};

//--------------------------------Fog-------------------------------------------
class DLLExport Fog
{
protected:
        float mode;
        float density;
        float start;
        float end;
        ColorRGB color;
public:
        Fog();
        Fog(float mode, float density, float start, float end, ColorRGB *color);
        virtual ~Fog();
        virtual void fogOn(bool on);
        virtual void setMode(float mode);
        virtual void setDensity(float density);
        virtual void setStart(float start);
        virtual void setEnd(float end);
        virtual void setColor(ColorRGB *color);

        virtual bool getFogOn();
        virtual float getMode();
        virtual float getDensity();
        virtual float getStart();
        virtual float getEnd();
        virtual ColorRGB& getColor();
};

//------------------------------------------------------------------------------
class DLLExport Blend
{
protected:
        GLenum sfactor;
        GLenum dfactor;
public:
        Blend();
        Blend(GLenum sfactor, GLenum dfactor);
        virtual ~Blend();
        virtual void blendOn(bool on);
        virtual void setBlend(GLenum sfactor, GLenum dfactor);

        virtual bool getBlendOn();
        virtual GLenum getBlendSrc();
        virtual GLenum getBlendDst();
};
};
};
#endif
