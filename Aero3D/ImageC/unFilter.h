//------------------------------------------------------------------------------

#ifndef unFilterH
#define unFilterH
#include <Graphics.hpp>
//------------------------------------------------------------------------------
class TFilter
{
 private:
        int Width,Height;
        BYTE **ImageDataR,**ImageDataG,**ImageDataB;
        void __fastcall ReadBMP(Graphics::TBitmap *bmp);
        void __fastcall WriteBMP(Graphics::TBitmap *bmp);
        void __fastcall NewBMP(Graphics::TBitmap *bmp);
        void __fastcall ReleaseBMP();
        int  __fastcall iLowpass(BYTE **ImageData, int x, int y);
        int  __fastcall iEdge(BYTE **ImageData, int x, int y);
 public:
        TFilter();
        ~TFilter();
        void __fastcall Mirror(Graphics::TBitmap *bmpM);
        void __fastcall Invert(Graphics::TBitmap *bmpInv);
        void __fastcall Threshold(Graphics::TBitmap *bmpThr);
        void __fastcall MiddleSign(Graphics::TBitmap *bmpMS);
        void __fastcall TransformHistogram(Graphics::TBitmap *bmpH);
        void __fastcall Water(Graphics::TBitmap *bmpW);
        void __fastcall Lowpass(Graphics::TBitmap *bmp);
        void __fastcall Edge(Graphics::TBitmap *bmp);

        void __fastcall Blur(Graphics::TBitmap *bmp);        //--- размытие
        void __fastcall Sharpen(Graphics::TBitmap *bmp);     //--- увеличение резкости
        void __fastcall Embossing(Graphics::TBitmap *bmp);       //--- тиснение
        void __fastcall WaterColour(Graphics::TBitmap *bmp); //--- акварель

};
//------------------------------------------------------------------------------
#endif
