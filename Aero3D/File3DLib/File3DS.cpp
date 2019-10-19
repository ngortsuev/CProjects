#include "StdAfx.h"
#include "File3DS.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                Chunk                                       */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Chunk::Chunk(fstream *file)
{
        this->id = 0;

        this->file = file;
		
        file->read((char*)&length, sizeof(length));
}

//------------------------------------------------------------------------------
Chunk::~Chunk()
{
}

//------------------------------------------------------------------------------
unsigned short Chunk::getId()
{
        return id;
}

//------------------------------------------------------------------------------
unsigned int Chunk::getLength()
{
        return length;
}

//------------------------------------------------------------------------------
void Chunk::getData(void *data)
{
}

//------------------------------------------------------------------------------
void Chunk::setData(void *data)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkNull                                   */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkNull::ChunkNull(fstream *file) : Chunk(file)
{
        id = NULL;
        file = NULL;
}

//------------------------------------------------------------------------------
ChunkNull::~ChunkNull()
{
}

//------------------------------------------------------------------------------
unsigned short ChunkNull::getId()
{
        return NULL;
}

//------------------------------------------------------------------------------
unsigned int ChunkNull::getLength()
{
        return NULL;
}

//------------------------------------------------------------------------------
void ChunkNull::getData(void *data)
{
	file->seekg(length-6);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkMain                                   */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkMain::ChunkMain(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chMain;
}

//------------------------------------------------------------------------------
ChunkMain::~ChunkMain()
{
}

//------------------------------------------------------------------------------
void ChunkMain::getData(void *data)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkEdit                                   */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkEdit::ChunkEdit(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chEdit;
}

//------------------------------------------------------------------------------
ChunkEdit::~ChunkEdit()
{
}

//------------------------------------------------------------------------------
void ChunkEdit::getData(void *data)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkObject                                 */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkObject::ChunkObject(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chObject;
}

//------------------------------------------------------------------------------
ChunkObject::~ChunkObject()
{
}

//------------------------------------------------------------------------------
void ChunkObject::getData(void *data)
{
        Mesh *mesh = (Mesh*)data;

        int i = 1;

        unsigned char l_char;

        do
        {
             file->read((char*)&l_char, sizeof(l_char));

             mesh->name+=l_char;

             i++;
        }while(l_char != '\0' && i<20);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkTriMesh                                */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkTriMesh::ChunkTriMesh(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chTriMesh;
}

//------------------------------------------------------------------------------
ChunkTriMesh::~ChunkTriMesh()
{
}

//------------------------------------------------------------------------------
void ChunkTriMesh::getData(void *data)
{

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkVertex                                 */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkVertex::ChunkVertex(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chVertex;
}

//------------------------------------------------------------------------------
ChunkVertex::~ChunkVertex()
{
}

//------------------------------------------------------------------------------
void ChunkVertex::getData(void *data)
{
        unsigned short vertex_count;

        Mesh *mesh = (Mesh*)data;

        file->read((char*)&vertex_count, sizeof(vertex_count));

        mesh->setVertexCount(vertex_count);

        for (int i = 0; i < vertex_count; i++)
        {
                file->read((char*)&(mesh->getVertex(i).x), sizeof(float));
                file->read((char*)&(mesh->getVertex(i).y), sizeof(float));
                file->read((char*)&(mesh->getVertex(i).z), sizeof(float));
        }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkPolygon                                */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkPolygon::ChunkPolygon(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chPolygon;
}

//------------------------------------------------------------------------------
ChunkPolygon::~ChunkPolygon()
{
}

//------------------------------------------------------------------------------
void ChunkPolygon::getData(void *data)
{
        unsigned short face_flags;
        unsigned short polygon_count;

        Mesh *mesh = (Mesh*)data;

        file->read((char*)&polygon_count, sizeof (unsigned short));

        mesh->setPolygonCount(polygon_count);

        for (int i=0; i<polygon_count; i++)
        {
                file->read((char*)&(mesh->getPolygon(i).a), sizeof (unsigned short));
                file->read((char*)&(mesh->getPolygon(i).b), sizeof (unsigned short));
                file->read((char*)&(mesh->getPolygon(i).c), sizeof (unsigned short));
                file->read((char*)&face_flags, sizeof (unsigned short));
        }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkMapCoord                               */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkMapCoord::ChunkMapCoord(fstream *file) : Chunk(file)
{
        id = ChunkCreator::chMapCoord;
}

//------------------------------------------------------------------------------
ChunkMapCoord::~ChunkMapCoord()
{
}

//------------------------------------------------------------------------------
void ChunkMapCoord::getData(void *data)
{
        Mesh *mesh = (Mesh*)data;

        unsigned short mapcoord_count;

        file->read((char*)&mapcoord_count, sizeof(unsigned short));

        for (int i = 0; i < mapcoord_count; i++)
        {
                file->read((char*)&(mesh->getMapcoord(i).u), sizeof(float));
                file->read((char*)&(mesh->getMapcoord(i).v), sizeof(float));
        }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkScale                                  */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkScale::ChunkScale(fstream *file) : Chunk(file)
{
}

//------------------------------------------------------------------------------
void ChunkScale::getData(void *data)
{
        Mesh *mesh = (Mesh*)data;

        file->read((char*)&mesh->scale, sizeof(float));
}

//--------------------------------ChunkViewportSize-----------------------------
ChunkViewportSize::ChunkViewportSize(fstream *file) : Chunk(file)
{
}

void ChunkViewportSize::getData(void *data)
{
        file->read((char*)&data, sizeof(short));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                ChunkCreator                                */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ChunkCreator::ChunkCreator()
{
}

//------------------------------------------------------------------------------
ChunkCreator::~ChunkCreator()
{
}

//------------------------------------------------------------------------------
Chunk* ChunkCreator::CreateChunk(fstream *file)
{
        unsigned short chunk_id;
        
        file->read((char*)&chunk_id, sizeof(chunk_id));

        switch(chunk_id)
        {
                case chMain : return new ChunkMain(file);
                case chEdit : return new ChunkEdit(file);
                case chObject   : return new ChunkObject(file);
                case chTriMesh  : return new ChunkTriMesh(file);
                case chVertex   : return new ChunkVertex(file);
                case chPolygon  : return new ChunkPolygon(file);
                case chMapCoord : return new ChunkMapCoord(file);
                case chScale    : return new ChunkScale(file);
                default: return new ChunkNull(file);
        }
}

//------------------------------------------------------------------------------
Chunk* ChunkCreator::CreateChunk(fstream *file, unsigned short id, void *data)
{
	Chunk *chunk = NULL;
	
	unsigned short chunk_id;
	
	long int pos = file->tellg();
	
	file->seekg(0);
	
	while( !file->eof() )
	{
		file->read((char*)&chunk_id, sizeof(chunk_id));
		
		if( chunk_id == id )
		{
			switch(chunk_id)
			{
				case chMain : chunk = new ChunkMain(file); chunk->getData(data); break;
				case chEdit : chunk = new ChunkEdit(file); chunk->getData(data); break;
				case chObject   : chunk = new ChunkObject(file);   chunk->getData(data); break;
				case chTriMesh  : chunk = new ChunkTriMesh(file);  chunk->getData(data); break;
				case chVertex   : chunk = new ChunkVertex(file);   chunk->getData(data); break;
				case chPolygon  : chunk = new ChunkPolygon(file);  chunk->getData(data); break;
				case chMapCoord : chunk = new ChunkMapCoord(file); chunk->getData(data); break;
                default: chunk = new ChunkNull(file);break;
			}
		}
	}
	file->seekg(pos);

    return chunk;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                File3DS                                     */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
File3DS::File3DS(string filename, Mesh *mesh)  
{
	this->filename = filename;

    this->mesh = mesh;
}

//------------------------------------------------------------------------------
File3DS::~File3DS()
{
}

//------------------------------------------------------------------------------
bool File3DS::open()
{
	file->open(filename.c_str(), ios::in);

	if( file )isOpened = true;
	else isOpened = false;

    return isOpened;
}

//------------------------------------------------------------------------------
void File3DS::read()
{
    Chunk *chunk;
    ChunkCreator *creator;

    if( mesh == NULL )return;

    if( !isOpened )return;

    creator = new ChunkCreator();

	while( !file->eof() )
	{
                chunk = creator->CreateChunk(file);

                chunk->getData(mesh);

                delete chunk;
	}
    mesh->PrepareDraw();

    delete creator;
}

//------------------------------------------------------------------------------
void File3DS::write()       //пока не использовать
{
    Chunk *chunk;
    ChunkCreator *creator;

    if( mesh == NULL )return;

    if( isOpened )return;

    creator = new ChunkCreator();

	while( !file->eof() )
	{
                chunk = creator->CreateChunk(file);

                chunk->setData(mesh);

                delete chunk;
	}

    delete creator;
}

//------------------------------------------------------------------------------
void File3DS::close()
{
	file->close();
}

//------------------------------------------------------------------------------
Mesh* File3DS::getMesh()
{
	return mesh;
}

//------------------------------------------------------------------------------
void File3DS::setMesh(Mesh *mesh)
{
	this->mesh = mesh;
}

