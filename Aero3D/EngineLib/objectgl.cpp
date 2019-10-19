#include "StdAfx.h"
#include "objectgl.h"

using namespace EngineGL;
using namespace ObjectGL;
using namespace MathGL;
using namespace TransformGL;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                              Object                                        */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int Object::list_count = 0;

Object::Object()
{
        name = "";
        color = 0;
        pos = 0;
        angle = 0;
        scale = 1;
        
        vertex  = 0; vertex_count  = 0;
        polygon = 0; polygon_count = 0;
        mapcoord = 0;
        faceNormal = 0;
        vertexNormal = 0;

        getIndexList();
}

//------------------------------------------------------------------------------
Object::Object(string name)
{
        setName(name);
        color = 0;
        pos = 0;
        angle = 0;
        scale = 1;

        vertex  = 0; vertex_count  = 0;
        polygon = 0; polygon_count = 0;
        mapcoord = 0;
        faceNormal = 0;
        vertexNormal = 0;

        getIndexList();
}

//------------------------------------------------------------------------------
Object::Object(double x, double y, double z)
{
        pos.x = x;
        pos.y = y;
        pos.z = z;
        angle = 0;
        scale = 1;

        vertex  = 0; vertex_count  = 0;
        polygon = 0; polygon_count = 0;
        mapcoord = 0;
        faceNormal = 0;
        vertexNormal = 0;

        getIndexList();
}

//------------------------------------------------------------------------------
Object::Object(string name, ColorRGB *color, Vector3 *pos)
{
        setName(name);
        setColor(color);
        setPosition(pos);

        angle = 0;
        scale = 1;

        vertex  = 0; vertex_count  = 0;
        polygon = 0; polygon_count = 0;
        mapcoord = 0;
        faceNormal = 0;
        vertexNormal = 0;

        getIndexList();
}

//------------------------------------------------------------------------------
Object::~Object()
{
        if( vertex  != NULL )delete[] vertex;
        if( polygon != NULL )delete[] polygon;
        if( mapcoord!= NULL )delete[] mapcoord;
        if( faceNormal != NULL )delete[] faceNormal;
        if( vertexNormal != NULL )delete[] vertexNormal;
}

//------------------------------------------------------------------------------
void Object::Draw()
{
        glCallList(index);
}

//------------------------------------------------------------------------------
void Object::PrepareDraw()
{
        newImageList();
}

//------------------------------------------------------------------------------
void Object::Rotate(double degree, double x, double y, double z)
{
        angle.x = x;
        angle.y = y;
        angle.z = z;
}

//------------------------------------------------------------------------------
void Object::Translate(double x, double y, double z)
{
        pos.x = x;
        pos.y = y;
        pos.z = z;
}

//------------------------------------------------------------------------------
void Object::Scale(double x, double y, double z)
{
        scale.x = x;
        scale.y = y;
        scale.z = z;
}

//------------------------------------------------------------------------------
void Object::setName(string name)
{
        this->name = name;
}

//------------------------------------------------------------------------------
void Object::setColor(ColorRGB *color)
{
        this->color = *color;
}

//------------------------------------------------------------------------------
void Object::setPosition(Vector3 *pos)
{
        Translate(pos->x, pos->y, pos->z);
}

//------------------------------------------------------------------------------
void Object::setVertexCount(int count)
{
        vertex_count = count;

        if( vertex != NULL )delete[] vertex;
        if( mapcoord != NULL )delete[] mapcoord;
        if( vertexNormal != NULL )delete[] vertexNormal;

        vertex = new Vertex[vertex_count];
        mapcoord = new Mapcoord[vertex_count];
        vertexNormal = new Vertex[vertex_count];
}

//------------------------------------------------------------------------------
void Object::setPolygonCount(int count)
{
        polygon_count = count;

        if( polygon != NULL )delete[] polygon;
        if( faceNormal != NULL )delete[] faceNormal;

        polygon = new GLPolygon[polygon_count];
        faceNormal = new Vertex[polygon_count];
}

//------------------------------------------------------------------------------
void Object::setVertexNull()
{
        if( vertex != NULL && vertex_count != 0 )
        {
                for(int i = 0; i < vertex_count; i++)
                {
                        vertex[i] = 0;
                }
        }
}

//------------------------------------------------------------------------------
void Object::setMapcoordNull()
{
        if( mapcoord != NULL && vertex_count != 0 )
        {
                for(int i = 0; i < vertex_count; i++)
                {
                        mapcoord[i].u = 0;
                        mapcoord[i].v = 0;
                }
        }
}

//------------------------------------------------------------------------------
void Object::setPolygonNull()
{
        if( polygon != NULL && polygon_count != 0)
        {
                for(int i = 0; i < polygon_count; i++)
                {
                        polygon[i].a = 0;
                        polygon[i].b = 0;
                        polygon[i].c = 0;
                }
        }
}

//------------------------------------------------------------------------------
void Object::setNormalNull()
{
        if( vertexNormal != NULL )

          for(int i = 0; i < vertex_count; i++)vertexNormal[i] = 0;

        if( faceNormal != NULL )

          for(int i = 0; i < polygon_count; i++)faceNormal[i] = 0;
}

//------------------------------------------------------------------------------
int Object::getCurrentIndex()
{
        return list_count;
}
//------------------------------------------------------------------------------
int Object::getIndexList()
{
        list_count++;

        index = list_count;

        return index;
}
//------------------------------------------------------------------------------
string Object::getName()
{
        return name;
}

//------------------------------------------------------------------------------
ColorRGB& Object::getColor()
{
        return color;
}

//------------------------------------------------------------------------------
Vector3& Object::getPosition()
{
        return pos;
}

//------------------------------------------------------------------------------
int Object::getVertexCount()
{
        return vertex_count;
}

//------------------------------------------------------------------------------
int Object::getPolygonCount()
{
        return polygon_count;
}

//------------------------------------------------------------------------------
void Object::Select()
{
        isSelected = true;
}

//------------------------------------------------------------------------------
void Object::UnSelect()
{
        isSelected = false;
}

//------------------------------------------------------------------------------
bool Object::IsSelected()
{
        return isSelected;
}

//------------------------------------------------------------------------------
bool Object::ContainPoint(double x, double y)
{
        bool contain = false;

        for(int i = 0; i < polygon_count; i++)
        {
//                if()
        }

        return contain;
}

//------------------------------------------------------------------------------
void Object::newImageList()
{
        glNewList(index, GL_COMPILE);
          glPushMatrix();
          glTranslatef(pos.x, pos.y, pos.z);
          glRotatef(angle.x, 1,0,0);
          glRotatef(angle.y, 0,1,0);
          glRotatef(angle.z, 0,0,1);
          glScalef(scale.x, scale.y, scale.z);

          glPolygonMode(GL_FRONT_AND_BACK, draw_mode);

          glShadeModel(shading);
          
          glMaterialfv(face_mode, GL_AMBIENT, (float*)ambient);
          glMaterialfv(face_mode, GL_DIFFUSE, (float*)diffuse);
          glMaterialfv(face_mode, GL_SPECULAR, (float*)specular);
          glMaterialfv(face_mode, GL_EMISSION, (float*)emission);
          glMaterialfv(face_mode, GL_SHININESS, (float*)shininess);

          glBegin(GL_TRIANGLES);
            glColor4f(color.red, color.green, color.blue, color.alpha);
            for(int i = 0; i < polygon_count; i++)
            {
                  glTexCoord2f( mapcoord[ polygon[i].a ].u, mapcoord[polygon[i].a ].v);
                  glVertex3f(vertex[polygon[i].a].x, vertex[polygon[i].a].y, vertex[polygon[i].a].z);

                  glTexCoord2f( mapcoord[ polygon[i].b ].u, mapcoord[polygon[i].b ].v);
                  glVertex3f(vertex[polygon[i].b].x, vertex[polygon[i].b].y, vertex[polygon[i].b].z);

                  glTexCoord2f( mapcoord[ polygon[i].c ].u, mapcoord[polygon[i].c ].v);
                  glVertex3f(vertex[polygon[i].c].x, vertex[polygon[i].c].y, vertex[polygon[i].c].z);
            }
          glEnd();
          glPopMatrix();
        glEndList();
}


