#include "StdAfx.h"
#include "Compressor.h"

//-------------------------------------------------------------------------------------------------------------
Compressor::Compressor(void)
{
}

//-------------------------------------------------------------------------------------------------------------
Compressor::~Compressor(void)
{
}

//-------------------------------------------------------------------------------------------------------------
//-----------------------------------------------ImageCompressor-----------------------------------------------
//-------------------------------------------------------------------------------------------------------------
ImageCompressor::ImageCompressor(void)
{
}

ImageCompressor::ImageCompressor(unsigned char *data, int dataSize)
{
	setData(data, dataSize);
}

//-------------------------------------------------------------------------------------------------------------
ImageCompressor::~ImageCompressor(void)
{
}


//-------------------------------------------------------------------------------------------------------------
int ImageCompressor::getPixelSize()
{
	return pixelSize;
}

//-------------------------------------------------------------------------------------------------------------
unsigned char* ImageCompressor::getData()
{
	return data;
}

//-------------------------------------------------------------------------------------------------------------
int ImageCompressor::getDataSize()
{
	return dataSize;
}

//-------------------------------------------------------------------------------------------------------------
void ImageCompressor::setPixelSize(int size)
{
	pixelSize = size;
}

//-------------------------------------------------------------------------------------------------------------
void ImageCompressor::setData(unsigned char *data, int size)
{
	this->dataSize = size;

	this->data = new unsigned char[size];

	for(int i = 0; i < size; i++)this->data[i] = data[i];
}
//-------------------------------------------------------------------------------------------------------------
//-----------------------------------------------RLEImageCompressor--------------------------------------------
//-------------------------------------------------------------------------------------------------------------
RLEImageCompressor::RLEImageCompressor(void)
{
}

//-------------------------------------------------------------------------------------------------------------
RLEImageCompressor::RLEImageCompressor(unsigned char *data, int dataSize) : ImageCompressor(data, dataSize)
{
}

//-------------------------------------------------------------------------------------------------------------
RLEImageCompressor::~RLEImageCompressor(void)
{
}

//-------------------------------------------------------------------------------------------------------------
void RLEImageCompressor::compress(unsigned char *compressData)
{
}

//-------------------------------------------------------------------------------------------------------------
void RLEImageCompressor::decompress(unsigned char *decompressData)
{
	int i;
	int index;
	int length;
		
	decompressData = new unsigned char[dataSize];

	i = 0;

	index = 0;

	while( index < dataSize )
	{
		if( data[i] & 0x80)
		{
			length = data[i]-127;

			i++;

			for(int j = 0; j < length; j++)
			{
				decompressData[index] = data[i];

				index++;				
			}

		}
		else
		{
			i++;

			decompressData[index] = data[i];

			index++;			
		}
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------
void RLEImageCompressor::decompress(unsigned char *data, unsigned char *decompressData, int size)
{
	int i;
	int index;
	int length;
		
	decompressData = new unsigned char[size];

	i = 0;

	index = 0;

	while( index < size )
	{
		if( data[i] & 0x80)
		{
			length = data[i]-127;

			i++;

			for(int j = 0; j < length; j++)
			{
				decompressData[index] = data[i];

				index++;				
			}

		}
		else
		{
			i++;

			decompressData[index] = data[i];

			index++;			
		}
		i++;
	}
}