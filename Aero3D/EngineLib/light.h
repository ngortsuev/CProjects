#pragma once

#ifndef lightH
#define lightH

#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <cmath>
#include "macros.h"
#include "color.h"
#include "vector.h"


using namespace EngineGL::MathGL;

namespace EngineGL
{
	namespace ObjectGL
	{
#define LIGHT  1
#define TARGET 2
#define LINK   3
#define FRAME  4
#define LIGHT_TARGET 5
//------------------------------------------------------------------------------
class DLLExport Light
{
protected:
        GLUquadricObj *lightObj;
        GLUquadricObj *targetObj;
        bool  lightON;
        Vector4 lightPos;
        Vector3 targetPos;
        Vector3 angle;
        float lightRadius;
        float lightHeight;
        float targetSize;
        float frameRadius;

        int   lightNumber;

        float spot_exp;
        float spot_cutoff;
        float const_atten;
        float linear_atten;
        float quad_atten;
        
        float ambient[4];
        float diffuse[4];
        float specular[4];

        ColorRGB colorLight;
        ColorRGB colorTarget;
        ColorRGB colorLink;
        ColorRGB colorFrame;

        bool visible;
public:
        Light();
        Light(int Number);
        Light(int Number, Vector4 *LightPos,  float LightRadius, float LightHeight,
                          Vector3 *TargetPos, float TargetSize,  float FrameRadius);
        virtual ~Light();
        virtual void lightOn(bool on);

        virtual void setNumber(int number);

        //---------------------------set function-------------------------------
        //position
        virtual void setLightPos(Vector4 &v);
        virtual void setTargetPos(Vector3 &v);
        virtual void setLightPos(float x, float y, float z, float w);
        virtual void setTargetPos(float x, float y, float z);

        //size
        virtual void setLightRadius(float radius);
        virtual void setLightHeight(float height);
        virtual void setTargetSize(float size);
        virtual void setFrameRadius(float radius);

        //color
        virtual void setColor(int type, ColorRGB &color);
        virtual void setColor(int type, float r, float g, float b);

        //properties
        virtual void setSpotExponent(float value);
        virtual void setSpotCutoff(float value);
        virtual void setConstAttenuation(float value);
        virtual void setLinearAttenuation(float value);
        virtual void setQuadAttenuation(float value);

        virtual void setAmbient(float a1, float a2, float a3, float a4);
        virtual void setDiffuse(float d1, float d2, float d3, float d4);
        virtual void setSpecular(float s1, float s2, float s3, float s4);

        virtual void setVisible(bool visible);      //show or hide light object

        //---------------------------get function-------------------------------
        virtual bool getLightOn(){ return lightON; }
        virtual int  getNumber(){  return lightNumber; }
        virtual bool getVisible(){ return visible; }
        virtual Vector4 getLightPos(){  return lightPos; }
        virtual Vector3 getTargetPos(){ return targetPos; }
        virtual float getSpotExponent(){ return spot_exp; }
        virtual float getSpotCutoff(){ return spot_cutoff; }
        virtual float getConstAttenuation(){ return const_atten; }
        virtual float getLinearAttenuation(){ return linear_atten; }
        virtual float getQuadAttenuation(){ return quad_atten; }

        virtual ColorRGB& getColor(int type);

        virtual void Rotate(float degree, int type);

        //---------------------------draw function------------------------------        
        virtual void DrawLight();
        virtual void DrawTarget();
        virtual void DrawLink();
        virtual void DrawFrame();
        virtual void Draw();
};
};
};
#endif
