#include "StdAfx.h"
#include "axis.h"
using namespace EngineGL;
using namespace ObjectGL;
using namespace MathGL;
//------------------------------------------------------------------------------
Axis::Axis()
{
        length = 0;
        radius = 0;
        height = 0;
        scaleText = 1;
        angleText = 0;
        position  = 0;

        color.color_x = ColorRed();
        color.color_y = ColorGreen();
        color.color_z = ColorBlue();

        draw_type = true;
        label_type = LABEL3D;

        draw_cone = true;
        draw_label = true;

        quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric,GLU_FILL);
        gluQuadricNormals(quadric, GLU_SMOOTH);
}

//------------------------------------------------------------------------------
Axis::Axis(float length, float radius, float height, float scaleText, float angleText, Vector3 *position)
{
        this->length = length;
        this->radius = radius;
        this->height = height;
        this->scaleText  = scaleText;
        this->angleText  = angleText;

        this->position = *position;

        color.color_x = ColorRed();
        color.color_y = ColorGreen();
        color.color_z = ColorBlue();

        draw_type = true;
        label_type = LABEL3D;

        draw_cone = true;
        draw_label = true;            

        quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric,GLU_FILL);
        gluQuadricNormals(quadric, GLU_SMOOTH);
}

//------------------------------------------------------------------------------
Axis::Axis(const Axis &axis)
{
        length = axis.length;
        radius = axis.radius;
        height = axis.height;
        scaleText = axis.scaleText;
        angleText = axis.angleText;

        position = axis.position;

        color.color_x = axis.color.color_x;
        color.color_y = axis.color.color_y;
        color.color_z = axis.color.color_z;

        draw_type = axis.draw_type;
        label_type = axis.label_type;

        quadric = gluNewQuadric();
        gluQuadricDrawStyle(quadric,GLU_FILL);
        gluQuadricNormals(quadric, GLU_SMOOTH);
}

//------------------------------------------------------------------------------
Axis::~Axis()
{
        gluDeleteQuadric(quadric);
}

//------------------------------------------------------------------------------
void Axis::setPosition(Vector3 *v)
{
        position = *v;
}

//------------------------------------------------------------------------------
void Axis::setPosition(float x, float y, float z)
{
        position.x = x;
        position.y = y;
        position.z = z;
}

//------------------------------------------------------------------------------
void Axis::setLength(float length)
{
        this->length = length;
}

//------------------------------------------------------------------------------
void Axis::setLength(Vector3 *length)
{
        this->length = *length;
}

//------------------------------------------------------------------------------
void Axis::setRadius(float radius)
{
        this->radius = radius;
}

//------------------------------------------------------------------------------
void Axis::setRadius(Vector3 *radius)
{
        this->radius = *radius;
}

//------------------------------------------------------------------------------
void Axis::setHeight(float height)
{
        this->height = height;
}

//------------------------------------------------------------------------------
void Axis::setHeight(Vector3 *height)
{
        this->height = *height;
}

//------------------------------------------------------------------------------
void Axis::setColor(int type, ColorRGB &color)
{
        switch(type)
        {
                case AXIS_X : this->color.color_x = color; break;
                case AXIS_Y : this->color.color_y = color; break;
                case AXIS_Z : this->color.color_z = color; break;
        }
}

//------------------------------------------------------------------------------
void Axis::setColor(int type, float red, float green, float blue)
{
        switch(type)
        {
                case AXIS_X : color.color_x = ColorRGB(red, green, blue); break;
                case AXIS_Y : color.color_y = ColorRGB(red, green, blue); break;
                case AXIS_Z : color.color_z = ColorRGB(red, green, blue); break;
        }
}

//------------------------------------------------------------------------------
void Axis::setScale(float scaleText)
{
        this->scaleText = scaleText;
}

//------------------------------------------------------------------------------
void Axis::setAngle(float angleText)
{
        this->angleText = angleText;
}

//------------------------------------------------------------------------------
void Axis::setLabelType(int type)
{
        label_type = type;
}

//------------------------------------------------------------------------------
void Axis::setDrawType(Vector3 *draw_type)
{
        this->draw_type = *draw_type;
}

//------------------------------------------------------------------------------
void Axis::setDrawType(bool x, bool y, bool z)
{
        draw_type.x = x;
        draw_type.y = y;
        draw_type.z = z;
}

//------------------------------------------------------------------------------
void Axis::setCone(bool draw)
{
        draw_cone = draw;
}

//------------------------------------------------------------------------------
void Axis::setLabel(bool draw)
{
        draw_label = draw;
}

//------------------------------------------------------------------------------
void Axis::setProperties(float length, float radius, float height, float scale, float angle, Vector3 *position)
{
        setLength(length);
        setRadius(radius);
        setHeight(height);
        setScale(scale);
        setAngle(angle);
        setPosition(position);
}

//------------------------------------------------------------------------------
Vector3& Axis::getLength()
{
        return length;
}

//------------------------------------------------------------------------------
Vector3& Axis::getRadius()
{
        return radius;
}

//------------------------------------------------------------------------------
Vector3& Axis::getHeight()
{
        return height;
}

//------------------------------------------------------------------------------
float Axis::getScale()
{
        return scaleText;
}

//------------------------------------------------------------------------------
float Axis::getAngle()
{
        return angleText;
}

//------------------------------------------------------------------------------
int Axis::getLabelType()
{
        return label_type;
}

//------------------------------------------------------------------------------
ColorRGB& Axis::getColor(int type)
{
        switch(type)
        {
                case AXIS_X : return color.color_x;
                case AXIS_Y : return color.color_y;
                case AXIS_Z : return color.color_z;
                default : return color.color_x;
        }
}

//------------------------------------------------------------------------------
Vector3& Axis::getPosition()
{
        return position;
}

//------------------------------------------------------------------------------
void Axis::DrawLine()
{
        glBegin(GL_LINES);
            //x - line
            if( draw_type.x )
            {
                    glColor3f(color.color_x.red, color.color_x.green, color.color_x.blue);
                    glVertex3f(position.x,          position.y, position.z);
                    glVertex3f(position.x+length.x, position.y, position.z);
            }

            //y - line
            if( draw_type.y )
            {
                    glColor3f(color.color_y.red, color.color_y.green, color.color_y.blue);
                    glVertex3f(position.x, position.y,          position.z);
                    glVertex3f(position.x, position.y+length.y, position.z);
            }

            //z - line
            if( draw_type.z )
            {
                    glColor3f(color.color_z.red, color.color_z.green, color.color_z.blue);
                    glVertex3f(position.x, position.y, position.z);
                    glVertex3f(position.x, position.y, position.z + length.z);
            }
        glEnd();

}

//------------------------------------------------------------------------------
void Axis::DrawCone()
{
        //---draw x-cone
        if( draw_type.x )
        {
          glPushMatrix();
            glColor3f(color.color_x.red, color.color_x.green, color.color_x.blue);
            glTranslatef(position.x + length.x, position.y, position.z);
            glRotatef(90.0f,0,1,0);

            gluCylinder(quadric, radius.x, 0, height.x, 15, 15);
            gluDisk(quadric, 0, radius.x, 15, 15);
          glPopMatrix();
        }

        //---draw y-cone
        if( draw_type.y )
        {
          glPushMatrix();
            glColor3f(color.color_y.red, color.color_y.green, color.color_y.blue);
            glTranslatef(position.x, position.y + length.y, position.z);
            glRotatef(-90.0f,1,0,0);

            gluCylinder(quadric, radius.y, 0, height.y, 15, 15);
            gluDisk(quadric, 0, radius.y, 15, 15);
          glPopMatrix();
        }

        //---draw z-cone
        if( draw_type.z )
        {
          glPushMatrix();
            glColor3f(color.color_z.red, color.color_z.green, color.color_z.blue);
            glTranslatef(position.x, position.y, position.z + length.z);
            glRotatef(90.0f,0,0,1);

            gluCylinder(quadric, radius.z, 0, height.z, 15, 15);
            gluDisk(quadric, 0, radius.z, 15, 15);
          glPopMatrix();
        }
}

//------------------------------------------------------------------------------
void Axis::DrawLabel()
{
      if( label_type == LABEL2D )
      {

      }
      
      if( label_type == LABEL3D )
      {
        if( draw_type.x )
        {
          glPushMatrix();
            glColor3f(color.color_x.red, color.color_x.green, color.color_x.blue);

            glTranslatef(position.x + length.x + height.x, position.y - radius.y, position.z + radius.z);
            glRotatef(angleText,1.0f, 0.0f, 0.0f);
            glScalef(scaleText,scaleText,scaleText);

            glListBase(100);
            glCallLists(1,GL_UNSIGNED_BYTE, "X");
          glPopMatrix();
        }

        //label Y
        if( draw_type.y )
        {
          glPushMatrix();
            glColor3f(color.color_y.red, color.color_y.green, color.color_y.blue);

            glTranslatef(position.x - radius.x, position.y + length.y + height.y + 0.1, position.z + radius.z);
            glRotatef(angleText, 0.0f, 1.0f,0.0f);
            glScalef(scaleText, scaleText, scaleText);

            glListBase(100);
            glCallLists(1,GL_UNSIGNED_BYTE, "Y");
          glPopMatrix();
        }

        //label Z
        if( draw_type.z )
        {
          glPushMatrix();
            glColor3f(color.color_z.red, color.color_z.green, color.color_z.blue);

            glTranslatef(position.x - radius.x, position.y - radius.y, position.z + length.z + height.z + 0.1);
            glRotatef(angleText,0.0f, 0.0f,1.0f);
            glScalef(scaleText,scaleText,scaleText);

            glListBase(100);
            glCallLists(1,GL_UNSIGNED_BYTE, "Z");
          glPopMatrix();
        }  
      }
}

//------------------------------------------------------------------------------
void Axis::Draw()
{
        glPushAttrib(GL_CURRENT_BIT);
         DrawLine();
         if( draw_cone )DrawCone();
         if( draw_label )DrawLabel();
        glPopAttrib();
}