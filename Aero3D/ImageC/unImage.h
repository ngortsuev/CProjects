//------------------------------------------------------------------------------

#ifndef unImageH
#define unImageH
#include <Graphics.hpp>
#include <Jpeg.hpp>
#include <Clipbrd.hpp>
#include <dstring.h>
#include "unUndoRedo.h"
#include "unFilter.h"
//------------------------------------------------------------------------------
struct StoredPixel
{
 BYTE pixel[3];
 int X;
 int Y;
};
//------------------------------------------------------------------------------
struct FileInfo
{

};
//------------------------------------------------------------------------------
class CBitmap
{
 private:
        Graphics::TBitmap *bmp;
        TIcon             *icon;
        TIconInfo         *iconInfo;
        TJPEGImage        *jpeg;
        TMetafile         *MetaFile;
        TCanvas *pCanvas;
        HANDLE handle;

        BYTE *LinePtr;
        BYTE **ImageDataR;
        BYTE **ImageDataG;
        BYTE **ImageDataB;
        BYTE **OutputDataR;
        BYTE **OutputDataG;
        BYTE **OutputDataB;
        int ImageWidth,ImageHeight;
        int OutputWidth,OutputHeight;
        int  iRotate;
        TList *listPixel;
        StoredPixel *sPixel;

 public:
        CBitmap();
        ~CBitmap();
        TUndoRedo *UndoRedo;
        TFilter *Filter;
        AnsiString FileName;
        AnsiString FileType;
        int Width;
        int Height;

        int PosX,PosY;
        int PosDX,PosDY;
        int initX,initY;
        bool Draw,DrawImage;
        bool Arc,ArcImage;
        bool Chord,ChordImage;
        bool Line,LineImage;
        bool Rectangle,RectangleImage;
        bool Ellipse,EllipseImage;
        bool FillRectangle,FillRectangleImage;
        bool FillEllipse,FillEllipseImage;
        bool Pen,PenImage;
        bool Brush,BrushImage;
        bool Text,TextImage;
        bool Zoom;
        bool ZoomBi;
        bool fZoomByMatrix;
        bool Move, MoveImage;
        bool Select, SelectImage;
        bool SelectAll;
        bool SelectByName;
        bool FilterLiquify,Liquify;

        void __fastcall Assign(Graphics::TBitmap *bmpA){bmp->Assign(bmpA);}
        void __fastcall NewFile(int Width, int Height);
        void __fastcall OpenFile(AnsiString FileName);
        void __fastcall CloseFile();
        void __fastcall SaveFile(AnsiString FileName);
        void __fastcall SaveAsHTML(AnsiString FileName);
  AnsiString __fastcall GetFileType();
  AnsiString __fastcall GetFileType(AnsiString FileExt);
  AnsiString __fastcall GetFileExt();
  AnsiString __fastcall GetFileExt(AnsiString FileType);
  AnsiString __fastcall GetFileInfo();
     Graphics::TBitmap* GetBitmap(){return bmp;}
        void __fastcall CopyToClipboard();
        void __fastcall PasteFromClipboard();
        void __fastcall SetImageSize(int NewWidth, int NewHeight);
        void __fastcall SetClientRect(int NewWidth, int NewHeight);
        void __fastcall SetDrawWindow(HANDLE h);

        void __fastcall DrawFile(int X, int Y);
        void __fastcall ZoomImage(Graphics::TBitmap *bmp, int X, int Y);
        int  __fastcall Bilinear(BYTE **ImageData,float i, float j);
        void __fastcall BilinearZoomImage(Graphics::TBitmap *bmp, int X, int Y);
        void __fastcall ZoomByMatrix(Graphics::TBitmap *bmp);
        void __fastcall UnZoomImage();
        void __fastcall ClearImage(Graphics::TBitmap *bmp);
        
        void __fastcall NewMassive(int Width, int Height);
        void __fastcall NewMassiveImage(int Width, int Height);
        void __fastcall NewMassiveOutput(int Width, int Height);

        void __fastcall ReleaseMassive();
        void __fastcall ReleaseMassiveImage();
        void __fastcall ReleaseMassiveOutput();

        void __fastcall ResizeMassive(int NewWidth, int NewHeight);
        void __fastcall ResizeMassiveImage(int NewWidth, int NewHeight);
        void __fastcall ResizeMassiveOutput(int NewWidth, int NewHeight);

        void __fastcall ClearMassive();
        void __fastcall ClearMassiveImage();
        void __fastcall ClearMassiveOutput();
        void __fastcall CopyMassive();

        void __fastcall ReadPixels(Graphics::TBitmap *bmp);
        void __fastcall WritePixels(Graphics::TBitmap *bmp);
        void __fastcall WritePixels(Graphics::TBitmap *bmp, byte r, byte g, byte b);
        
        void __fastcall iRotateImage(TPoint &p);
        void __fastcall RotateImage();
        void __fastcall RotateImageOnDeg(int Degree);


        void __fastcall DrawShape(int x, int y);
        void __fastcall StorePixel(int x, int y);
        void __fastcall RestorePixel();
        void __fastcall ClearPixel(int k);

        void __fastcall DrawFilter(int X, int Y);
        void __fastcall SetFilter(AnsiString FilterName);
        void __fastcall ConvertToBitmap();
        void __fastcall BitmapConvertTo();

        void __fastcall DisableFlagDraw();
        void __fastcall DisableFlagImageDraw();
        void __fastcall EnableFlagImageDraw();
        void __fastcall FractalMandelbrot();
        void __fastcall FractalNewton();
        void __fastcall FractalTeylor();
};
//------------------------------------------------------------------------------
#endif
