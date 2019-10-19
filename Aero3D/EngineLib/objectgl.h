#pragma once

#ifndef objectglH
#define objectglH

#include <string>
#include <gl/gl.h>
#include <gl/glu.h>
#include "macros.h"
#include "color.h"
#include "vector.h"
#include "transform.h"

using namespace std;
using namespace EngineGL::TransformGL;

namespace EngineGL
{
	namespace ObjectGL
	{

typedef Vector3 Vertex;

using namespace std;

//------------------------------------------------------------------------------
struct DLLExport GLPolygon
{
        int a,b,c;
};

struct DLLExport Mapcoord
{
        double u,v;
};

//------------------------------------------------------------------------------
class DLLExport Object
{
protected:
        static int list_count;
        int index;

        SELObject   *selObject;    //selection object
        ROTObject   *rotObject;    //rotation object
        SCALEObject *scaleObject;  //scaling object

        Vertex    *vertex;
        GLPolygon *polygon;
        Mapcoord  *mapcoord;
        Vertex    *faceNormal;
        Vertex    *vertexNormal;
        int vertex_count;
        int polygon_count;

        bool    isSelected;
public:
        string   name;
        Vector3  pos;             //vector - position
        Vector3  angle;           //vector - rotation
        Vector3  scale;           //vector - scale
        
        ColorRGB color;
        ColorRGB ambient;
        ColorRGB diffuse;
        ColorRGB specular;
        ColorRGB emission;
        ColorRGB shininess;
        int draw_mode;
        int face_mode;
        int shading;
        
        Object();
        Object(string name);
        Object(double x, double y, double z);
        Object(string name, ColorRGB *color, Vector3 *position); 
        virtual ~Object();

        virtual void Draw();
        virtual void PrepareDraw();
        virtual void Rotate(double degree, double x, double y, double z);
        virtual void Translate(double x, double y, double z);
        virtual void Scale(double x, double y, double z);
        
        virtual void setName(string name);
        virtual void setColor(ColorRGB *color);
        virtual void setPosition(Vector3 *position);
        virtual void setVertexCount(int count);
        virtual void setPolygonCount(int count);
        virtual void setVertexNull();
        virtual void setMapcoordNull();
        virtual void setPolygonNull();
        virtual void setNormalNull();

        virtual int getCurrentIndex();
        virtual int getIndexList();

        virtual string getName();
        virtual ColorRGB& getColor();
        virtual Vector3& getPosition();
        virtual int getVertexCount();
        virtual int getPolygonCount();

        virtual void Select();
        virtual void UnSelect();
        virtual bool IsSelected();

        virtual bool ContainPoint(double x, double y);

        virtual void newImageList();
};

	};
};
#endif
