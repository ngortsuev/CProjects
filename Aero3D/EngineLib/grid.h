#pragma once

#ifndef gridH
#define gridH
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "macros.h"
#include "color.h"
#include "vector.h"
#include "axis.h"

namespace EngineGL
{
	namespace ObjectGL
	{
#define GRID_XY 1
#define GRID_XZ 2
#define GRID_YZ 4

#define GRID_XY_XZ 3
#define GRID XY_YZ 5
#define GRID_XZ_YZ 6
#define GRID_ALL 7

//------------------------------------------------------------------------------
class DLLExport Grid
{
protected:
        float length;
        float width;
        float height;
        float interval;
        ColorRGB color;
        Vector3 pos;
        Vector3 draw_type;
        
        bool draw_axis;
public:
        Axis *axis;     //axis for grid
        
        Grid();
        Grid(float length, float width, float height, float interval);
        Grid(float length, float width, float height, float interval, ColorRGB *color, Vector3 *pos);
        Grid(const Grid &grid);
        virtual ~Grid();

        virtual void setInterval(float interval);
        
        virtual void setPosition(Vector3 *v);
        virtual void setPosition(float x, float y, float z);

        virtual void setLength(float length);
        virtual void setWidth(float width);
        virtual void setHeight(float height);

        virtual void setColor(ColorRGB *color);
        virtual void setColor(float red, float green, float blue);

        virtual void setDrawType(Vector3 *draw_type);
        
        virtual void setAxis(bool draw_axis);
        virtual void setProperties(float length, float width, float height, float interval, ColorRGB *color, Vector3 *pos);
        
        virtual float getLength();
        virtual float getWidth();
        virtual float getHeight();
        virtual float getInterval();
        virtual ColorRGB&   getColor();
        virtual Vector3& getPosition();

        virtual void DrawGridXY();
        virtual void DrawGridXZ();
        virtual void DrawGridYZ();
        virtual void Draw();
};
};
};
//------------------------------------------------------------------------------
#endif
 