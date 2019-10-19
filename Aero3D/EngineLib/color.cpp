#include "StdAfx.h"
#include "color.h"

//------------------------------------------------------------------------------
double ColorFunc::Min(double value1, double value2)
{
	return ( (value1 < value2) ? value1 : value2);
}

//------------------------------------------------------------------------------
double ColorFunc::Min(double value1, double value2, double value3)
{
        double min_value;

        if( value1 < value2 )min_value = value1;
        else min_value = value2;

        if( min_value < value3 )return min_value;
        else return value3;
}

//------------------------------------------------------------------------------
double ColorFunc::Max(double value1, double value2)
{
	return ( (value1 > value2) ? value1 : value2);        
}

//------------------------------------------------------------------------------
double ColorFunc::Max(double value1, double value2, double value3)
{
        double max_value;

        if( value1 > value2 )max_value = value1;
        else max_value = value2;

        if( max_value > value3 )return max_value;
        else return value3;
}

//------------------------------------------------------------------------------
//--------------------------------ColorCMYK-------------------------------------
//------------------------------------------------------------------------------
ColorCMYK::ColorCMYK()
{
        cyan = 0;
        magenta = 0;
        yellow  = 0;
        black   = 0;
}

//------------------------------------------------------------------------------
ColorCMYK::ColorCMYK(double c, double m, double y, double k)
{
        cyan = c;
        magenta = m;
        yellow  = y;
        black   = k;
}

//------------------------------------------------------------------------------
//--------------------------------ColorXYZ--------------------------------------
//------------------------------------------------------------------------------
ColorXYZ::ColorXYZ()
{
        x = 0;
        y = 0;
        z = 0;
}

//------------------------------------------------------------------------------
ColorXYZ::ColorXYZ(double x, double y, double z)
{
        this->x = x;
        this->y = y;
        this->z = z;
}

//------------------------------------------------------------------------------
//--------------------------------ColorHSV--------------------------------------
//------------------------------------------------------------------------------
ColorHSV::ColorHSV()
{
        hue = 0;
        sat = 0;
        value = 0;
}

//------------------------------------------------------------------------------
ColorHSV::ColorHSV(double h, double s, double v)
{
        hue = h;
        sat = s;
        value = v;
}


//------------------------------------------------------------------------------
//--------------------------------ColorHSL--------------------------------------
//------------------------------------------------------------------------------
ColorHSL::ColorHSL()
{
        hue = 0;
        sat = 0;
        lightness = 0;
}

//------------------------------------------------------------------------------
ColorHSL::ColorHSL(double h, double s, double l)
{
        hue = h;
        sat = s;
        lightness = l;
}

//------------------------------------------------------------------------------
//--------------------------------ColorLAB--------------------------------------
//------------------------------------------------------------------------------
ColorLAB::ColorLAB()
{
        l = 0;
        a = 0;
        b = 0;
}

//------------------------------------------------------------------------------
ColorLAB::ColorLAB(double l, double a, double b)
{
        this->l = l;
        this->a = a;
        this->b = b;
}

//------------------------------------------------------------------------------
//--------------------------------ColorLMS--------------------------------------
//------------------------------------------------------------------------------
ColorLMS::ColorLMS()
{
        l = 0;
        m = 0;
        s = 0;
}

//------------------------------------------------------------------------------
ColorLMS::ColorLMS(double l, double m, double s)
{
        this->l = l;
        this->m = m;
        this->s = s;
}

//------------------------------------------------------------------------------
//--------------------------------ColorYUV--------------------------------------
//------------------------------------------------------------------------------
ColorYUV::ColorYUV()
{
        y = 0;
        u = 0;
        v = 0;
}

//------------------------------------------------------------------------------
ColorYUV::ColorYUV(double y, double u, double v)
{
        this->y = y;
        this->u = u;
        this->v = v;
}

//------------------------------------------------------------------------------
//---------------------------------ColorBGR-------------------------------------
//------------------------------------------------------------------------------
ColorBGR::ColorBGR()
{
	blue = 0;
	green = 0;
	red = 0;
}

//------------------------------------------------------------------------------
ColorBGR::ColorBGR(double b, double g, double r)
{
	blue = b;
	green = g;
	red = r;
}

//------------------------------------------------------------------------------
//--------------------------------ColorRGB--------------------------------------
//------------------------------------------------------------------------------
ColorRGB::ColorRGB()
{
        red   = 0;
        green = 0;
        blue  = 0;
        alpha = 1;
}

//------------------------------------------------------------------------------
ColorRGB::ColorRGB(const int type)
{
        *this = getColor(type);
}

//------------------------------------------------------------------------------
ColorRGB::ColorRGB(double value)
{
        red   = value;
        green = value;
        blue  = value;
}

//------------------------------------------------------------------------------
ColorRGB::ColorRGB(double red, double green, double blue)
{
        this->red   = red;
        this->green = green;
        this->blue  = blue;
        alpha = 1;
}

//------------------------------------------------------------------------------
ColorRGB::ColorRGB(double red, double green, double blue, double alpha)
{
        this->red   = red;
        this->green = green;
        this->blue  = blue;
        this->alpha = alpha;
}

//------------------------------------------------------------------------------
ColorRGB::ColorRGB(const ColorRGB &color)
{
        red   = color.red;
        green = color.green;
        blue  = color.blue;
        alpha = color.alpha;
}

//------------------------------------------------------------------------------
ColorRGB::~ColorRGB()
{
}

//------------------------------------------------------------------------------
ColorRGB::operator int()
{
        return (int)red + (int)green + (int)blue;
}

//------------------------------------------------------------------------------
ColorRGB::operator float()
{
        return (float)red + (float)green + (float)blue;
}


//------------------------------------------------------------------------------
ColorRGB::operator double()
{
        return red + green + blue;
}

//------------------------------------------------------------------------------
ColorRGB::operator float*()
{
        float *color = new float[4];

        color[0] = (float)red;
        color[1] = (float)green;
        color[2] = (float)blue;
        color[3] = (float)alpha;

        return color;
}

//------------------------------------------------------------------------------
ColorRGB::operator double*()
{
        double *color = new double[4];

        color[0] = red;
        color[1] = green;
        color[2] = blue;
        color[3] = alpha;

        return color;
}

//------------------------------------------------------------------------------
ColorRGB& ColorRGB::operator=(const ColorRGB &color)
{
        red   = color.red;
        green = color.green;
        blue  = color.blue;
        alpha = color.alpha;

        return *this;
}

//------------------------------------------------------------------------------
ColorRGB& ColorRGB::operator=(double value)
{
        red   = value;
        green = value;
        blue  = value;
        
        return *this;
}

//------------------------------------------------------------------------------
bool ColorRGB::operator==(ColorRGB &color)
{
        if( red == color.red && green == color.green && blue == color.blue && alpha == color.alpha)

                return true;

        else return false;
}

//------------------------------------------------------------------------------
bool ColorRGB::operator!=(ColorRGB &color)
{
        if( red != color.red || green != color.green || blue != color.blue || alpha != color.alpha)

                return true;

        else return false;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::getColor(int type)
{
        switch(type)
        {
                case RED   : return ColorRGB(1,0,0);
                case GREEN : return ColorRGB(0,1,0);
                case BLUE  : return ColorRGB(0,0,1);

                default: return ColorRGB(1,0,0);
        }
}

//------------------------------------------------------------------------------
COLORREF ColorRGB::getColorRef(int type)
{
        ColorRGB color = getColor(type);

        return getColorRef(color);
}

//------------------------------------------------------------------------------
COLORREF ColorRGB::getColorRef(ColorRGB &color)
{
        return RGB(color.red, color.green, color.blue);
}

//--------------------------------CMYK------------------------------------------
ColorCMYK ColorRGB::RGBtoCMYK(ColorRGB &color)
{
        ColorCMYK c;

        c.cyan = 255 - color.red;
        c.magenta = 255 - color.green;
        c.yellow  = 255 - color.blue;

		c.black = ColorFunc::Min(c.cyan, c.magenta, c.yellow);

        c.cyan = ColorFunc::Max(0, c.cyan - c.black);
        c.magenta = ColorFunc::Max(0, c.magenta - c.black);
        c.yellow  = ColorFunc::Max(0, c.yellow  - c.black);

        return c;
}

//------------------------------------------------------------------------------
ColorRGB  ColorRGB::CMYKtoRGB(ColorCMYK &color)
{
        ColorRGB c;

        c.red   = 255 - ColorFunc::Min(255, color.cyan + color.black);
        c.green = 255 - ColorFunc::Min(255, color.magenta + color.black);
        c.blue  = 255 - ColorFunc::Min(255, color.yellow  + color.black);

        return c;
}

//--------------------------------XYZ------------------------------------------
ColorXYZ ColorRGB::RGBtoXYZ(ColorRGB &color)
{
        ColorXYZ c;

        c.x = 0.431*color.red + 0.342*color.green + 0.178*color.blue;
        c.y = 0.222*color.red + 0.707*color.green + 0.071*color.blue;
        c.z = 0.020*color.red + 0.130*color.green + 0.939*color.blue;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB  ColorRGB::XYZtoRGB(ColorXYZ &color)
{
        ColorRGB c;

        c.red   =  3.063*color.x - 1.393*color.y - 0.476*color.z;
        c.green = -0.969*color.x + 1.876*color.y + 0.042*color.z;
        c.blue  =  0.068*color.x - 0.229*color.y + 1.069*color.z;

        return c;
}

//--------------------------------HSV-------------------------------------------
ColorHSV ColorRGB::RGBtoHSV(ColorRGB &color)
{
        ColorHSV c;

        double r, g, b;
        double max_v, min_v;

        r = color.red/255;
        g = color.green/255;
        b = color.blue/255;

        max_v = ColorFunc::Max(r, g, b);
        min_v = ColorFunc::Min(r, g, b);

        if( max_v == min_v )c.hue = 0;
        if( max_v == r && g >= b) c.hue = 60 * ((g - b)/(max_v - min_v));
        if( max_v == r && g < b ) c.hue = 60 * ((g - b)/(max_v - min_v)) + 360;
        if( max_v == g ) c.hue = 60 * ((b - r)/(max_v - min_v)) + 120;
        if( max_v == b ) c.hue = 60 * ((r - g)/(max_v - min_v)) + 240;

        if( max_v == 0 )c.sat = 0;
        else c.sat = 1 - min_v/max_v;

        c.value = max_v;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::HSVtoRGB(ColorHSV &color)
{
        ColorRGB c;
        short l;
        double h, s, v, f, p, q, t;

        h = 6.0 * (((double)color.hue)) / (double)360;
        s = (double)color.sat / (double)255;
        v = (double)color.value / (double)255;
        l = (short)floor(h);
        f = h - (double)l;

        p = v * (1.0 - s);
        q = v * (1.0 - s * f);
        t = v * (1.0 - (s * (1.0 - f)));
        switch(l)
        {
                case 0: c.red = v*255;  c.green = t*255;  c.blue = p*255; break;
                case 1: c.red = q*255;  c.green = v*255;  c.blue = p*255; break;
                case 2: c.red = p*255;  c.green = v*255;  c.blue = t*255; break;
                case 3: c.red = p*255;  c.green = q*255;  c.blue = v*255; break;
                case 4: c.red = t*255;  c.green = p*255;  c.blue = v*255; break;
                case 5: c.red = v*255;  c.green = p*255;  c.blue = q*255; break;
        }

        return c;
}

//--------------------------------HSL-------------------------------------------
ColorHSL ColorRGB::RGBtoHSL(ColorRGB &color)
{
        ColorHSL c;

        double r, g, b;
        double max_v, min_v;

        r = color.red/255;
        g = color.green/255;
        b = color.blue/255;

        max_v = ColorFunc::Max(r, g, b);
        min_v = ColorFunc::Min(r, g, b);

        if( max_v == min_v )c.hue = 0;
        if( max_v == r && g >= b) c.hue = 60 * ((g - b)/(max_v - min_v));
        if( max_v == r && g < b ) c.hue = 60 * ((g - b)/(max_v - min_v)) + 360;
        if( max_v == g ) c.hue = 60 * ((b - r)/(max_v - min_v)) + 120;
        if( max_v == b ) c.hue = 60 * ((r - g)/(max_v - min_v)) + 240;

        c.lightness = (max_v + min_v)/2;

        if( c.lightness == 0 || max_v == min_v )c.sat = 0;
        if( c.lightness > 0   && c.lightness <= 0.5 )c.sat = (max_v - min_v)/(max_v + min_v);
        if( c.lightness > 0.5 && c.lightness < 1    )c.sat = (max_v - min_v)/(2 - (max_v + min_v));
        if( c.lightness == 1 )c.sat = 1;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::HSLtoRGB(ColorHSL &color)
{
        ColorRGB c;

        double q, p, h, t_r, t_g, t_b;

        if( color.lightness < 0.5 )q = color.lightness * (1.0 + color.sat);
        if( color.lightness >= 0.5 )q = color.lightness + color.sat -  (color.lightness * color.sat);

        p = 2.0 * color.lightness - q;

        h = color.hue / 360;
        
        t_r = h + (double)1/(double)3;
        t_g = h;
        t_b = h - (double)1/(double)3;

        if( t_r < 0 )t_r = t_r + 1.0;
        if( t_g < 0 )t_g = t_g + 1.0;
        if( t_b < 0 )t_b = t_b + 1.0;

        if( t_r > 1 )t_r = t_r - 1.0;
        if( t_g > 1 )t_g = t_g - 1.0;
        if( t_b > 1 )t_b = t_b - 1.0;

        double v_1_6 = (double)1/(double)6;
        double v_1_2 = (double)1/(double)2;
        double v_2_3 = (double)2/(double)3;

        if( t_r <  v_1_6                )c.red = p + ((q - p) * 6.0 * t_r);
        if( t_r >= v_1_6 && t_r < v_1_2 )c.red = q;
        if( t_r >= v_1_2 && t_r < v_2_3 )c.red = p + ((q - p) * (v_2_3 - t_r) * 6.0);
        if( t_r >  v_2_3                )c.red = p;

        if( t_g <  v_1_6                )c.green = p + ((q - p) * 6.0 * t_r);
        if( t_g >= v_1_6 && t_g < v_1_2 )c.green = q;
        if( t_g >= v_1_2 && t_g < v_2_3 )c.green = p + ((q - p) * (v_2_3 - t_r) * 6.0);
        if( t_g >  v_2_3                )c.green = p;

        if( t_b <  v_1_6                )c.blue = p + ((q - p) * 6.0 * t_r);
        if( t_b >= v_1_6 && t_b < v_1_2 )c.blue = q;
        if( t_b >= v_1_2 && t_b < v_2_3 )c.blue = p + ((q - p) * (v_2_3 - t_r) * 6.0);
        if( t_b >  v_2_3                )c.blue = p;

        return c;
}

//--------------------------------LAB-------------------------------------------
ColorLAB ColorRGB::RGBtoLAB(ColorRGB &color)
{
        ColorLAB c;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::LABtoRGB(ColorLAB &color)
{
        ColorRGB c;

        return c;
}

//--------------------------------LMS-------------------------------------------
ColorLMS ColorRGB::RGBtoLMS(ColorRGB &color)
{
        ColorLMS c;

        c.l = 0.3811*color.red + 0.5783*color.green + 0.0402*color.blue;
        c.m = 0.1967*color.red + 0.7244*color.green + 0.0782*color.blue;
        c.s = 0.0241*color.red + 0.1288*color.green + 0.8444*color.blue;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::LMStoRGB(ColorLMS &color)
{
        ColorRGB c;

        c.red   =  0.0497*color.l - 0.2439*color.m + 1.2045*color.s;
        c.green = -1.2186*color.l + 2.3809*color.m - 0.1624*color.s;
        c.blue  =  4.4679*color.l - 3.5873*color.m + 0.1193*color.s;

        return c;
}

//--------------------------------YUV-------------------------------------------
ColorYUV ColorRGB::RGBtoYUV(ColorRGB &color)
{
        ColorYUV c;

        c.y = color.red *  0.299 + color.green *  0.587 + color.blue * 0.114;
        c.u = color.red * -0.169 + color.green * -0.332 + color.blue * 0.500 + 128;
        c.v = color.red *  0.500 + color.green * -0.419 + color.blue * -0.0813 + 128;

        return c;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::YUVtoRGB(ColorYUV &color)
{
        ColorRGB c;

        c.red   = color.y + (1.4075 * (color.v - 128));
        c.green = color.y - (0.3455 * (color.u - 128) - (0.7169 * (color.v - 128)));
        c.blue  = color.y + (1.7790 * (color.u - 128));

        return c;
}

//--------------------------------Grayscale-------------------------------------
double ColorRGB::RGBtoGrayscale(ColorRGB &color)
{
        return 0.299*color.red + 0.587*color.green + 0.114*color.blue;
}

//------------------------------------------------------------------------------
ColorRGB ColorRGB::BGRtoRGB(ColorBGR &color)
{
	ColorRGB c;

	c.red = color.red;
	c.green = color.green;
	c.blue = color. blue;

	return c;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                              VColorXYZ - Vector Color                        */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
VColorXYZ::VColorXYZ()
{
        color_x = 0;
        color_y = 0;
        color_z = 0;
}

//------------------------------------------------------------------------------
VColorXYZ::VColorXYZ(ColorRGB *color_x, ColorRGB *color_y, ColorRGB *color_z)
{
        this->color_x = *color_x;
        this->color_y = *color_y;
        this->color_z = *color_z;
}

//------------------------------------------------------------------------------
VColorXYZ::VColorXYZ(const VColorXYZ &vcolor)
{
        color_x = vcolor.color_x;
        color_y = vcolor.color_y;
        color_z = vcolor.color_z;
}

//------------------------------------------------------------------------------
VColorXYZ& VColorXYZ::operator=(const VColorXYZ &vcolor)
{
        color_x = vcolor.color_x;
        color_y = vcolor.color_y;
        color_z = vcolor.color_z;

        return *this;
}

//------------------------------------------------------------------------------
VColorXYZ& VColorXYZ::operator=(const ColorRGB &color)
{
        color_x = color;
        color_y = color;
        color_z = color;

        return *this;
}

//------------------------------------------------------------------------------
VColorXYZ& VColorXYZ::operator=(double value)
{
        color_x = value;
        color_y = value;
        color_z = value;

        return *this;
}

//------------------------------------------------------------------------------
bool VColorXYZ::operator==(VColorXYZ &vcolor)
{
        if( color_x == vcolor.color_x && color_y == vcolor.color_y && color_z == vcolor.color_z )

                return true;

        else return false;
}

//------------------------------------------------------------------------------
bool VColorXYZ::operator!=(VColorXYZ &vcolor)
{
        if( color_x != vcolor.color_x || color_y != vcolor.color_y || color_z == vcolor.color_z )

                return true;

        else return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                              VColor - Vector Color                         */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
VColor::VColor()
{
	colors = 0;        
}

//------------------------------------------------------------------------------
VColor::VColor(int size)
{
	colors = new ColorRGB(size);	
}

//------------------------------------------------------------------------------
VColor::VColor(const VColor &vc)
{
	if( colors != NULL )delete[] colors;

	size = vc.size;

	colors = new ColorRGB(size);

	for(int i = 0; i < size; i++)colors[i] = vc.colors[i];
	
}

//------------------------------------------------------------------------------
VColor& VColor::operator=(const VColor &vc)
{
	if( colors != NULL )delete[] colors;

	size = vc.size;

	colors = new ColorRGB(size);

	for(int i = 0; i < size; i++)colors[i] = vc.colors[i];	

	return *this;
}

//------------------------------------------------------------------------------
VColor::~VColor()
{
	if( colors != NULL )delete[] colors;
}

//------------------------------------------------------------------------------
VColor& VColor::operator=(const ColorRGB &c)
{
	if( colors != NULL )
	
		for(int i = 0; i < size; i++)colors[i] = c;	

	return *this;
}

//------------------------------------------------------------------------------
VColor& VColor::operator=(double value)
{
	if( colors != NULL )
	
		for(int i = 0; i < size; i++)colors[i] = value;	

	return *this;
}

//------------------------------------------------------------------------------
bool VColor::operator==(VColor &vc)
{
	if( size != vc.size )return false; 

	for(int i = 0; i < size; i++)

		if( colors[i] != vc.colors[i] )return false;

	return true;
}

//------------------------------------------------------------------------------
bool VColor::operator!=(VColor &vc)
{
	if( size != vc.size )return true; 

	for(int i = 0; i < size; i++)

		if( colors[i] != vc.colors[i] )return true;

	return false;
}

//------------------------------------------------------------------------------
int VColor::getSize()
{
	return size;
}

//------------------------------------------------------------------------------
void VColor::setSize(int newSize)
{
	size = newSize;

	if( colors != NULL )delete[] colors;

	colors = new ColorRGB(size);
}