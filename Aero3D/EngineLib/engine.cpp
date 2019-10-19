#include "StdAfx.h"
#include "engine.h"

using namespace EngineGL;
using namespace ObjectGL;
using namespace MathGL;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Context                                     */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Context::Context(HANDLE handle)
{
        this->handle = handle;

        hdc = (HDC)GetDC((HWND)handle);

        setPixelFormat();

        hrc = wglCreateContext(hdc);
}

//------------------------------------------------------------------------------
Context::~Context()
{
        wglDeleteContext(hrc);

        ReleaseDC((HWND)handle, hdc);
}

//------------------------------------------------------------------------------
void Context::setPixelFormat()
{
     PIXELFORMATDESCRIPTOR pfd;
     int pixelFormat;

     memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));

     pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
     pfd.nVersion = 1;
     pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
     pfd.iPixelType = PFD_TYPE_RGBA;
     pfd.cColorBits = 64;
     pfd.cAlphaBits = 64;
     pfd.cAccumBits = 64;
     pfd.cDepthBits = 64;
     pfd.cStencilBits = 64;
     pfd.iLayerType = PFD_MAIN_PLANE;

     pixelFormat = ChoosePixelFormat(hdc,&pfd);

     SetPixelFormat(hdc,pixelFormat,&pfd);
}

//------------------------------------------------------------------------------
void Context::setViewport(int Width, int Height)
{
        glViewport(0,0,Width,Height);
}

//------------------------------------------------------------------------------
void Context::setProjection(Matrix4 *matrix)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glLoadMatrixd((GLdouble*)(*matrix));

        glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
void Context::setOrtho(double left, double right, double bottom, double top, double znear, double zfar)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(left, right, bottom, top, znear, zfar);

        glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
void Context::setFrustum(double left, double right, double bottom, double top, double znear, double zfar)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glFrustum(left, right, bottom, top, znear, zfar);

        glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
void Context::setPerspective(double angley, double aspect, double znear, double zfar)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(angley, aspect, znear, zfar);

        glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
void Context::setFont(LOGFONT &font)
{
        //set font
        this->font.lfHeight = font.lfHeight;
        this->font.lfWeight = font.lfWeight;
        this->font.lfCharSet = font.lfCharSet;
        this->font.lfOutPrecision = font.lfOutPrecision;
        this->font.lfClipPrecision = font.lfClipPrecision;
        this->font.lfQuality = font.lfQuality;
        this->font.lfPitchAndFamily = font.lfPitchAndFamily;
        strcpy((char*)this->font.lfFaceName, (char*)font.lfFaceName);

        //---create font and set for window
        HFONT hNewFont = CreateFontIndirect(&font);
        HFONT hOldFont = (HFONT)SelectObject(hdc, hNewFont);

        DeleteObject(hOldFont);
        DeleteObject(hNewFont);

        wglUseFontOutlines(hdc, 0, 255, 100, 0.0, 0.5, WGL_FONT_POLYGONS, NULL);
}

//------------------------------------------------------------------------------
HANDLE Context::getHandle()
{
        return handle;
}

//------------------------------------------------------------------------------
HDC Context::getDC()
{
        return hdc;
}

//------------------------------------------------------------------------------
void Context::Select()
{
        wglMakeCurrent(NULL, NULL);
        
        wglMakeCurrent(hdc, hrc);
}

//------------------------------------------------------------------------------
void Context::SwapBuffers()
{
        ::SwapBuffers(hdc);
}

//------------------------------------------------------------------------------
void Context::Invalidate()
{
        InvalidateRect((HWND)handle, NULL, false);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                 OpenGL                                     */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Context* OpenGL::SelectedContext = 0;
Scene* OpenGL::SelectedScene = 0;

OpenGL::OpenGL()
{
        contexts = new vector<Context*>;

        scenes = new vector<Scene*>;
}

//------------------------------------------------------------------------------
OpenGL::~OpenGL()
{
        wglMakeCurrent(NULL,NULL);
		
		contexts->erase(contexts->begin(), contexts->end());

		scenes->erase(scenes->begin(), scenes->end());

		delete contexts;
        delete scenes;
}

//------------------------------------------------------------------------------
int OpenGL::CreateContext(HANDLE Handle)
{
	contexts->push_back(new Context(Handle));

	return 1;
}

//------------------------------------------------------------------------------
int OpenGL::CreateScene()
{
	scenes->push_back(new Scene());
	
	return 1;
}

//------------------------------------------------------------------------------
Context* OpenGL::SelectContext(int index)
{
	SelectedContext = (Context*)contexts->at(index);
	
	SelectedContext->Select();
	
	return SelectedContext;
}

//------------------------------------------------------------------------------
Scene* OpenGL::SelectScene(int index)
{
	SelectedScene = (Scene*)scenes->at(index);
	
	return SelectedScene;
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                              Scene                                         */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Scene::Scene() : Object()
{
        objects = new vector<Object*>;

        draw_axis = false;
        draw_grid = false;

        axis = new Axis();
        grid = new Grid();
}

//------------------------------------------------------------------------------
Scene::Scene(string name) : Object(name)
{
        objects = new vector<Object*>;
}

//------------------------------------------------------------------------------
Scene::~Scene()
{
        delete axis;
        delete grid;

		objects->erase(objects->begin(), objects->end());

        delete objects;
}

//------------------------------------------------------------------------------
void Scene::Clear()
{
        glClearColor(0.75f, 0.75f, 0.75f, 1.05f);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

//------------------------------------------------------------------------------
void Scene::Draw()
{
        unsigned char lighting;

        glGetBooleanv(GL_LIGHTING, &lighting);

        if( lighting )glDisable(GL_LIGHTING);

          if( draw_axis )axis->Draw();

          if( draw_grid )grid->Draw();

        if( lighting )glEnable(GL_LIGHTING);

        for(int i = 0; i < objects->size(); i++)
        {
			Object *object = objects->at(i);
			
			object->Draw();
        }
        
}

//------------------------------------------------------------------------------
void Scene::AddObject(Object *object)
{
	objects->push_back(object);
}

//------------------------------------------------------------------------------
void Scene::DeleteObject(int index)
{	
        //objects->remove(index);
}

//------------------------------------------------------------------------------
int Scene::FindObject(Object *object)
{		
		for(int i = 0; i < objects->size(); i++)
        {
			Object *obj = objects->at(i);
			
			if( obj == object )return i;
        }
        return -1;
}

//------------------------------------------------------------------------------
Object* Scene::SelectObject(int x, int y)
{
        if( objects->size() == 0 )return NULL;

        Object *obj;
        
        Object *obj_sel = NULL;

        for(int i = 0; i < objects->size(); i++)
        {
			obj = objects->at(i);
			
			if( obj->ContainPoint(x,y) )
            {
                if( obj->pos.z > obj_sel->pos.z )obj_sel = obj;
            }
        }

        return obj_sel;
}

//------------------------------------------------------------------------------
void Scene::Rotate(float degree, float x, float y, float z)
{
        glRotatef(degree, x, y, z);
}

//------------------------------------------------------------------------------
void Scene::Translate(float x, float y, float z)
{
        glTranslatef(x, y, z);
}

//------------------------------------------------------------------------------
void Scene::Scale(float x, float y, float z)
{
        glScalef(x, y, z);
}

//------------------------------------------------------------------------------
int Scene::getCount()
{
        return objects->size();
}

//------------------------------------------------------------------------------
Object* Scene::getObject(int i)
{
        return objects->at(i);
}

//------------------------------------------------------------------------------
void Scene::setAxis(bool draw)
{
        draw_axis = draw;
}

//------------------------------------------------------------------------------
void Scene::setGrid(bool draw)
{
        draw_grid = draw;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Fog                                         */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Fog::Fog()
{
        mode = GL_EXP;
}

//------------------------------------------------------------------------------
Fog::Fog(float mode, float density, float start, float end, ColorRGB *color)
{
        this->mode    = mode;
        this->density = density;
        this->start   = start;
        this->end     = end;
        this->color   = *color;
}

//------------------------------------------------------------------------------
Fog::~Fog()
{
}

//------------------------------------------------------------------------------
void Fog::fogOn(bool on)
{
        if( on )

             glEnable(GL_FOG);

        else glDisable(GL_FOG);
}

//------------------------------------------------------------------------------
void Fog::setMode(float mode)
{
        this->mode = mode;

        glFogf(GL_FOG_MODE, mode);
}

//------------------------------------------------------------------------------
void Fog::setDensity(float density)
{
        this->density = density;

        glFogf(GL_FOG_DENSITY, density);
}

//------------------------------------------------------------------------------
void Fog::setStart(float start)
{
        this->start = start;

        glFogf(GL_FOG_START, start);
}

//------------------------------------------------------------------------------
void Fog::setEnd(float end)
{
        this->end = end;

        glFogf(GL_FOG_END, end);
}

//------------------------------------------------------------------------------
void Fog::setColor(ColorRGB *color)
{
        this->color = *color;

        glFogfv(GL_FOG_COLOR, (float*)this->color);
}

//------------------------------------------------------------------------------
bool Fog::getFogOn()
{
        unsigned char fog_on;

        glGetBooleanv(GL_FOG, &fog_on);

        return fog_on;
}

//------------------------------------------------------------------------------
float Fog::getMode()
{
        glGetFloatv(GL_FOG_MODE, &mode);

        return mode;
}

//------------------------------------------------------------------------------
float Fog::getDensity()
{
        glGetFloatv(GL_FOG_DENSITY, &density);

        return density;
}

//------------------------------------------------------------------------------
float Fog::getStart()
{
        glGetFloatv(GL_FOG_START, &start);

        return start;
}

//------------------------------------------------------------------------------
float Fog::getEnd()
{
        glGetFloatv(GL_FOG_END, &end);

        return end;
}

//------------------------------------------------------------------------------
ColorRGB& Fog::getColor()
{
        float fog_color[4];

        fog_color[0] = 0;
        fog_color[1] = 0;
        fog_color[2] = 0;
        fog_color[3] = 0;

        glGetFloatv(GL_FOG_COLOR, fog_color);

        color.red   = fog_color[0];
        color.green = fog_color[1];
        color.blue  = fog_color[2];
        color.alpha = fog_color[3];

        return color;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Blend                                       */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Blend::Blend()
{
        sfactor = 0;
        dfactor = 0;
}

//------------------------------------------------------------------------------
Blend::Blend(GLenum sfactor, GLenum dfactor)
{
        this->sfactor = sfactor;
        this->dfactor = dfactor;

        glBlendFunc(sfactor, dfactor);
}

//------------------------------------------------------------------------------
Blend::~Blend()
{
}

//------------------------------------------------------------------------------
void Blend::blendOn(bool on)
{
        if( on )

                glEnable(GL_BLEND);

        else glDisable(GL_BLEND);
}

//------------------------------------------------------------------------------
void Blend::setBlend(GLenum sfactor, GLenum dfactor)
{
        this->sfactor = sfactor;
        this->dfactor = dfactor;

        glBlendFunc(sfactor, dfactor);
}

//------------------------------------------------------------------------------
bool Blend::getBlendOn()
{
        unsigned char blend_on;

        glGetBooleanv(GL_BLEND, &blend_on);

        return blend_on;
}

//------------------------------------------------------------------------------
GLenum Blend::getBlendSrc()
{
        int src;

        glGetIntegerv(GL_BLEND_SRC, &src);

        return src;
}

//------------------------------------------------------------------------------
GLenum Blend::getBlendDst()
{
        int dst;

        glGetIntegerv(GL_BLEND_DST, &dst);

        return dst;
}
