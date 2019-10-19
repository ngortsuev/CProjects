#pragma once

#ifndef axisH
#define axisH

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "macros.h"
#include "color.h"
#include "vector.h"

using namespace EngineGL::MathGL;

namespace EngineGL
{
	namespace ObjectGL
	{
#define LABEL2D 1
#define LABEL3D 2
#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 4

//------------------------------------------------------------------------------
class DLLExport Axis
{
protected:
        Vector3 length;         //length
        Vector3 radius;         //radius disk
        Vector3 height;         //height conus
        float scaleText;
        float angleText;

        VColorXYZ color;
        Vector3 position;
        Vector3 draw_type;
        int     label_type;

        bool draw_cone;
        bool draw_label;

        GLUquadricObj *quadric;
public:
        Axis();
        Axis(float length, float radius, float height, float scale, float angle, Vector3 *position);
        Axis(const Axis &axis);
        virtual ~Axis();
        virtual void setPosition(Vector3 *v);
        virtual void setPosition(float x, float y, float z);

        virtual void setLength(float length);
        virtual void setLength(Vector3 *length);

        virtual void setRadius(float radius);
        virtual void setRadius(Vector3 *radius);

        virtual void setHeight(float height);
        virtual void setHeight(Vector3 *height);

        virtual void setColor(int type, ColorRGB &color);
        virtual void setColor(int type, float red, float green, float blue);

        virtual void setScale(float scale);
        virtual void setAngle(float angle);
        virtual void setLabelType(int type);
        
        virtual void setDrawType(Vector3 *draw_type);
        virtual void setDrawType(bool x, bool y, bool z);

        virtual void setCone(bool draw);
        virtual void setLabel(bool draw);
        
        virtual void setProperties(float length, float radius, float height, float scale, float angle, Vector3 *position);

        virtual Vector3& getLength();
        virtual Vector3& getRadius();
        virtual Vector3& getHeight();
        virtual float getScale();
        virtual float getAngle();
        virtual int   getLabelType();

        virtual ColorRGB& getColor(int type);
        virtual Vector3& getPosition();
        
        virtual void DrawLine();
        virtual void DrawCone();
        virtual void DrawLabel();
        virtual void Draw();
};
	};
};
#endif