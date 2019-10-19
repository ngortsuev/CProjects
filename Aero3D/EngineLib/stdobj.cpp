#include "StdAfx.h"
#include "stdobj.h"
#include "engine.h"
//------------------------------------------------------------------------------
Box::Box() : Object()
{
        setLength(0);
        setWidth(0);
        setHeight(0);

        setVertexCount(8);
        setPolygonCount(12);
}

//------------------------------------------------------------------------------
Box::Box(string name) : Object(name)
{
        setLength(0);
        setWidth(0);
        setHeight(0);

        setVertexCount(8);
        setPolygonCount(12);
}

//------------------------------------------------------------------------------
Box::Box(string name, ColorRGB *color, Vector3 *pos) : Object(name, color, pos)
{
        setLength(0);
        setWidth(0);
        setHeight(0);

        setVertexCount(8);
        setPolygonCount(12);
}

//------------------------------------------------------------------------------
Box::Box(string name, float length, float width, float height, ColorRGB *color, Vector3 *pos) : Object(name, color, pos)
{
        setLength(length);
        setWidth(width);
        setHeight(height);

        setVertexCount(8);
        setPolygonCount(12);

        PrepareDraw();        
}

//------------------------------------------------------------------------------
void Box::setLength(float length)
{
        this->length = length;
}

//------------------------------------------------------------------------------
void Box::setWidth(float width)
{
        this->width = width;
}

//------------------------------------------------------------------------------
void Box::setHeight(float height)
{
        this->height = height;
}

//------------------------------------------------------------------------------
void Box::Draw()
{
        Object::Draw();

        if( isSelected && selObject != NULL )selObject->Draw();
}

//------------------------------------------------------------------------------
void Box::PrepareDraw()
{
        vertex[0].x = pos.x - length/2;  vertex[0].y = pos.y - width/2; vertex[0].z = pos.z;
        vertex[1].x = pos.x + length/2;  vertex[1].y = pos.y - width/2; vertex[1].z = pos.z;
        vertex[2].x = pos.x + length/2;  vertex[2].y = pos.y + width/2; vertex[2].z = pos.z;
        vertex[3].x = pos.x - length/2;  vertex[3].y = pos.y + width/2; vertex[3].z = pos.z;

        vertex[4].x = pos.x - length/2;  vertex[4].y = pos.y - width/2;  vertex[4].z = pos.z + height;
        vertex[5].x = pos.x + length/2;  vertex[5].y = pos.y - width/2;  vertex[5].z = pos.z + height;
        vertex[6].x = pos.x + length/2;  vertex[6].y = pos.y + width/2;  vertex[6].z = pos.z + height;
        vertex[7].x = pos.x - length/2;  vertex[7].y = pos.y + width/2;  vertex[7].z = pos.z + height;
        //
        polygon[0].a = 0; polygon[0].b = 1; polygon[0].c = 2;
        polygon[1].a = 0; polygon[1].b = 2; polygon[1].c = 3;

        polygon[2].a = 4; polygon[2].b = 5; polygon[2].c = 6;
        polygon[3].a = 4; polygon[3].b = 6; polygon[3].c = 7;

        //
        polygon[4].a = 5; polygon[4].b = 1; polygon[4].c = 2;
        polygon[5].a = 5; polygon[5].b = 2; polygon[5].c = 6;

        polygon[6].a = 4; polygon[6].b = 0; polygon[6].c = 3;
        polygon[7].a = 4; polygon[7].b = 3; polygon[7].c = 7;

        //
        polygon[8].a = 4; polygon[8].b = 5; polygon[8].c = 1;
        polygon[9].a = 4; polygon[9].b = 1; polygon[9].c = 0;

        
        polygon[10].a = 7; polygon[10].b = 6; polygon[10].c = 2;
        polygon[11].a = 7; polygon[11].b = 2; polygon[11].c = 3;

        Object::PrepareDraw();
}

//------------------------------------------------------------------------------
void Box::Rotate(float degree, float x, float y, float z)
{
        if( x == 1 && y == 0 && z == 0)angle.x += degree;
        if( x == 0 && y == 1 && z == 0)angle.y += degree;
        if( x == 0 && y == 0 && z == 1)angle.z += degree;
     
        newImageList();
}

//------------------------------------------------------------------------------
void Box::Translate(float x, float y, float z)
{
        pos.x += x;
        pos.y += y;
        pos.z += z;
        /*
        for(int i = 0; i < vertex_count; i++)
        {
                vertex[i].x += x;
                vertex[i].y += y;
                vertex[i].z += z;
        }
        */
        newImageList();
}

//------------------------------------------------------------------------------
void Box::Scale(float x, float y, float z)
{
        scale.x = x;
        scale.y = y;
        scale.z = z;
        /*
        for(int i = 0; i < vertex_count; i++)
        {
                vertex[i].x *= x;
                vertex[i].y *= y;
                vertex[i].z *= z;
        }
        */
        newImageList();
}

//------------------------------------------------------------------------------
void Box::Select()
{
        isSelected = true;

        selObject = new SELObject(&pos, length, width, height, 0.2);
}

//------------------------------------------------------------------------------
void Box::UnSelect()
{
        isSelected = false;

        if( selObject != NULL )delete selObject;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Sphere                                      */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Sphere::Sphere() : Object()
{
        radius = 0;
}

//------------------------------------------------------------------------------
Sphere::Sphere(string name) : Object(name)
{
        radius = 0;
}

//------------------------------------------------------------------------------
Sphere::Sphere(string name, ColorRGB *color, Vertex *pos) : Object(name,color,pos)
{
        radius = 0;
}

//------------------------------------------------------------------------------
Sphere::Sphere(string name, ColorRGB *color, Vertex *pos, float radius) : Object(name,color,pos)
{
        this->radius = radius;
}

//------------------------------------------------------------------------------
void Sphere::Draw()
{

}

//------------------------------------------------------------------------------
void Sphere::PrepareDraw()
{
        int count;
        float i,j;
        float x1,y1,z1;

        j = -M_PI/2;
        while( j <= M_PI/2)
        {
                i = -M_PI;
                glBegin(GL_LINE_STRIP);
                   while( i <= M_PI + 0.1 )
                   {
                       x1 = radius * cos(j) * cos(i);
                       y1 = radius * cos(j) * sin(i);
                       z1 = radius * sin(j);

                       glVertex3f(x1 + pos.x, y1 + pos.y, z1 + pos.z);
                       
                       i = i + 0.1;
                   }
                glEnd();

                j = j + 0.1;
        }

}

//------------------------------------------------------------------------------
void Sphere::setRadius(float radius)
{
        this->radius = radius;

        PrepareDraw();
}

//------------------------------------------------------------------------------
void Sphere::Select()
{
}

//------------------------------------------------------------------------------
void Sphere::UnSelect()
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Text3D                                      */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Text3D::Text3D() : Object()
{
        deviation = 0;
        extrusion = 0;
        format    = WGL_FONT_POLYGONS;
}

//------------------------------------------------------------------------------
Text3D::Text3D(string name, ColorRGB *color, Vector3 *pos) : Object(name, color, pos)
{
        deviation = 0;
        extrusion = 0;
        format    = WGL_FONT_POLYGONS;
}

//------------------------------------------------------------------------------
Text3D::Text3D(string textStr, string name, ColorRGB *color, Vector3 *pos) : Object(name, color, pos)
{
        this->textStr = textStr;

        deviation = 0;
        extrusion = 0;
        format    = WGL_FONT_POLYGONS;
}

//------------------------------------------------------------------------------
Text3D::~Text3D()
{
}

//------------------------------------------------------------------------------
void Text3D::Draw()
{
        glPushMatrix();
          glColor3f(color.red, color.green, color.blue);

          glTranslatef(pos.x, pos.y, pos.z);
          glRotatef(angle.x, 1, 0, 0);
          glRotatef(angle.y, 0, 1, 0);
          glRotatef(angle.z, 0, 0, 1);
          glScalef(scale.x, scale.y, scale.z);

		  glListBase(index);
          glCallLists(textStr.length(), GL_UNSIGNED_BYTE, textStr.c_str());
        glPopMatrix();
}

//------------------------------------------------------------------------------
void Text3D::Draw(string textStr)
{
        setText(textStr);

        Draw();
}

//------------------------------------------------------------------------------
void Text3D::Draw(string textStr, Vector3 *pos)
{
        setText(textStr);

        setPosition(pos);

        Draw();
}

//------------------------------------------------------------------------------
void Text3D::PrepareDraw()
{
        wglUseFontOutlines((OpenGL::getSelContext())->getDC(), 0, 255, index, deviation, extrusion, format, NULL);
}

//------------------------------------------------------------------------------
void Text3D::setText(string textStr)
{
        this->textStr = textStr;
}

//------------------------------------------------------------------------------
void Text3D::setDeviation(float deviation)
{
        this->deviation = deviation;
}

//------------------------------------------------------------------------------
void Text3D::setExtrusion(float extrusion)
{
        this->extrusion = extrusion;
}

//------------------------------------------------------------------------------
void Text3D::setFormat(int format)
{
        this->format = format;
}

//------------------------------------------------------------------------------
Mesh::Mesh() : Object()
{
}

//------------------------------------------------------------------------------
Mesh::~Mesh()
{
}

//------------------------------------------------------------------------------
Vertex& Mesh::getVertex(int index)
{
        return vertex[index];
}

//------------------------------------------------------------------------------
GLPolygon& Mesh::getPolygon(int index)
{
        return polygon[index];
}

//------------------------------------------------------------------------------
Mapcoord& Mesh::getMapcoord(int index)
{
        return mapcoord[index];
}
