#include "StdAfx.h"
#include "grid.h"
using namespace EngineGL;
using namespace ObjectGL;
using namespace MathGL;
//------------------------------------------------------------------------------
Grid::Grid()
{
        length = 0;
        width  = 0;
        height = 0;
        interval = 0;
        color = 0;
        pos   = 0;

        draw_type = true;
        draw_axis = true;

        axis = new Axis();
}

//------------------------------------------------------------------------------
Grid::Grid(float length, float width, float height, float interval)
{
        this->length   = length;
        this->width    = width;
        this->height   = height;
        this->interval = interval;
        this->color    = 0;
        this->pos      = 0;

        draw_type = true;
        draw_axis = true;

        axis = new Axis();
}

//------------------------------------------------------------------------------
Grid::Grid(float length, float width, float height, float interval, ColorRGB *color, Vector3 *pos)
{
        this->length   = length;
        this->width    = width;
        this->height   = height;
        this->interval = interval;
        this->color    = *color;
        this->pos     = *pos;

        draw_type = true;
        draw_axis = true;        

        axis = new Axis();
        axis->setPosition(pos);
        axis->setLength(&Vector3(length,width,height));
}

//------------------------------------------------------------------------------
Grid::Grid(const Grid &grid)
{
        length = grid.length;
        width  = grid.width;
        height = grid.height;
        interval = grid.interval;
        color = grid.color;
        pos   = grid.pos;

        draw_type = grid.draw_type;
        draw_axis = grid.draw_axis;

        axis = new Axis((const Axis&)grid.axis);
}

//------------------------------------------------------------------------------
Grid::~Grid()
{
        delete axis;
}

//------------------------------------------------------------------------------
void Grid::setInterval(float interval)
{
        this->interval = interval;
}

//------------------------------------------------------------------------------
void Grid::setPosition(Vector3 *v)
{
        pos = *v;
}

//------------------------------------------------------------------------------
void Grid::setPosition(float x, float y, float z)
{
        pos.x = x;
        pos.y = y;
        pos.z = z;

        axis->setPosition(x,y,z);
}

//------------------------------------------------------------------------------
void Grid::setLength(float length)
{
        this->length = length;

        axis->setLength(&Vector3(length, width, height));
}

//------------------------------------------------------------------------------
void Grid::setWidth(float width)
{
        this->width = width;

        axis->setLength(&Vector3(length, width, height));
}

//------------------------------------------------------------------------------
void Grid::setHeight(float height)
{
        this->height = height;

        axis->setLength(&Vector3(length, width, height));
}

//------------------------------------------------------------------------------
void Grid::setColor(ColorRGB *color)
{
        this->color = *color;
}

//------------------------------------------------------------------------------
void Grid::setColor(float red, float green, float blue)
{
        color.red = red;
        color.green = green;
        color.blue = blue;
}

//------------------------------------------------------------------------------
void Grid::setDrawType(Vector3 *draw_type)
{
        this->draw_type = *draw_type;
}

//------------------------------------------------------------------------------
void Grid::setAxis(bool draw_axis)
{
        this->draw_axis = draw_axis;
}

//------------------------------------------------------------------------------
void Grid::setProperties(float length, float width, float height, float interval, ColorRGB *color, Vector3 *pos)
{
        setLength(length);
        setWidth(width);
        setHeight(height);
        setInterval(interval);
        setColor(color);
        setPosition(pos);
}

//------------------------------------------------------------------------------
float Grid::getLength()
{
        return length;
}

//------------------------------------------------------------------------------
float Grid::getWidth()
{
        return width;
}

//------------------------------------------------------------------------------
float Grid::getHeight()
{
        return height;
}

//------------------------------------------------------------------------------
float Grid::getInterval()
{
        return interval;
}

//------------------------------------------------------------------------------
ColorRGB& Grid::getColor()
{
        return color;
}

//------------------------------------------------------------------------------
Vector3& Grid::getPosition()
{
        return pos;
}

//------------------------------------------------------------------------------
void Grid::DrawGridXY()
{
        float i;

        glBegin(GL_LINES);
          i = pos.y;
          while( i <= pos.y + width )
          {
                  glVertex3f(pos.x,          i, pos.z);
                  glVertex3f(pos.x + length, i, pos.z);
                  i = i + interval;
          }

          i = pos.x;
          while( i <= pos.x + length )
          {
                  glVertex3f(i, pos.y,         pos.z);
                  glVertex3f(i, pos.y + width, pos.z);
                  i = i + interval;
          }
        glEnd();
}

//------------------------------------------------------------------------------
void Grid::DrawGridXZ()
{
        float i;

        glBegin(GL_LINES);
          //---draw XZ
          i = pos.z;
          while( i <= pos.z + height )
          {
                glVertex3f(pos.x,          pos.y, i);
                glVertex3f(pos.x + length, pos.y, i);
                i = i + interval;
          }

          i = pos.x;
          while( i <= pos.x + length )
          {
                glVertex3f(i, pos.y, pos.z);
                glVertex3f(i, pos.y, pos.z + height);
                i = i + interval;
          }
        glEnd();
}

//------------------------------------------------------------------------------
void Grid::DrawGridYZ()
{
        float i;

        glBegin(GL_LINES);
          i = pos.y;
          while( i <= pos.y + width )
          {
                glVertex3f(pos.x, i, pos.z);
                glVertex3f(pos.x, i, pos.z + height);
                i = i + interval;
          }

          i = pos.z;
          while( i <= pos.z + height )
          {
                glVertex3f(pos.x, pos.y,         i);
                glVertex3f(pos.x, pos.y + width, i);
                i = i + interval;
          }
        glEnd();
}

//------------------------------------------------------------------------------
void Grid::Draw()
{
        glPushAttrib(GL_CURRENT_BIT);
          unsigned char lighting;

          glGetBooleanv(GL_LIGHTING, &lighting);

          if( lighting )glDisable(GL_LIGHTING);

            if( draw_axis )axis->Draw();

            glColor3f(color.red, color.green, color.blue);
            if( draw_type.x )DrawGridXY();
            if( draw_type.y )DrawGridXZ();
            if( draw_type.z )DrawGridYZ();
            
          if( lighting )glEnable(GL_LIGHTING);
        glPopAttrib();
}

//------------------------------------------------------------------------------

