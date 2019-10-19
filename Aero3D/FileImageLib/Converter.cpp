#include "StdAfx.h"
#include "Converter.h"

//-------------------------------------------------------------------------------------------------------------
Converter::Converter(void)
{
}

//-------------------------------------------------------------------------------------------------------------
Converter::~Converter(void)
{
}

//-------------------------------------------------------------------------------------------------------------
ImageConverter::ImageConverter(void)
{
}

//-------------------------------------------------------------------------------------------------------------
ImageConverter::~ImageConverter(void)
{
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::convert(int type)
{
}

//-------------------------------------------------------------------------------------------------------------
Image* ImageConverter::getImage()
{
	return image;
}

//-------------------------------------------------------------------------------------------------------------
unsigned char* ImageConverter::getPixels()
{
	return pixels;
}

//-------------------------------------------------------------------------------------------------------------
int ImageConverter::getBitsPerPixel()
{
	return this->bitsPerPixel;
}

//-------------------------------------------------------------------------------------------------------------
int ImageConverter::getBytesPerLine()
{
	return this->bytesPerLine;
}

//-------------------------------------------------------------------------------------------------------------
int ImageConverter::getNumBitPlanes()
{
	return this->numBitPlanes;
}

//-------------------------------------------------------------------------------------------------------------
unsigned char** ImageConverter::getPalette()
{
	return palette;
}

//-------------------------------------------------------------------------------------------------------------
bool ImageConverter::getPaletteFlag()
{
	return paletteFlag;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setImage(Image *image)
{
	this->image = image;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setPixels(unsigned char *pixels)
{
	this->pixels = pixels;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setBitsPerPixel(int bitsPerPixel)
{
	this->bitsPerPixel = bitsPerPixel;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setBytesPerLine(int bytesPerLine)
{
	this->bytesPerLine = bytesPerLine;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setNumBitPlanes(int numBitPlanes)
{
	this->numBitPlanes = numBitPlanes;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setPalette(unsigned char **palette)
{
	this->palette = palette;
}

//-------------------------------------------------------------------------------------------------------------
void ImageConverter::setPaletteFlag(bool paletteFlag)
{
	this->paletteFlag = paletteFlag;
}

//-------------------------------------------------------------------------------------------------------------
//-----------------------------------------------BMPImageConverter---------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void BMPImageConverter::convert(int type)
{
	switch(type)
	{
		case BMP8: BMP8ToRGB(image, pixels, palette, bitsPerPixel); break;
		case BMP24: BMP24ToRGB(image, pixels, bitsPerPixel); break;		
	}
}

//-------------------------------------------------------------------------------------------------------------
void BMPImageConverter::BMP8ToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bitsPerPixel)
{
	int offset = image->getWidth() * bitsPerPixel / 8;

	for(int y = 0; y < image->getHeight(); y++)

		for(int x = 0; x < image->getWidth(); x++)
		{
			image->data[x*3 + 0][y] = palette[pixels[x + y*offset]][0];
            image->data[x*3 + 1][y] = palette[pixels[x + y*offset]][1];
            image->data[x*3 + 2][y] = palette[pixels[x + y*offset]][2];
		}
}

//-------------------------------------------------------------------------------------------------------------
void BMPImageConverter::BMP24ToRGB(Image *image, unsigned char *pixels, int bitsPerPixel)
{	
	int offset = image->getWidth() * bitsPerPixel / 8;

	for(int y = 0; y < image->getHeight(); y++)

		for(int x = 0; x < image->getWidth(); x++)
	    {
			image->data[x*bitsPerPixel/8 + 0][y] = pixels[x*bitsPerPixel / 8 + 0 + y*offset];
            image->data[x*bitsPerPixel/8 + 1][y] = pixels[x*bitsPerPixel / 8 + 1 + y*offset];
            image->data[x*bitsPerPixel/8 + 2][y] = pixels[x*bitsPerPixel / 8 + 2 + y*offset];
			if( bitsPerPixel == 32 )image->data[x*bitsPerPixel / 8 + 3][y] = pixels[x*bitsPerPixel / 8 + 3 + y*offset];
		}	
}

//-------------------------------------------------------------------------------------------------------------
//-----------------------------------------------PCXImageConverter---------------------------------------------
//-------------------------------------------------------------------------------------------------------------//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::convert(int type)
{
	switch(type)
	{
		case PCX_Mono: PCXMonoToRGB(image, pixels, bytesPerLine); break;
		case PCX_CGA: PCXCgaToRGB(image, pixels, palette); break;
		case PCX_EGA: PCXEgaToRGB(image, pixels, palette, bytesPerLine); break;
		case PCX_VGA: PCXVgaToRGB(image, pixels, palette, bytesPerLine, paletteFlag); break;
		case PCX_EVGA: PCXEvgaToRGB(image, pixels, palette, bytesPerLine, numBitPlanes, paletteFlag); break;
	}
}

//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::PCXMonoToRGB(Image *image, unsigned char *pixels, int bytesPerLine)
{
	for(int y = 0; y < image->getHeight(); y++)

		for(int x = 0; x < bytesPerLine; x++)
			
			image->data[x][y] = pixels[x + y*bytesPerLine];
}

//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::PCXCgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette)
{
	for(int i = 0; i< 48; i++)
    {
		BYTE CgaBackgroundColor  = palette[0][0] >> 4;
        BYTE CgaColorBurstEnable = (palette[0][3] & 0x80) >> 7;
        BYTE CgaPaletteValue     = (palette[0][3] & 0x40) >> 6;
        BYTE CgaIntensityValue   = (palette[0][3] & 0x20) >> 5;
    }
}

//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::PCXEgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine)
{
	for(int y = 0; y < image->getHeight(); y++)
                                        
		for(int x = 0; x < bytesPerLine; x++)
		{
			image->data[x*3 + 0][y] = palette[pixels[x + y*bytesPerLine]][0] >> 6;
			image->data[x*3 + 1][y] = palette[pixels[x + y*bytesPerLine]][1] >> 6;
			image->data[x*3 + 2][y] = palette[pixels[x + y*bytesPerLine]][2] >> 6;
		}
}

//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::PCXVgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine, bool paletteFlag)
{
	if( paletteFlag ) //has 256-palette  ;no work
    {
		for(int y = 0; y < image->getHeight(); y++)
		                                
			for(int x = 0; x < bytesPerLine; x++)
			{
				image->data[x*3 + 0][y] = palette[pixels[x + y*bytesPerLine]][2];
				image->data[x*3 + 1][y] = palette[pixels[x + y*bytesPerLine]][1];
				image->data[x*3 + 2][y] = palette[pixels[x + y*bytesPerLine]][0];
			}
		
	}
	else     //no work
	{
		for(int y = 0; y < image->getHeight(); y++)
	
			for(int x = 0; x < image->getWidth(); x++)
			{
				image->data[x*3 + 0][y] = pixels[x + y*bytesPerLine] >> 6;
				image->data[x*3 + 1][y] = pixels[x + y*bytesPerLine] >> 6;
				image->data[x*3 + 2][y] = pixels[x + y*bytesPerLine] >> 6;
			}

	}
}

//-------------------------------------------------------------------------------------------------------------
void PCXImageConverter::PCXEvgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine, int numBitPlanes, bool paletteFlag)
{
	if( paletteFlag ) //has 256-palette  ;work
    {                    
		for(int y = 0; y < image->getHeight(); y++)
	
			for(int x = 0; x < bytesPerLine; x++)
			{
				image->data[x*3 + 0][y] = palette[pixels[x + y*bytesPerLine]][2];
				image->data[x*3 + 1][y] = palette[pixels[x + y*bytesPerLine]][1];
				image->data[x*3 + 2][y] = palette[pixels[x + y*bytesPerLine]][0];
			}
	
	}
	else  //no 256-palette  ;no work
	{   
		for(int y = 0; y < image->getHeight(); y++)
	
			for(int x = 0; x < bytesPerLine; x++)
			{
				image->data[x*3 + 0][y] = pixels[x*numBitPlanes + y*numBitPlanes*bytesPerLine + 0];
				image->data[x*3 + 1][y] = pixels[x*numBitPlanes + y*numBitPlanes*bytesPerLine + 1];
				image->data[x*3 + 2][y] = pixels[x*numBitPlanes + y*numBitPlanes*bytesPerLine + 2];
			}

	}
}

//-------------------------------------------------------------------------------------------------------------
//-----------------------------------------------TGAImageConverter---------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void TGAImageConverter::convert(int type)
{
	switch(type)
	{
		case TGA_INDEX: TGAIndexToRGB(image, pixels, palette, bitsPerPixel); break;
		case TGA_RGB: TGARgbToRGB(image, pixels, bitsPerPixel); break;
	}
}

//-------------------------------------------------------------------------------------------------------------
void TGAImageConverter::TGAIndexToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bitsPerPixel)
{
	int offset = image->getWidth() * (bitsPerPixel / 8 );

	for(int y = 0; y < image->getHeight(); y++)

		for(int x = 0; x < image->getWidth(); x++)
		{
			image->data[x*3 + 0][y] = palette[pixels[x + y*offset]][0];
            image->data[x*3 + 1][y] = palette[pixels[x + y*offset]][1];
            image->data[x*3 + 2][y] = palette[pixels[x + y*offset]][2];
		}
}

//-------------------------------------------------------------------------------------------------------------
void TGAImageConverter::TGARgbToRGB(Image *image, unsigned char *pixels, int bitsPerPixel)
{
	int offset = image->getWidth() * (bitsPerPixel / 8 );

	for(int y = 0; y < image->getHeight(); y++)

		for(int x = 0; x < image->getWidth(); x++)
		{
			image->data[x*3 + 0][y] = pixels[x*3 + 0 + y*offset];
            image->data[x*3 + 1][y] = pixels[x*3 + 1 + y*offset];
            image->data[x*3 + 2][y] = pixels[x*3 + 2 + y*offset];
		}
}