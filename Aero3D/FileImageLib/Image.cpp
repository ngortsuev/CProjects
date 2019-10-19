#include "StdAfx.h"
#include "Image.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*                                  Image                                     */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Image::Image()
{
	width = 0;
	height = 0;
	data = 0;
}

//------------------------------------------------------------------------------
Image::Image(int width, int height)
{
        this->width = width;
        this->height = height;

        new_data();
}

//------------------------------------------------------------------------------
Image::Image(const Image &image)
{
        width = image.width;
        height = image.height;

        new_data();

        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

                data[x][y] = image.data[x][y];
}

//------------------------------------------------------------------------------
Image::Image(int width, int height, double value)
{
        this->width = width;
        this->height = height;

        new_data();

        fillImage(value);
}

//------------------------------------------------------------------------------
Image::Image(int width, int height, ColorRGB &color)
{
        this->width = width;
        this->height = height;

        new_data();

        fillImage(color);
}

//------------------------------------------------------------------------------
Image::~Image()
{
        free_data();
}

//------------------------------------------------------------------------------
void Image::new_data()
{
        if( width ==  0 || height == 0 )return;

        data = new ColorRGB*[width];

        for(int i = 0; i < width; i++)
        {
                data[i] = new ColorRGB[height];
        }
}

//------------------------------------------------------------------------------
void Image::free_data()
{
        if( data != NULL )
        {
                for(int i = 0; i < width; i++)delete[] data[i];

                delete[] data;
        }
}

//------------------------------------------------------------------------------
Image& Image::operator=(double value)
{
        fillImage(value);

        return *this;
}

//------------------------------------------------------------------------------
Image& Image::operator=(const ColorRGB &color)
{
        fillImage((ColorRGB&)color);

        return *this;
}

//------------------------------------------------------------------------------
Image& Image::operator=(const Image &image)
{
        fillImage((Image*)&image);

        return *this;
}

//------------------------------------------------------------------------------
bool Image::operator==(Image &image)
{
        if( width  != image.width  )return false;
        if( height != image.height )return false;

        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

            if( data[x][y] != image.data[x][y] )return false;

        return true;
}

//------------------------------------------------------------------------------
bool Image::operator!=(Image &image)
{
        if( width  != image.width )return true;
        if( height != image.height )return true;

        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

            if( data[x][y] != image.data[x][y] )return true;

        return false;
}

//------------------------------------------------------------------------------
int Image::getWidth()
{
        return width;
}

//------------------------------------------------------------------------------
int Image::getHeight()
{
        return height;
}

//------------------------------------------------------------------------------
void Image::setWidth(int width)
{
        this->width = width;

        free_data();

        new_data();
}

//------------------------------------------------------------------------------
void Image::setHeight(int height)
{
        this->height = height;

        free_data();

        new_data();
}

//------------------------------------------------------------------------------
void Image::fillRGB(int type, double value)
{
        if( type == FILL_RED )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[x][y] = ColorRGB(value, 255 - y, x);
                        }
                }
        }

        if( type == FILL_GREEN )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[x][y] = ColorRGB(255 - y, value, x);
                        }
                }
        }

        if( type == FILL_BLUE )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[x][y] = ColorRGB(x, 255 - y, value);
                        }
                }
        }
}

//------------------------------------------------------------------------------
void Image::fillHSV(int type, double value)
{
        if( type == FILL_HUE )
        {
                for(int s = 0; s < width; s++)
                {
                        for(int v = 0; v < height; v++)
                        {
                                data[s][(height-1)-v] = ColorRGB::HSVtoRGB(ColorHSV(value, s,v));
                        }
                }
        }

        if( type == FILL_SAT )
        {
                int index;
                for(int h = 0; h < 360; h++)
                {
                        index = int(((double)h / (double)360)*(double)256);
                        if( index >= 0 && index <= 255)
                        for(int v = 0; v < height; v++)
                        {
                                data[index][(height-1)-v] = ColorRGB::HSVtoRGB(ColorHSV(h, value, v));
                        }
                }
        }

        if( type == FILL_VALUE )
        {
                int index;
                for(int h = 0; h < 360; h++)
                {
                        index = int(((double)h / (double)360)*(double)256);
                        if( index >= 0 && index <= 255)
                        for(int s = 0; s < height; s++)
                        {
                                data[index][(height-1)-s] = ColorRGB::HSVtoRGB(ColorHSV(h, s, value));
                        }
                }
        }
}

//------------------------------------------------------------------------------
void Image::fillCMYK(int type, double value, double black)
{
        if( type == FILL_CYAN )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[(width-1)-x][y] = ColorRGB::CMYKtoRGB(ColorCMYK(value, y, x, black));
                        }
                }
        }

        if( type == FILL_MAGENTA )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[(width-1)-x][y] = ColorRGB::CMYKtoRGB(ColorCMYK(y, value, x, black));
                        }
                }
        }

        if( type == FILL_YELLOW )
        {
                for(int y = 0; y < height; y++)
                {
                        for(int x = 0; x < width; x++)
                        {
                                data[(width-1)-x][y] = ColorRGB::CMYKtoRGB(ColorCMYK(x, y, value, black));
                        }
                }
        }
}

//------------------------------------------------------------------------------
void Image::fillGrayscale()
{
        for(int y = 0; y < height; y++)

                for(int x = 0; x < width; x++)
                {
                        data[x][(height-1)-y] = ColorRGB::RGBtoGrayscale(ColorRGB(x,y,255));
                }
}

//------------------------------------------------------------------------------
void Image::fillGradient()
{

}

//------------------------------------------------------------------------------
void Image::fillRed(double green, double blue)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB(y, green, blue);
}

//------------------------------------------------------------------------------
void Image::fillGreen(double red, double blue)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB(red, y, blue);
}

//------------------------------------------------------------------------------
void Image::fillBlue(double red, double green)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB(red, green, y);
}

//------------------------------------------------------------------------------
void Image::fillCyan(double magenta, double yellow, double black)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB::CMYKtoRGB(ColorCMYK(y, magenta, yellow, black));
}

//------------------------------------------------------------------------------
void Image::fillMagenta(double cyan, double yellow, double black)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB::CMYKtoRGB(ColorCMYK(cyan, y, yellow, black));
}

//------------------------------------------------------------------------------
void Image::fillYellow(double cyan, double magenta, double black)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][(height-1)-y] = ColorRGB::CMYKtoRGB(ColorCMYK(cyan, magenta, y, black));
}

//------------------------------------------------------------------------------
void Image::fillHue(double sat, double value)
{
        for(int s = 0; s < width; s++)

          for(int v = 0; v < height; v++)

               data[s][(height-1)-v] = ColorRGB::HSVtoRGB(ColorHSV(v, sat, value));
}

//------------------------------------------------------------------------------
void Image::fillSat(double hue, double value)
{
        for(int s = 0; s < width; s++)

          for(int v = 0; v < height; v++)

               data[s][(height-1)-v] = ColorRGB::HSVtoRGB(ColorHSV(hue, v, value));
}

//------------------------------------------------------------------------------
void Image::fillValue(double hue, double sat)
{
        for(int s = 0; s < width; s++)

          for(int v = 0; v < height; v++)

               data[s][(height-1)-v] = ColorRGB::HSVtoRGB(ColorHSV(hue, sat, v));
}

//------------------------------------------------------------------------------
/*
void Image::fillBitmap(Graphics::TBitmap *bitmap)
{
        BYTE *LinePtr;
        for(int y = 0; y < height; y++)
        {
                LinePtr = (BYTE*)bitmap->ScanLine[y];
                for(int x = 0; x < width; x++)
                {
                        LinePtr[x*3+0] = data[x][y].blue;
                        LinePtr[x*3+1] = data[x][y].green;
                        LinePtr[x*3+2] = data[x][y].red;
                } 
        }
}

//------------------------------------------------------------------------------
void Image::fillBitmap(int x_begin, int y_begin, Graphics::TBitmap *bitmap)
{
        BYTE *LinePtr;
        for(int y = 0; y < height; y++)
        {
                LinePtr = (BYTE*)bitmap->ScanLine[y + y_begin];
                for(int x = 0; x < width; x++)
                {
                        LinePtr[(x + x_begin)*3+0] = data[x][y].blue;
                        LinePtr[(x + x_begin)*3+1] = data[x][y].green;
                        LinePtr[(x + x_begin)*3+2] = data[x][y].red;
                } 
        }
}
*/
//------------------------------------------------------------------------------
void Image::fillImage(double value)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][y] = value;
}

//------------------------------------------------------------------------------
void Image::fillImage(ColorRGB &color)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][y] = color;
}

//------------------------------------------------------------------------------
void Image::fillImage(ColorRGB &color1, ColorRGB &color2)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width/2; x++)
          {
               data[x][y] = color1;

               data[(width-1)-x][(height-1)-y] = color2;
          }
}

//------------------------------------------------------------------------------
void Image::fillImage(Image *image)
{
        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

               data[x][y] = image->data[x][y];
}

//------------------------------------------------------------------------------
double Image::imagecmp(Image *image)
{
        double value;

		value = 0;

        for(int y = 0; y < height; y++)

          for(int x = 0; x < width; x++)

                if( data[x][y] != image->data[x][y] )value++;


        return value / (width*height);
}

