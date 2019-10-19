#pragma once

#include <cmath>
#include "Macros.h"

#define RED   1
#define GREEN 2
#define BLUE  3

#define FILL_RED   1
#define FILL_GREEN 2
#define FILL_BLUE  3

#define FILL_CYAN    4
#define FILL_MAGENTA 5
#define FILL_YELLOW  6

#define FILL_HUE   7
#define FILL_SAT   8
#define FILL_VALUE 9


//------------------------------------------------------------------------------
class DLLExport ColorFunc
{
public:
	static double Min(double value1, double value2);
	static double Min(double value1, double value2, double value3);

	static double Max(double value1, double value2);
	static double Max(double value1, double value2, double value3);
};
//------------------------------------------------------------------------------
class DLLExport ColorCMYK
{                             
public:
        double cyan, magenta, yellow, black;
        ColorCMYK();        
        ColorCMYK(double c, double m, double y, double k);
};

//------------------------------------------------------------------------------
class DLLExport ColorXYZ
{
public:
        double x,y,z;
        ColorXYZ();
        ColorXYZ(double x, double y, double z);
};

//------------------------------------------------------------------------------
class DLLExport ColorHSV
{
public:
        double hue, sat, value;
        ColorHSV();
        ColorHSV(double h, double s, double v);
};

//------------------------------------------------------------------------------
class DLLExport ColorHSL
{
public:
        double hue, sat, lightness;
        ColorHSL();
        ColorHSL(double h, double s, double l);
};

//------------------------------------------------------------------------------
class DLLExport ColorLAB
{
public:
        double l, a, b;
        ColorLAB();
        ColorLAB(double l, double a, double b);
};

//------------------------------------------------------------------------------
class DLLExport ColorLMS
{
public:
        double l,m,s;
        ColorLMS();
        ColorLMS(double l, double m, double s);
};

//------------------------------------------------------------------------------
class DLLExport ColorYUV
{
public:
        double y,u,v;
        ColorYUV();
        ColorYUV(double y, double u, double v);
};

//------------------------------------------------------------------------------
class DLLExport ColorBGR
{
public:
	double blue;
	double green;
	double red;
	ColorBGR();
	ColorBGR(double b, double g, double r);
};

//------------------------------------------------------------------------------
class DLLExport ColorRGB
{
public:
        double red;
        double green;
        double blue;
        double alpha;
        ColorRGB();
        ColorRGB(const int type);
        ColorRGB(double value);
        ColorRGB(double red, double green, double blue);
        ColorRGB(double red, double green, double blue, double alpha);        
        ColorRGB(const ColorRGB &ColorRGB);
        virtual ~ColorRGB();

        operator int();
		operator float();
		operator double();
        operator double*();
		operator float*();

        ColorRGB& operator=(const ColorRGB& ColorRGB);
        ColorRGB& operator=(double value);

        bool operator==(ColorRGB &ColorRGB);
        bool operator!=(ColorRGB &ColorRGB);

        static ColorRGB getColor(int type);
        static COLORREF getColorRef(int type);
        static COLORREF getColorRef(ColorRGB &color);
        
        //CMYK
        static ColorCMYK RGBtoCMYK(ColorRGB &color); //do
        static ColorRGB  CMYKtoRGB(ColorCMYK &color);//do

        //XYZ
        static ColorXYZ RGBtoXYZ(ColorRGB &color);   //do
        static ColorRGB XYZtoRGB(ColorXYZ &color);  //do

        //HSV
        static ColorHSV RGBtoHSV(ColorRGB &color);   //do
        static ColorRGB HSVtoRGB(ColorHSV &color);   //do

        //HSL
        static ColorHSL RGBtoHSL(ColorRGB &color);   //do
        static ColorRGB HSLtoRGB(ColorHSL &color);   //do

        //LAB
        static ColorLAB RGBtoLAB(ColorRGB &color);
        static ColorRGB LABtoRGB(ColorLAB &color);

        //LMS
        static ColorLMS RGBtoLMS(ColorRGB &color);   //do
        static ColorRGB LMStoRGB(ColorLMS &color);   //do

        //YUV
        static ColorYUV RGBtoYUV(ColorRGB &color);   //do
        static ColorRGB YUVtoRGB(ColorYUV &color);   //do

        //Grayscale
        static double RGBtoGrayscale(ColorRGB &color); //do

		//BGR
		static ColorRGB BGRtoRGB(ColorBGR &color);
};

//------------------------------------------------------------------------------
class DLLExport ColorRed : public ColorRGB
{
public:
        ColorRed(){ red = 1; green = 0; blue = 0; }
};

//------------------------------------------------------------------------------
class DLLExport ColorGreen : public ColorRGB
{
public:
        ColorGreen(){ red = 0; green = 1; blue = 0; }
};

//------------------------------------------------------------------------------
class DLLExport ColorBlue : public ColorRGB
{
public:
        ColorBlue(){ red = 0; green = 0; blue = 1; }
};

//------------------------------------------------------------------------------
class DLLExport VColorXYZ
{
public:
        ColorRGB color_x;
        ColorRGB color_y;
        ColorRGB color_z;
        VColorXYZ();
        VColorXYZ(ColorRGB *color_x, ColorRGB *color_y, ColorRGB *color_z);
        VColorXYZ(const VColorXYZ &vcolor);

        VColorXYZ& operator=(const VColorXYZ &vcolor);
        VColorXYZ& operator=(const ColorRGB &color);
        VColorXYZ& operator=(double value);

        bool operator==(VColorXYZ &vcolor);
        bool operator!=(VColorXYZ &vcolor);
};

//------------------------------------------------------------------------------
class DLLExport VColor
{
protected:
	int size;
	ColorRGB *colors;

public:
	VColor();
	VColor(int size);
	VColor(const VColor &vc);
	virtual ~VColor();

    VColor& operator=(const VColor &vc);
    VColor& operator=(const ColorRGB &c);
    VColor& operator=(double value);

    bool operator==(VColor &vc);
    bool operator!=(VColor &vc);

	void getColor(int index);
	int  getSize();

	void setColor(int index, ColorRGB *color);
	void setSize(int newSize);
};