#include "StdAfx.h"
#include "light.h"
using namespace EngineGL;
using namespace ObjectGL;
using namespace MathGL;
//------------------------------------------------------------------------------
Light::Light()
{
        lightON = false;
        lightNumber = 0;
        lightPos  = 0;
        targetPos = 0;

        colorLight  = ColorRGB(1,1,0);
        colorTarget = ColorRGB(1,1,0);
        colorLink   = ColorRGB(0,0,1);
        colorFrame  = ColorRGB(0,0,1);
        lightObj = gluNewQuadric();
        targetObj = gluNewQuadric();

        gluQuadricDrawStyle(lightObj, GLU_LINE);
        gluQuadricDrawStyle(targetObj, GLU_LINE);

        glGetFloatv(GL_SPOT_EXPONENT, &spot_exp);
        glGetFloatv(GL_SPOT_CUTOFF, &spot_cutoff);

        glGetLightfv(GL_LIGHT0 + lightNumber, GL_CONSTANT_ATTENUATION, &const_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_LINEAR_ATTENUATION, &linear_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_QUADRATIC_ATTENUATION, &quad_atten);        

        visible = true;
}

//------------------------------------------------------------------------------
Light::Light(int Number)
{
        lightON = false;
        lightNumber = Number;
        lightPos  = 0;
        targetPos = 0;

        colorLight  = ColorRGB(1,1,0);
        colorTarget = ColorRGB(1,1,0);
        colorLink   = ColorRGB(0,0,1);
        colorFrame  = ColorRGB(0,0,1);
        lightObj = gluNewQuadric();
        targetObj = gluNewQuadric();

        gluQuadricDrawStyle(lightObj, GLU_LINE);
        gluQuadricDrawStyle(targetObj, GLU_LINE);

        glGetFloatv(GL_SPOT_EXPONENT, &spot_exp);
        glGetFloatv(GL_SPOT_CUTOFF, &spot_cutoff);

        glGetLightfv(GL_LIGHT0 + lightNumber, GL_CONSTANT_ATTENUATION, &const_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_LINEAR_ATTENUATION, &linear_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_QUADRATIC_ATTENUATION, &quad_atten);
        
        visible = true;
}

//------------------------------------------------------------------------------
Light::Light(int Number, Vector4 *LightPos, float LightRadius, float LightHeight,
                         Vector3 *TargetPos, float TargetSize, float FrameRadius)
{
        lightON = false;
        lightNumber = Number;
        setLightPos(*LightPos);
        setTargetPos(*TargetPos);

        lightRadius = LightRadius;
        lightHeight = LightHeight;
        targetSize  = TargetSize;
        frameRadius = FrameRadius;

        colorLight  = ColorRGB(1,1,0);
        colorTarget = ColorRGB(1,1,0);
        colorLink   = ColorRGB(0,0,1);
        colorFrame  = ColorRGB(0,0,1);
        lightObj = gluNewQuadric();
        targetObj = gluNewQuadric();

        gluQuadricDrawStyle(lightObj, GLU_LINE);
        gluQuadricDrawStyle(targetObj, GLU_LINE);

        glGetFloatv(GL_SPOT_EXPONENT, &spot_exp);
        glGetFloatv(GL_SPOT_CUTOFF, &spot_cutoff);        

        glGetLightfv(GL_LIGHT0 + lightNumber, GL_CONSTANT_ATTENUATION, &const_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_LINEAR_ATTENUATION, &linear_atten);
        glGetLightfv(GL_LIGHT0 + lightNumber, GL_QUADRATIC_ATTENUATION, &quad_atten);
                
        visible = true;        
}

//------------------------------------------------------------------------------
Light::~Light()
{
        gluDeleteQuadric(lightObj);
}

//------------------------------------------------------------------------------
void Light::lightOn(bool on)
{
        lightON = on;

        if( lightON )

                glEnable(GL_LIGHT0 + lightNumber);

        else glDisable(GL_LIGHT0 + lightNumber);
}

//------------------------------------------------------------------------------
void Light::setNumber(int number)
{
        lightNumber = number;
}

//------------------------------------------------------------------------------
void Light::setLightPos(Vector4 &v)
{
        lightPos = v;

        glLightfv(GL_LIGHT0 + lightNumber, GL_POSITION, lightPos);
}

//------------------------------------------------------------------------------
void Light::setTargetPos(Vector3 &v)
{
        targetPos = v;

        glLightfv(GL_LIGHT0 + lightNumber, GL_SPOT_DIRECTION, targetPos);        
}

//------------------------------------------------------------------------------
void Light::setLightPos(float x, float y, float z, float w)
{
        lightPos = Vector4(x,y,z,w);

        glLightfv(GL_LIGHT0 + lightNumber, GL_POSITION, lightPos);
}

//------------------------------------------------------------------------------
void Light::setTargetPos(float x, float y, float z)
{
        targetPos = Vector3(x,y,z);

        glLightfv(GL_LIGHT0 + lightNumber, GL_SPOT_DIRECTION, targetPos);
}

//------------------------------------------------------------------------------
void Light::setLightRadius(float radius)
{
        lightRadius = radius;
}

//------------------------------------------------------------------------------
void Light::setLightHeight(float height)
{
        lightHeight = height;
}

//------------------------------------------------------------------------------
void Light::setTargetSize(float size)
{
        targetSize = size;
}

//------------------------------------------------------------------------------
void Light::setFrameRadius(float radius)
{
        frameRadius = radius;
}

//------------------------------------------------------------------------------
void Light::setColor(int type, ColorRGB &color)
{
        switch(type)
        {
                case LIGHT  : colorLight  = color; break;
                case TARGET : colorTarget = color; break;
                case LINK   : colorLink   = color; break;
                case FRAME  : colorFrame  = color; break;

                case LIGHT_TARGET: colorLight  = color;
                                   colorTarget  = color;
                                   break;
        }
}

//------------------------------------------------------------------------------
void Light::setColor(int type, float r, float g, float b)
{
        switch(type)
        {
                case LIGHT  : colorLight  = ColorRGB(r, g, b); break;
                case TARGET : colorTarget = ColorRGB(r, g, b); break;
                case LINK   : colorLink   = ColorRGB(r, g, b); break;
                case FRAME  : colorFrame  = ColorRGB(r, g, b); break;

                case LIGHT_TARGET: colorLight  = ColorRGB(r, g, b);
                                   colorTarget  = ColorRGB(r, g, b);
                                   break;     
        }
}

//------------------------------------------------------------------------------
void Light::setSpotExponent(float value)
{
        spot_exp = value;

        glLightf(GL_LIGHT0 + lightNumber, GL_SPOT_EXPONENT, value);
}

//------------------------------------------------------------------------------
void Light::setSpotCutoff(float value)
{
        spot_cutoff = value;
        
        glLightf(GL_LIGHT0 + lightNumber, GL_SPOT_CUTOFF, value);
}

//------------------------------------------------------------------------------
void Light::setConstAttenuation(float value)
{
        const_atten = value;

        glLightf(GL_LIGHT0 + lightNumber, GL_CONSTANT_ATTENUATION, value);
}

//------------------------------------------------------------------------------
void Light::setLinearAttenuation(float value)
{
        linear_atten = value;

        glLightf(GL_LIGHT0 + lightNumber, GL_LINEAR_ATTENUATION, value);
}

//------------------------------------------------------------------------------
void Light::setQuadAttenuation(float value)
{
        quad_atten = value;
        
        glLightf(GL_LIGHT0 + lightNumber, GL_QUADRATIC_ATTENUATION, value);
}

//------------------------------------------------------------------------------
void Light::setAmbient(float a1, float a2, float a3, float a4)
{
        ambient[0] = a1;
        ambient[1] = a2;
        ambient[2] = a3;
        ambient[3] = a4;

        glLightfv(GL_LIGHT0 + lightNumber, GL_AMBIENT, ambient);
}

//------------------------------------------------------------------------------
void Light::setDiffuse(float d1, float d2, float d3, float d4)
{
        diffuse[0] = d1;
        diffuse[1] = d2;
        diffuse[2] = d3;
        diffuse[3] = d4;

        glLightfv(GL_LIGHT0 + lightNumber, GL_DIFFUSE, diffuse);
}

//------------------------------------------------------------------------------
void Light::setSpecular(float s1, float s2, float s3, float s4)
{
        specular[0] = s1;
        specular[1] = s2;
        specular[2] = s3;
        specular[3] = s4;

        glLightfv(GL_LIGHT0 + lightNumber, GL_SPECULAR, specular);        
}

//------------------------------------------------------------------------------
void Light::setVisible(bool visible)
{
        this->visible = visible;
}

//------------------------------------------------------------------------------
ColorRGB& Light::getColor(int type)
{
        switch(type)
        {
                case LIGHT  : return colorLight;
                case TARGET : return colorTarget;
                case LINK   : return colorLink;
                case FRAME  : return colorFrame;

                default: return colorLight;
        }
}

//------------------------------------------------------------------------------
void Light::Rotate(float degree, int type)
{
        if( type == 1 )angle.x = degree;
        if( type == 2 )angle.y = degree;
        if( type == 3 )angle.z = degree;
}

//------------------------------------------------------------------------------
void Light::Draw()
{
        if( !visible )return;
        
        glPushMatrix();
          glPushAttrib(GL_POLYGON_BIT);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            DrawLight();
            DrawTarget();
            DrawLink();
            DrawFrame();
          glPopAttrib();
        glPopMatrix();
}

//------------------------------------------------------------------------------
void Light::DrawLight()
{
        glPushMatrix();
          glPushAttrib(GL_CURRENT_BIT);
            glColor3f(colorLight.red, colorLight.green, colorLight.blue);

            glTranslatef(lightPos.x, lightPos.y, lightPos.z);

            gluCylinder(lightObj, lightRadius, 0, lightHeight, 15, 15);
          glPopAttrib();
        glPopMatrix();
}

//------------------------------------------------------------------------------
void Light::DrawTarget()
{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glPushMatrix();
          glPushAttrib(GL_CURRENT_BIT);
            glColor3f(colorTarget.red, colorTarget.green, colorTarget.blue);

            glTranslatef(targetPos.x, targetPos.y, targetPos.z);

            gluCylinder(targetObj, targetSize, targetSize, targetSize, 4, 1);
          glPopAttrib();
        glPopMatrix();
}

//------------------------------------------------------------------------------
void Light::DrawLink()
{
        glPushAttrib(GL_CURRENT_BIT);
        glColor3f(colorLink.red, colorLink.green, colorLink.blue);
        glBegin(GL_LINES);
          glVertex3f(lightPos.x,  lightPos.y,  lightPos.z + lightHeight);
          glVertex3f(targetPos.x, targetPos.y, targetPos.z);
        glEnd();
        glPopAttrib();
}

//------------------------------------------------------------------------------
void Light::DrawFrame()
{
        float x1,y1,i = -M_PI;
        glPushAttrib(GL_CURRENT_BIT);

        glColor3f(colorFrame.red, colorFrame.green, colorFrame.blue);
        //draw circle
        glBegin(GL_LINE_STRIP);
          while(i <= M_PI + 0.1 )
          {
                x1 = frameRadius * cos(i);
                y1 = frameRadius * sin(i);

                glVertex3f( targetPos.x + x1 ,  targetPos.y + y1, targetPos.z);

                i = i + 0.1;
          }
        glEnd();

        glBegin(GL_LINES);

          glVertex3f(lightPos.x,                lightPos.y,  lightPos.z + lightHeight);
          glVertex3f(targetPos.x + frameRadius, targetPos.y, targetPos.z);

          glVertex3f(lightPos.x,                lightPos.y,  lightPos.z + lightHeight);
          glVertex3f(targetPos.x - frameRadius, targetPos.y, targetPos.z);

          glVertex3f(lightPos.x,  lightPos.y,                lightPos.z + lightHeight);
          glVertex3f(targetPos.x, targetPos.y + frameRadius, targetPos.z);

          glVertex3f(lightPos.x,  lightPos.y,                lightPos.z + lightHeight);
          glVertex3f(targetPos.x, targetPos.y - frameRadius, targetPos.z);
        glEnd();

        glPopAttrib();

}
