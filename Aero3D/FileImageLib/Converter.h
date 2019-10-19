#pragma once

#include "Macros.h"
#include "Image.h"
#include "FileImage.h"

//-------------------------------------------Converter---------------------------------------------------------
class DLLExport Converter
{
public:
	Converter(void);
	virtual ~Converter(void);
	virtual void convert(int type) = 0;
};

//-------------------------------------------ImageConverter----------------------------------------------------
class DLLExport ImageConverter : public Converter
{
protected:
	Image *image;
	unsigned char *pixels;
	unsigned char **palette;
	int bitsPerPixel;
	int bytesPerLine;
	int numBitPlanes;
	bool paletteFlag;

public:
	ImageConverter();
	virtual ~ImageConverter();
	virtual void convert(int type);

	virtual Image* getImage();
	virtual unsigned char* getPixels();
	virtual int getBitsPerPixel();
	virtual int getBytesPerLine();
	virtual int getNumBitPlanes();
	virtual unsigned char** getPalette();
	virtual bool getPaletteFlag();

	virtual void setImage(Image *image);
	virtual void setPixels(unsigned char *pixels);
	virtual void setBitsPerPixel(int bitsPerPixel);
	virtual void setBytesPerLine(int bytesPerLine);
	virtual void setNumBitPlanes(int numBitPlanes);
	virtual void setPalette(unsigned char **palette);
	virtual void setPaletteFlag(bool paletteFlag);
};

//-------------------------------------------BMPImageConverter-------------------------------------------------
class DLLExport BMPImageConverter : public ImageConverter
{
public:
	virtual void convert(int type);
	static void BMP8ToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bitsPerPixel);
	static void BMP24ToRGB(Image *image, unsigned char *pixels, int bitsPerPixel);
};

//-------------------------------------------PCXImageConverter-------------------------------------------------
class DLLExport PCXImageConverter : public ImageConverter
{
public:
	virtual void convert(int type);
	static void PCXMonoToRGB(Image *image, unsigned char *pixels, int bytesPerLine);
	static void PCXCgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette);
	static void PCXEgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine);
	static void PCXVgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine, bool paletteFlag);
	static void PCXEvgaToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bytesPerLine, int numBitPlanes, bool paletteFlag);
};

//-------------------------------------------TGAImageConverter-------------------------------------------------
class DLLExport TGAImageConverter : public ImageConverter
{
public:
	virtual void convert(int type);
	static void TGAIndexToRGB(Image *image, unsigned char *pixels, unsigned char **palette, int bitsPerPixel);
	static void TGARgbToRGB(Image *image, unsigned char *pixels, int bitsPerPixel);
};
