#include "StdAfx.h"
#include "transform.h"

using namespace EngineGL;
using namespace MathGL;
using namespace TransformGL;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                              SELObject - Select Object                     */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
SELObject::SELObject(float x, float y, float z)
{
        pos.x = x;
        pos.y = y;
        pos.z = z;
        length = 0;
        width = 0;
        height = 0;

        axis = new Axis(0.2, 0.05, 0.1, 0.1, 0, &pos);
}

//------------------------------------------------------------------------------
SELObject::SELObject(float x, float y, float z, float length, float width, float height, float size)
{
        pos.x = x;
        pos.y = y;
        pos.z = z;
        this->length = length;
        this->width  = width;
        this->height = height;
        this->size   = size;

        axis = new Axis(0.2, 0.05, 0.1, 0.1, 0, &pos);
}

//------------------------------------------------------------------------------
SELObject::SELObject(Vector3 *pos, float length, float width, float height, float size)
{
        this->pos = *pos;
        this->length = length;
        this->width  = width;
        this->height = height;
        this->size   = size;

        axis = new Axis(0.2, 0.05, 0.1, 0.1, 0, pos);
}

//------------------------------------------------------------------------------
SELObject::SELObject(Vector3 *pos, Vector3 *param, float size)
{
        this->pos = *pos;
        this->length = param->x;
        this->width  = param->y;
        this->height = param->z;
        this->size   = size;

        axis = new Axis(0.2, 0.05, 0.1, 0.1, 0, pos);
}

//------------------------------------------------------------------------------
SELObject::~SELObject()
{ 
}

//------------------------------------------------------------------------------
void SELObject::DrawAngle(Vector3 &pos)
{
        for(int i = 0; i < 8; i++)
        {
                glVertex3fv(pos); pos.x -= size;
                glVertex3fv(pos); pos.x += size;

                glVertex3fv(pos); pos.y -= size;
                glVertex3fv(pos); pos.y += size;

                glVertex3fv(pos); pos.z -= size;
                glVertex3fv(pos); pos.z += size;
        }
}

//------------------------------------------------------------------------------
void SELObject::Draw()
{
        float length_p = pos.x + length/2;
        float length_m = pos.x - length/2;

        float width_p  = pos.y + width/2;
        float width_m  = pos.y - width/2;

        float height_p = pos.z + height;

        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
          glColor3f(1,1,1);

          DrawAngle(Vector3(length_p, width_p, height_p));
          /*
          glVertex3f(length_p,        width_p,  height_p);
          glVertex3f(length_p - size, width_p,  height_p);

          glVertex3f(length_p,        width_p,        height_p);
          glVertex3f(length_p,        width_p - size, height_p);

          glVertex3f(length_p,        width_p, height_p);
          glVertex3f(length_p,        width_p, height_p - size);
          */
          //----
          glVertex3f(length_m,        width_p, height_p);
          glVertex3f(length_m + size, width_p, height_p);

          glVertex3f(length_m,        width_p,        height_p);
          glVertex3f(length_m,        width_p - size, height_p);

          glVertex3f(length_m,        width_p, height_p);
          glVertex3f(length_m,        width_p, height_p - size);

          //----
          glVertex3f(length_m,        width_m, height_p);
          glVertex3f(length_m + size, width_m, height_p);

          glVertex3f(length_m,        width_m,        height_p);
          glVertex3f(length_m,        width_m + size, height_p);

          glVertex3f(length_m, width_m, height_p);
          glVertex3f(length_m, width_m, height_p - size);

          //----
          glVertex3f(length_m,        width_p, pos.z);
          glVertex3f(length_m + size, width_p, pos.z);

          glVertex3f(length_m, width_p,        pos.z);
          glVertex3f(length_m, width_p - size, pos.z);

          glVertex3f(length_m, width_p, pos.z);
          glVertex3f(length_m, width_p, pos.z + size);

          //----
          glVertex3f(length_m,        width_m, pos.z);
          glVertex3f(length_m + size, width_m, pos.z);

          glVertex3f(length_m, width_m,        pos.z);
          glVertex3f(length_m, width_m + size, pos.z);

          glVertex3f(length_m, width_m, pos.z);
          glVertex3f(length_m, width_m, pos.z + size);

          //----
          glVertex3f(length_p,        width_m, height_p);
          glVertex3f(length_p - size, width_m, height_p);

          glVertex3f(length_p, width_m,        height_p);
          glVertex3f(length_p, width_m + size, height_p);

          glVertex3f(length_p, width_m, height_p);
          glVertex3f(length_p, width_m, height_p - size);

          //----
          glVertex3f(length_p,        width_m, pos.z);
          glVertex3f(length_p - size, width_m, pos.z);

          glVertex3f(length_p, width_m,        pos.z);
          glVertex3f(length_p, width_m + size, pos.z);

          glVertex3f(length_p, width_m, pos.z);
          glVertex3f(length_p, width_m, pos.z + size);

          //----
          glVertex3f(length_p,        width_p, pos.z);
          glVertex3f(length_p - size, width_p, pos.z);

          glVertex3f(length_p, width_p,        pos.z);
          glVertex3f(length_p, width_p - size, pos.z);

          glVertex3f(length_p, width_p, pos.z);
          glVertex3f(length_p, width_p, pos.z + size);
        glEnd();

        axis->Draw();

        glEnable(GL_LIGHTING);
}

//------------------------------------------------------------------------------
void SELObject::setLength(float length)
{
        this->length = length;
}

//------------------------------------------------------------------------------
void SELObject::setWidth(float width)
{
        this->width = width;
}

//------------------------------------------------------------------------------
void SELObject::setHeight(float height)
{
        this->height = height;
}
