#pragma once

#include <string>
#include <fstream>
#include "Macros.h"
#include "Image.h"
#include "Compressor.h"
#include "Converter.h"

using namespace std;

#define NONAME 0
#define BMP 1
#define BMP8 11
#define BMP24 12
#define BMP32 13
#define BMP_RLE 14
#define GIF 2
#define JPG 3
#define PCX 4
#define PCX_Mono 41
#define PCX_CGA 42
#define PCX_EGA 43
#define PCX_VGA 44
#define PCX_EVGA 45
#define PNG 5
#define TGA 6
#define TGA_INDEX 61
#define TGA_RGB 62
#define TGA_RLE_INDEX 63
#define	TGA_RLE_RGB 64 	

//-----------------------------------------------FileImage-----------------------------------------------------
class DLLExport FileImage
{
protected:
	Image *image;
	int    imageType;
	bool   hasPaletteFlag;
	string  filename;
	fstream file;	
		
	virtual void readHeader() = 0;
	virtual void readPalette() = 0;
	virtual void readData() = 0;

public:
	FileImage(void);
	FileImage(const string filename);
	virtual ~FileImage(void);

	virtual void flipImage(unsigned char *data, int width, int height, int bits);
	virtual bool hasPalette();
	virtual Image* getImage();
	virtual int    getImageType();
	virtual string getFilename();

	virtual void setImage(Image *image);
	virtual void setImageType(int type);
	virtual void setFilename(const string filename);	

    virtual void open();
	virtual void close();

	virtual void read() = 0;
	virtual void write() = 0;	
};

//-----------------------------------------------FileImageFactory----------------------------------------------
class DLLExport FileImageFactory
{
protected:
public:
	FileImageFactory(void);
	virtual ~FileImageFactory(void);
	
	Image *CreateImage(int type, const string filename);
	FileImage *CreateFileImage(int type, const string filename);	
};

//-----------------------------------------------Bitmap--------------------------------------------------------
class DLLExport BMPFileHeader
{
public:
        unsigned short sign;
        unsigned int   size;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int location;
};

//------------------------------------------------------------------------------
class DLLExport BMPInfoHeader
{
public:
        //---file info header
        unsigned int headerSize;
        unsigned int width;
        unsigned int height;
        unsigned short planes;     //always = 1
        unsigned short bits;       //1,2,4,8,16,24,32
        unsigned int compress;     //0 - no compress; 1 - 8-bit RLE;  2 -  4-bit RLE; 3
        unsigned int num;
        unsigned int horizontal;
        unsigned int vertical;
        unsigned int numColors;
        unsigned int numIColors;
};

//------------------------------------------------------------------------------
class DLLExport BMPHeader
{
public:
	BMPFileHeader fileHeader;
	BMPInfoHeader infoHeader;
};

//------------------------------------------------------------------------------
class DLLExport FileBitmap : public FileImage
{
protected:
	BMPHeader header;	
	unsigned char palette[256][3];
		
	virtual void readHeader();
	virtual void readPalette();
	virtual void readData();

public:
	FileBitmap(void);
	FileBitmap(const string filename);
	virtual ~FileBitmap(void);

	virtual bool hasPalette();
	virtual int  getImageType();	
	
	virtual void read();
	virtual void write();
};

//-------------------------------------------------------------------------------------------------------------
class DLLExport GIFHeader
{
public:
	unsigned char  Sign[3];
    unsigned char  Version[3];
    unsigned short ScreenWidth, ScreenHeight;
    unsigned char  Packed;
    unsigned char  BackgroundColor;
    unsigned char  AspectRatio;
};

//---------------------------------------------
class DLLExport FileGIF : public FileImage
{
protected:
	GIFHeader header;
	unsigned char palette[256][3];

    virtual void readHeader();
	virtual void readPalette();
    virtual void readData();

public:
	FileGIF();
	FileGIF(const string filename);
	virtual ~FileGIF();
	virtual void read();
	virtual void write();
};

//-------------------------------------------------------------------------------------------------------------
class DLLExport JPGHeader
{
};

class DLLExport FileJPG : public FileImage
{
protected:
	JPGHeader header;
	unsigned char palette[256][3];

	virtual void readHeader();
	virtual void readPalette();
	virtual void readData();

public:
	FileJPG();
	FileJPG(const string filename);
	virtual ~FileJPG();
	virtual void read();
	virtual void write();
};

//-------------------------------------------------------------------------------------------------------------
class DLLExport PCXHeader
{
public:
        unsigned char  Manuf;
        unsigned char  Version;
        unsigned char  Encoding;
        unsigned char  BitsPerPixel;
        unsigned short x1,y1,x2,y2;
        unsigned short HorzRes, VertRes;
        unsigned char  Palette[16][3];
        unsigned char  Reserved1;
        unsigned char  NumBitPlanes;
        unsigned short BytesPerLine;
        unsigned short PaletteType;
        unsigned short HorzScreenSize, VertScreenSize;
        unsigned char  Reserved2[54];
};

//--------------------------------------------------------
class DLLExport FilePCX : public FileImage
{
protected:
	PCXHeader header; //заголовок изображения
	unsigned char palette[256][3];	

    virtual void readHeader();
    virtual void readPalette();
	virtual void readData();	

public:
	FilePCX();
	FilePCX(const string filename);
	virtual ~FilePCX();

	virtual int getImageType();

	virtual void read();
	virtual void write();
};

//-------------------------------------------------------------------------------------------------------------
class DLLExport FilePNG : public FileImage
{
protected:   
 	virtual void readHeader();
	virtual void readPalette();
	virtual void readData();	

public:
	FilePNG();
	FilePNG(const string filename);
	virtual ~FilePNG();
	virtual void read();
	virtual void write();
};

//-------------------------------------------------------------------------------------------------------------
class DLLExport TGAType
{
public:
	unsigned char  v0;
	unsigned char  type;
	unsigned char  encoding;
};

class DLLExport TGAPaletteInfo
{
public:
	unsigned char start;
	unsigned char end;
};

class DLLExport TGACoord
{
public:
	unsigned char x1;
	unsigned char x2;
	unsigned char y1;
	unsigned char y2;
};

class DLLExport TGAHeader
{
public:
	TGAType		   imageType;
	TGAPaletteInfo paletteInfo;
	TGACoord	   coord;
	unsigned char  bitsPerPixel;
};

class DLLExport FileTGA : public FileImage
{
protected:
	TGAHeader header;
	unsigned char palette[256][3];
	
    virtual bool hasPalette();
	virtual int  getImageType();
	

	virtual void readHeader();
	virtual void readPalette();
    virtual void readData();		
public:
	FileTGA();
	FileTGA(const string filename);
	virtual ~FileTGA();
	virtual void read();
	virtual void write();
};