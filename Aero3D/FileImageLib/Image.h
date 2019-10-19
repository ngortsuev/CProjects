#pragma once

#include "Macros.h"
#include "color.h"

class DLLExport Image
{
protected:
        int width;
        int height;

        void new_data();
        void free_data();
public:
        ColorRGB **data;
		Image();
        Image(int width, int height);
        Image(int width, int height, double value);
        Image(int width, int height, ColorRGB &color);
        Image(const Image &image);
        virtual ~Image();

        Image& operator=(double value);
        Image& operator=(const ColorRGB &color);
        Image& operator=(const Image &image);

        bool operator==(Image &image);
        bool operator!=(Image &image);

        virtual int getWidth();
        virtual int getHeight();

        virtual void setWidth(int width);
        virtual void setHeight(int height);

        virtual void fillRGB(int type, double value);
        virtual void fillHSV(int type, double value);
        virtual void fillCMYK(int type, double value, double black);
        virtual void fillGrayscale();
        virtual void fillGradient();

        virtual void fillRed(double green, double blue);
        virtual void fillGreen(double red, double blue);
        virtual void fillBlue(double red, double green);

        virtual void fillCyan(double magenta, double yellow, double black);
        virtual void fillMagenta(double cyan, double yellow, double black);
        virtual void fillYellow(double cyan, double magenta, double black);

        virtual void fillHue(double sat, double value);
        virtual void fillSat(double hue, double value);
        virtual void fillValue(double hue, double value);

        //virtual void fillBitmap(Graphics::TBitmap *bitmap);
        //virtual void fillBitmap(int x_begin, int y_begin, Graphics::TBitmap *bitmap);

        virtual void fillImage(double value);
        virtual void fillImage(ColorRGB &color);
        virtual void fillImage(ColorRGB &color1, ColorRGB &color2);
        virtual void fillImage(Image *image);

        double imagecmp(Image *image);

		static Image& TGAtoRGB(unsigned char *data);		
};
