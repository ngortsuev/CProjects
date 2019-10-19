#pragma once

#include <string>
#include <fstream>
#include "Macros.h"
#include "stdobj.h"

using namespace std;


//------------------------------------------------------------------------------
class DLLExport Chunk
{
protected:
        unsigned short id;
        unsigned int length;
        fstream *file;
public:
        Chunk(fstream *file);
        virtual ~Chunk();
        virtual unsigned short getId();
        virtual unsigned int getLength();
        virtual void getData(void *data);
        virtual void setData(void *data);
        //virtual int findChunk(unsigned short id);
};

//------------------------------------------------------------------------------
class DLLExport ChunkNull : public Chunk
{
public:
        ChunkNull(fstream *file);
        virtual ~ChunkNull();
        virtual unsigned short getId();
        virtual unsigned int getLength();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkMain : public Chunk
{
public:
        ChunkMain(fstream *file);
        virtual ~ChunkMain();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkEdit : public Chunk
{
public:
        ChunkEdit(fstream *file);
        virtual ~ChunkEdit();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkObject : public Chunk
{
public:
        ChunkObject(fstream *file);
        virtual ~ChunkObject();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkTriMesh : public Chunk
{
public:
        ChunkTriMesh(fstream *file);
        virtual ~ChunkTriMesh();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkVertex : public Chunk
{
public:
        ChunkVertex(fstream *file);
        virtual ~ChunkVertex();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkPolygon : public Chunk
{
public:
        ChunkPolygon(fstream *file);
        virtual ~ChunkPolygon();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkMapCoord : public Chunk
{
public:
        ChunkMapCoord(fstream *file);
        virtual ~ChunkMapCoord();
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkScale : public Chunk
{
public:
        ChunkScale(fstream *file);
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkViewportSize : public Chunk
{
public:
        ChunkViewportSize(fstream *file);
        virtual void getData(void *data);
};

//------------------------------------------------------------------------------
class DLLExport ChunkCreator
{
public:
        static const unsigned short chMain = 0x4d4d;         //MAIN3DS
        static const unsigned short chEdit = 0x3d3d;         //EDIT3DS
        static const unsigned short chObject = 0x4000;       //EDIT_OBJECT
        static const unsigned short chTriMesh = 0x4100;        //OBJ_TRIMESH
        static const unsigned short chVertex = 0x4110;           //VERTEX
        static const unsigned short chPolygon = 0x4120;          //FACES
        static const unsigned short chMapCoord = 0x4140;         //MAPPINGCOORDS
        static const unsigned short chScale = 0x0100;

        //----------------------------------------------
        ChunkCreator();
        virtual ~ChunkCreator();
        virtual Chunk* CreateChunk(fstream *file);
        virtual Chunk* CreateChunk(fstream *file, unsigned short id, void *data);
};

//--------------------------------File3DS---------------------------------------
class DLLExport File3DS
{
protected:
    Mesh *mesh;
    fstream *file;        
	string filename;
	bool isOpened;
	
public:
	File3DS(string filename);
    File3DS(string filename, Mesh *mesh);
    virtual ~File3DS();
    virtual bool open();
    virtual void read();
    virtual void write();
    virtual void close();
    virtual Mesh* getMesh();
    virtual void  setMesh(Mesh *mesh);
};
