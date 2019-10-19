//------------------------------------------------------------------------------
#pragma hdrstop
#include "unFilter.h"
//------------------------------------------------------------------------------
TFilter::TFilter()
{
}
//------------------------------------------------------------------------------
TFilter::~TFilter()
{
}
//------------------------------------------------------------------------------

void __fastcall TFilter::NewBMP(Graphics::TBitmap *bmp)
{
 int x,y;
 Width=bmp->Width;
 Height=bmp->Height;

 ImageDataR=new BYTE*[Width];
 ImageDataG=new BYTE*[Width];
 ImageDataB=new BYTE*[Width];
 for(x=0;x<Width;x++)
 {
  ImageDataR[x]=new BYTE[Height];
  ImageDataG[x]=new BYTE[Height];
  ImageDataB[x]=new BYTE[Height];
 }
}
//------------------------------------------------------------------------------

void __fastcall TFilter::ReleaseBMP()
{
 int x;
 for(x=0;x<Width;x++)
 {
  delete[] ImageDataR[x];
  delete[] ImageDataG[x];
  delete[] ImageDataB[x];
 }
 delete[] ImageDataR;
 delete[] ImageDataG;
 delete[] ImageDataB;
}
//------------------------------------------------------------------------------

void __fastcall TFilter::ReadBMP(Graphics::TBitmap *bmp)
{
 int x,y;
 BYTE *LinePtr;
 Width=bmp->Width;
 Height=bmp->Height;

 NewBMP(bmp);
 for(y=0;y<bmp->Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<bmp->Width;x++)
  {
   ImageDataB[x][y]=LinePtr[x*3];
   ImageDataG[x][y]=LinePtr[x*3+1];
   ImageDataR[x][y]=LinePtr[x*3+2];
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall TFilter::WriteBMP(Graphics::TBitmap *bmp)
{
 int x,y;
 BYTE *LinePtr;

 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   LinePtr[x*3+2]=ImageDataR[x][y];
   LinePtr[x*3+1]=ImageDataG[x][y];
   LinePtr[x*3]=ImageDataB[x][y];
  }
 }
 ReleaseBMP();
}
//------------------------------------------------------------------------------

void __fastcall TFilter::Mirror(Graphics::TBitmap *bmp)
{
 int x,y;
 BYTE *LinePtr;

 ReadBMP(bmp);
 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   LinePtr[x*3+2]=ImageDataR[Width-x-1][y];
   LinePtr[x*3+1]=ImageDataG[Width-x-1][y];
   LinePtr[x*3]=ImageDataB[Width-x-1][y];
  }
 }
 ReleaseBMP();
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Invert(Graphics::TBitmap *bmp)
{
 int x,y;
 int Width,Height;
 BYTE *LinePtr;
 Width=bmp->Width;
 Height=bmp->Height;
 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   LinePtr[x*3]=255-LinePtr[x*3];
   LinePtr[x*3+1]=255-LinePtr[x*3+1];
   LinePtr[x*3+2]=255-LinePtr[x*3+2];
  }
 }
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Threshold(Graphics::TBitmap *bmp)
{
 int x,y;
 int threshold=128;
 int newsign=255;
 int elsesign=0;
 int Width,Height;
 BYTE *LinePtr;

 Width=bmp->Width;
 Height=bmp->Height;
 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   if(LinePtr[x*3]>threshold)LinePtr[x*3]=newsign;
   else LinePtr[x*3]=elsesign;

   if(LinePtr[x*3+1]>threshold)LinePtr[x*3+1]=newsign;
   else LinePtr[x*3+1]=elsesign;

   if(LinePtr[x*3+2]>threshold)LinePtr[x*3+2]=newsign;
   else LinePtr[x*3+2]=elsesign;
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall TFilter::MiddleSign(Graphics::TBitmap *bmp)
{
 int x,y;
 int middle;
 int count=0;
 int newsign=255;
 int elsesign=0;
 int Width,Height;
 BYTE *LinePtr;

 Width=bmp->Width;
 Height=bmp->Height;
 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   middle+=LinePtr[x*3];
   middle+=LinePtr[x*3+1];
   middle+=LinePtr[x*3+2];
   count+=3;
  }
 }
 middle=middle/count;
 newsign=middle+50;
 elsesign=middle-50;
 for(y=0;y<Height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<Width;x++)
  {
   if(LinePtr[x*3]>middle)LinePtr[x*3]=newsign;
   else LinePtr[x*3]=elsesign;

   if(LinePtr[x*3+1]>middle)LinePtr[x*3+1]=newsign;
   else LinePtr[x*3+1]=elsesign;

   if(LinePtr[x*3+2]>middle)LinePtr[x*3+2]=newsign;
   else LinePtr[x*3+2]=elsesign;
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall TFilter::TransformHistogram(Graphics::TBitmap *bmp)
{
 int x,y;
 int sumR=0,sumG=0,sumB=0;
 int width,height;
 BYTE *HistogramR,*HistogramG,*HistogramB;
 BYTE *TransformR,*TransformG,*TransformB;
 BYTE *LinePtr;
 width=bmp->Width;
 height=bmp->Height;
 //------------------------------------------

 HistogramR=new BYTE[width];
 HistogramG=new BYTE[width];
 HistogramB=new BYTE[width];
 TransformR=new BYTE[width];
 TransformG=new BYTE[width];
 TransformB=new BYTE[width];

 //------------------------------------------

 for(x=0;x<width;x++)
 {
  HistogramR[x]=0;
  HistogramG[x]=0;
  HistogramB[x]=0;
 }
 for(y=0;y<height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<width;x++)
  {
   HistogramR[LinePtr[x*3+2]]++;
   HistogramG[LinePtr[x*3+1]]++;
   HistogramB[LinePtr[x*3]]++;
  }
 }
 for(x=0;x<width;x++)
 {
  sumR=0;
  sumG=0;
  sumB=0;
  for(y=0;y<=x;y++)
  {
   sumR=sumR+HistogramR[y];
   sumG=sumG+HistogramG[y];
   sumB=sumB+HistogramB[y];
  }
  TransformR[x]=(width*(sumR+sumG+sumB))/(width*height);
  TransformG[x]=(width*(sumR+sumG+sumB))/(width*height);
  TransformB[x]=(width*(sumR+sumG+sumB))/(width*height);
 }
 for(y=0;y<height;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<width;x++)
  {
   LinePtr[x*3+2]=TransformR[LinePtr[x*3+2]];
   LinePtr[x*3+1]=TransformG[LinePtr[x*3+1]];
   LinePtr[x*3]=  TransformB[LinePtr[x*3]];
  }
 }
 //------------------------------------------

 delete[] HistogramR;
 delete[] HistogramG;
 delete[] HistogramB;
 delete[] TransformR;
 delete[] TransformG;
 delete[] TransformB;
}
//------------------------------------------------------------------------------

void __fastcall TFilter::Water(Graphics::TBitmap *bmp)
{
 int x,y,dx,dy,i,j;
 int Width,Height;
 BYTE *LinePtr;
 x=4;
 y=4;
 dx=4;
 dy=4;
 Width=bmp->Width;
 Height=bmp->Height;
 //----------------------------------------
 while(y<Height)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  while(x<Width)
  {
   for(i=x-dx;i<x+dx;i++)
    for(j=y-dy;j<y+dy;j++)
    {
     if(i<Width)
      if(j<Height)
      {
       LinePtr[i*3+2]=LinePtr[x*3+2];
       LinePtr[i*3+1]=LinePtr[x*3+1];
       LinePtr[i*3]=LinePtr[x*3];
      }
    }
   x+=dx;
  }
  y+=dy;
  x=dx;
 }
 //----------------------------------------
}
//------------------------------------------------------------------------------

int __fastcall TFilter::iLowpass(BYTE **ImageData, int x, int y)
{
 int Mask[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
 int i, j, sum=0;

 for (j=-1; j<=1; j++)
  for (i=-1; i<=1; i++)
   sum += ImageData[x+i][y+j]*Mask[i+1][j+1];
 return INT(sum/9.0);
}
//------------------------------------------------------------------------------

int __fastcall TFilter::iEdge(BYTE **ImageData, int x, int y)
{
 int Mask[3][3] = {{-1, -1, -1,}, {-1, 9, -1}, {-1, -1, -1}};
 int i, j, sum=0;

 for (j=-1; j<=1; j++)
  for (i=-1; i<=1; i++)
   sum += ImageData[x+i][y+j]*Mask[i+1][j+1];
 return INT(sum/9.0);
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Lowpass(Graphics::TBitmap *bmp)
{
 int x,y;
 BYTE *LinePtr;

 ReadBMP(bmp);
 for(y=1;y<bmp->Height-1;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=1;x<bmp->Width-1;x++)
  {
   LinePtr[x*3]=  iLowpass(ImageDataB,x,y);
   LinePtr[x*3+1]=iLowpass(ImageDataG,x,y);
   LinePtr[x*3+2]=iLowpass(ImageDataR,x,y);
  }
 }
 ReleaseBMP();
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Edge(Graphics::TBitmap *bmp)
{
 int x,y;
 BYTE *LinePtr;

 ReadBMP(bmp);
 for(y=1;y<bmp->Height-1;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=1;x<bmp->Width-1;x++)
  {
   LinePtr[x*3]=  iEdge(ImageDataB,x,y);
   LinePtr[x*3+1]=iEdge(ImageDataG,x,y);
   LinePtr[x*3+2]=iEdge(ImageDataR,x,y);
  }
 }
 ReleaseBMP();
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Blur(Graphics::TBitmap *bmp)
{
 //
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Sharpen(Graphics::TBitmap *bmp)
{
}
//------------------------------------------------------------------------------
void __fastcall TFilter::Embossing(Graphics::TBitmap *bmp)
{
}
//------------------------------------------------------------------------------
void __fastcall TFilter::WaterColour(Graphics::TBitmap *bmp)
{
}
//------------------------------------------------------------------------------
#pragma package(smart_init)
