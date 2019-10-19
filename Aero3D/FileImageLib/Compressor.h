#pragma once

#include "Macros.h"

#define OP_NO 0
#define OP_COMPRESS 1
#define OP_DECOMPRESS 2

//-------------------------------------------------Compressor--------------------------------------------------
class DLLExport Compressor
{
public:
	Compressor();
	virtual ~Compressor();
};

//-----------------------------------------------ImageCompressor-----------------------------------------------
class DLLExport ImageCompressor : Compressor
{
protected:
	int dataSize;
	int pixelSize;
	unsigned char *data;

public:
	ImageCompressor(void);
	ImageCompressor(unsigned char *data, int dataSize);
	virtual ~ImageCompressor(void);

	virtual int getPixelSize();
	virtual unsigned char* getData();
	virtual int getDataSize();

	virtual void setPixelSize(int size);
	virtual void setData(unsigned char *data, int dataSize);
	
	virtual void compress(unsigned char *compressData) = 0;
	virtual void decompress(unsigned char *decompressData) = 0;
	
};

//-----------------------------------------------RLEImageCompressor--------------------------------------------
class DLLExport RLEImageCompressor : public ImageCompressor
{
public:
	RLEImageCompressor();
	RLEImageCompressor(unsigned char *data, int dataSize);
	virtual ~RLEImageCompressor();

	virtual void compress(unsigned char *compressData);
	virtual void decompress(unsigned char *decompressData);
	static  void decompress(unsigned char *data, unsigned char *decompressData, int size);
};
