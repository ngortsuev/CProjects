//------------------------------------------------------------------------------
#pragma hdrstop
#include <math.h>
#include "unImage.h"
#include "unComplex.h"
//------------------------------------------------------------------------------
CBitmap::CBitmap()
{
 bmp=new Graphics::TBitmap;
 pCanvas=new TCanvas;
 listPixel=new TList;
 UndoRedo=new TUndoRedo;
 Filter=new TFilter;
 jpeg=NULL;
 icon=NULL;
 iconInfo=NULL;
 MetaFile=NULL;
 iRotate=0;
}
//------------------------------------------------------------------------------
CBitmap::~CBitmap()
{
 for(int i=0;i<listPixel->Count;i++)
 {
  sPixel=(StoredPixel*)listPixel->Items[i];
  delete sPixel;
 }
 delete listPixel;
 if(bmp!=NULL)delete bmp;
 if(jpeg!=NULL)delete jpeg;
 if(icon!=NULL)delete icon;
 if(iconInfo!=NULL)delete iconInfo;
 if(MetaFile!=NULL)delete MetaFile;
 delete pCanvas;
 delete UndoRedo;
 delete Filter;
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::NewFile(int Width, int Height)
{
 NewMassiveImage(Width,Height);
 NewMassiveOutput(Width,Height);
 bmp->PixelFormat=pf24bit;
 bmp->Width=Width;
 bmp->Height=Height;
 ClearImage(bmp);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::OpenFile(AnsiString FileName)
{
 CBitmap::FileName=FileName;
 FileType=GetFileType();
 if(FileType=="Bitmap")
 {
  bmp->LoadFromFile(FileName);
  ImageWidth=bmp->Width;
  ImageHeight=bmp->Height;
 }
 if(FileType=="Jpeg")
 {   
  jpeg=new TJPEGImage;
  jpeg->LoadFromFile(FileName);
  ImageWidth=jpeg->Width;
  ImageHeight=jpeg->Height;
 }
 if(FileType=="Icon")
 {
  icon=new TIcon;
  iconInfo=new TIconInfo;
  icon->LoadFromFile(FileName);
  ImageWidth=icon->Width;
  ImageHeight=icon->Height;
 }
 if(FileType=="Gif")
 {
 }
 if(FileType=="Tiff")
 {
 }
 if(FileType=="Png")
 {
 }
 if(FileType=="Emf")
 {
  MetaFile=new TMetafile;
  MetaFile->Enhanced=true;
  MetaFile->LoadFromFile(FileName);
  ImageWidth=MetaFile->Width;
  ImageHeight=MetaFile->Height;
 }
 if(FileType=="Wmf")
 {
  MetaFile=new TMetafile;
  MetaFile->Enhanced=false;
  MetaFile->LoadFromFile(FileName);
  ImageWidth=MetaFile->Width;
  ImageHeight=MetaFile->Height;
 }
 ConvertToBitmap();
 Width=ImageWidth;
 Height=ImageHeight;
 NewMassiveImage(ImageWidth,ImageHeight);
 NewMassiveOutput(ImageWidth,ImageHeight);

} 
//------------------------------------------------------------------------------

void __fastcall CBitmap::CloseFile()
{
 if(FileType=="Jpeg")
 {
  if(jpeg!=NULL)delete jpeg;
 }
 if(FileType=="Icon")
 {
  if(icon!=NULL)delete icon;
  if(iconInfo!=NULL)delete iconInfo;
 }
 if(FileType=="Gif")
 {
 }
 if(FileType=="Tiff")
 {
 }
 if(FileType=="Png")
 {
 }
 if(FileType=="Emf")
 {
  if(MetaFile!=NULL)delete MetaFile;
 }
 if(FileType=="Wmf")
 {
  if(MetaFile!=NULL)delete MetaFile;
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::SaveFile(AnsiString File)
{
 AnsiString Extension;
 FileName=File;
 if(ExtractFileExt(FileName)=="")
 {
  Extension=GetFileExt();
  FileName=FileName+Extension;
 }
 else
 {
  Extension=GetFileExt();
  FileName=ChangeFileExt(FileName,Extension);
 }
 BitmapConvertTo();
 if(FileType=="Bitmap")bmp->SaveToFile(FileName);
 if(FileType=="Jpeg")jpeg->SaveToFile(FileName);
 if(FileType=="Icon")icon->SaveToFile(FileName);
 if(FileType=="Gif")
 {
 }
 if(FileType=="Tiff")
 {
 }
 if(FileType=="Png")
 {
 }
 if(FileType=="Emf")MetaFile->SaveToFile(FileName);
 if(FileType=="Wmf")MetaFile->SaveToFile(FileName);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::SaveAsHTML(AnsiString FileName)
{
 AnsiString text,FileNameHTML;
 FileNameHTML=ChangeFileExt(FileName,".htm");
 
 TFileStream *fm=new TFileStream(FileNameHTML,fmCreate);
 text="<IMG SRC="+FileName+">";
 fm->Write("<HTML>",6);
 fm->Write("<HEAD>",6);
 fm->Write("<BODY>",6);
 fm->Write(text.c_str(),text.Length());
 fm->Write("</BODY>",7);
 fm->Write("</HEAD>",7);
 fm->Write("</HTML>",7);
 delete fm;
}
//------------------------------------------------------------------------------

AnsiString __fastcall CBitmap::GetFileType()
{
 AnsiString Ext;
 if(FileName!="")
 {
  Ext=ExtractFileExt(FileName);
  Ext=Ext.UpperCase();
  if(Ext==".BMP")return "Bitmap";
  if(Ext==".JPEG" || Ext==".JPG")return "Jpeg";
  if(Ext==".ICO")return "Icon";
  if(Ext==".GIF")return "Gif";
  if(Ext==".TIFF")return "Tiff";
  if(Ext==".PNG")return "Png";
  if(Ext==".EMF")return "Emf";
  if(Ext==".WMF")return "Wmf";
  return "";
 }
 else return "";
}
//------------------------------------------------------------------------------
AnsiString __fastcall CBitmap::GetFileType(AnsiString FileExt)
{
 FileExt=FileExt.UpperCase();
 if(FileExt==".BMP")return "Bitmap";
 if(FileExt==".JPEG" || FileExt==".JPG")return "Jpeg";
 if(FileExt==".ICO")return "Icon";
 if(FileExt==".GIF")return "Gif";
 if(FileExt==".TIFF")return "Tiff";
 if(FileExt==".PNG")return "Png";
 if(FileExt==".EMF")return "Emf";
 if(FileExt==".WMF")return "Wmf";
 return "";
}
//------------------------------------------------------------------------------
AnsiString __fastcall CBitmap::GetFileExt()
{
 if(FileType=="Bitmap")return ".bmp";
 if(FileType=="Jpeg")return ".jpg";
 if(FileType=="Icon")return ".ico";
 if(FileType=="Gif")return ".gif";
 if(FileType=="Tiff")return ".tiff";
 if(FileType=="Png")return ".png";
 if(FileType=="Emf")return ".emf";
 if(FileType=="Wmf")return ".wmf";
 return "";
}
//------------------------------------------------------------------------------
AnsiString __fastcall CBitmap::GetFileExt(AnsiString FileType)
{
 if(FileType=="Bitmap")return ".bmp";
 if(FileType=="Jpeg")return ".jpg";
 if(FileType=="Icon")return ".ico";
 if(FileType=="Gif")return ".gif";
 if(FileType=="Tiff")return ".tiff";
 if(FileType=="Png")return ".png";
 if(FileType=="Emf")return ".emf";
 if(FileType=="Wmf")return ".wmf";
 return "";
}

//------------------------------------------------------------------------------
AnsiString __fastcall CBitmap::GetFileInfo()
{
 SIZE size;
 HDC hdc;
 BITMAPINFO bmpInfo;
 HBITMAP hBmp;
 HBITMAP mask;
 HPALETTE palette;
 ////////////////////////
 BITMAP ibmp;
 DIBSECTION dibsec;
 HBRUSH hbrush;
 HPEN hpen;
 HFONT hfont;
 LOGBRUSH lb;
 LOGPEN lp;
 LOGFONT lf;
 ////////////////////////
 HANDLE hFile;
 WIN32_FIND_DATA FileData;
 FILETIME Time;
 FILETIME LocalTime;
 SYSTEMTIME SysTime;
 AnsiString FileTime;
 AnsiString LastAccessTime;
 AnsiString LastWriteTime;
 AnsiString FileSize;
 AnsiString FilePath;
 AnsiString FileExt;
 AnsiString Ret;
 //----------------------------------
 hdc=pCanvas->Handle;
 hBmp=bmp->Handle;
 bmpInfo.bmiHeader.biBitCount=0;

 //----------------------------------
 hFile=FindFirstFile(FileName.c_str(),&FileData);
 FindClose(hFile);

 //--- Time Creation
 Time=FileData.ftCreationTime;
 FileTimeToLocalFileTime(&Time,&LocalTime);
 FileTimeToSystemTime(&LocalTime,&SysTime);
 FileTime=FloatToStr(SysTime.wDay)+"."+FloatToStr(SysTime.wMonth)+"."+
          FloatToStr(SysTime.wYear)+" "+FloatToStr(SysTime.wHour)+":"+
          FloatToStr(SysTime.wMinute)+":"+FloatToStr(SysTime.wSecond);
 Ret+=FileTime+";";

 //---Last Access Time
 Time=FileData.ftLastAccessTime;
 FileTimeToLocalFileTime(&Time,&LocalTime);
 FileTimeToSystemTime(&LocalTime,&SysTime);
 LastAccessTime=FloatToStr(SysTime.wDay)+"."+FloatToStr(SysTime.wMonth)+"."+
                FloatToStr(SysTime.wYear)+" "+FloatToStr(SysTime.wHour)+":"+
                FloatToStr(SysTime.wMinute)+":"+FloatToStr(SysTime.wSecond);
 Ret+=LastAccessTime+";";

 //---Last Write Time
 Time=FileData.ftLastWriteTime;
 FileTimeToLocalFileTime(&Time,&LocalTime);
 FileTimeToSystemTime(&LocalTime,&SysTime);
 LastWriteTime=FloatToStr(SysTime.wDay)+"."+FloatToStr(SysTime.wMonth)+"."+
               FloatToStr(SysTime.wYear)+" "+FloatToStr(SysTime.wHour)+":"+
               FloatToStr(SysTime.wMinute)+":"+FloatToStr(SysTime.wSecond);
 Ret+=LastWriteTime+";";

 FileSize=FloatToStr(FileData.nFileSizeHigh*MAXDWORD+FileData.nFileSizeLow);
 FilePath=ExtractFilePath(FileName);
 FileExt=ExtractFileExt(FileName);
 Ret+=FileSize+";"+FilePath+";"+FileExt+";"+ExtractFileName(FileName)+";"+FileType+";";
 Ret+=IntToStr(FileData.dwFileAttributes)+";";
 //-------------------------------------------

 memset(&bmpInfo,NULL,sizeof(bmpInfo));
 memset(&bmpInfo.bmiHeader,NULL,sizeof(bmpInfo.bmiHeader));

 GetBitmapDimensionEx(hBmp,&size);
 GetDIBits(pCanvas->Handle,hBmp,0,0,NULL,&bmpInfo,DIB_RGB_COLORS);
 GetObject(hBmp,sizeof(ibmp),&ibmp);
 GetObject(hBmp,sizeof(dibsec),&dibsec);

 Ret+=IntToStr(ibmp.bmWidth)+";";
 Ret+=IntToStr(ibmp.bmHeight)+";";
 Ret+=IntToStr(dibsec.dsBmih.biXPelsPerMeter)+";";
 Ret+=IntToStr(dibsec.dsBmih.biYPelsPerMeter)+";";
 Ret+=IntToStr(ibmp.bmBitsPixel)+";";
 Ret+=IntToStr(ibmp.bmPlanes)+";";
 //---------------------------------------------------
 hbrush=GetCurrentObject(hdc,OBJ_BRUSH);
 hpen=GetCurrentObject(hdc,OBJ_PEN);
 hfont=GetCurrentObject(hdc,OBJ_FONT);

 if(hbrush!=NULL)GetObject(hbrush,sizeof(lb),&lb);
 if(hpen!=NULL)GetObject(hpen,sizeof(lp),&lp);
 if(hfont!=NULL)GetObject(hfont,sizeof(lf),&lf);
 return Ret;
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::CopyToClipboard()
{
 unsigned int DataHandle;
 HPALETTE hPalette;
 unsigned short Format;
 try
 {
  bmp->SaveToClipboardFormat(Format,DataHandle,hPalette);
  Clipboard()->SetAsHandle(Format,DataHandle);
 }
 catch(...)
 {
 }
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::PasteFromClipboard()
{
 TClipboard *cb=Clipboard();
 if(cb->HasFormat(CF_BITMAP))
 try
 {
  //AddUndo();
  Graphics::TBitmap *bmpCB=new Graphics::TBitmap;
  bmpCB->LoadFromClipboardFormat(CF_BITMAP,cb->GetAsHandle(CF_BITMAP),0);
  bmp->Assign(bmpCB);
  delete bmpCB;
 }
 catch(...)
 {

 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::SetImageSize(int NewWidth, int NewHeight)
{
 ResizeMassive(NewWidth,NewHeight);
 bmp->Width=NewWidth;
 bmp->Height=NewHeight;
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::SetClientRect(int NewWidth, int NewHeight)
{
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::SetDrawWindow(HANDLE h)
{
 handle=h;
 pCanvas->Handle=GetDC(h);
 //bmp->Canvas->Handle=GetDC(h);
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::DrawFile(int X, int Y)
{
 pCanvas->Handle=GetDC(handle);
 pCanvas->Draw(X,Y,bmp);
}
//------------------------------------------------------------------------------
//--------------------------------Zoom Image------------------------------------
void __fastcall CBitmap::ZoomImage(Graphics::TBitmap *bmp, int X, int Y)
{
 int i,j,x,y;
 int x0,y0;
 float zoom=2;

 x0=X;
 y0=Y;
 ReadPixels(bmp);
 //----------------Zoom Image--------------------------
 for(y=0;y< ImageHeight;y++)
 {
  for(x=0;x< ImageWidth;x++)
  {
   i=INT((x+(zoom-1)*x0)/zoom);
   j=INT((y+(zoom-1)*y0)/zoom);
   OutputDataR[x][y]=ImageDataR[i][j];
   OutputDataG[x][y]=ImageDataG[i][j];
   OutputDataB[x][y]=ImageDataB[i][j];
  }
 } 
 WritePixels(bmp);
}
//------------------------------------------------------------------------------

int __fastcall CBitmap::Bilinear(BYTE **Image,float i, float j)
{
 int x1,y1,x2,y2;
 float Gray;
 x1=(int)floor(i);
 x2=x1+1;
 y1=(int)floor(j);
 y2=y1+1;
 Gray=(y2-j)*(x2-i)*Image[x1][y1]+
      (y2-j)*(i-x1)*Image[x2][y1]+
      (j-y1)*(x2-i)*Image[x1][y2]+
      (j-y1)*(i-x1)*Image[x2][y2];
 return INT(Gray);
}
//------------------------------Bilinear Zoom Image-----------------------------

void __fastcall CBitmap::BilinearZoomImage(Graphics::TBitmap *bmp, int X, int Y)
{
 int i,j,x,y;
 int x0,y0;
 float zoom=2;
 x0=X;
 y0=Y;

 ReadPixels(bmp);
 //----------------Zoom Image--------------------------
 for(y=0;y< ImageHeight;y++)
   for(x=0;x< ImageWidth;x++)
   {
    i=(int)(x+(zoom-1)*x0)/zoom;
    j=(int)(y+(zoom-1)*y0)/zoom;
    OutputDataB[x][y]=Bilinear(ImageDataB,i,j);     //---blue pixel
    OutputDataG[x][y]=Bilinear(ImageDataG,i,j);     //---green pixel
    OutputDataR[x][y]=Bilinear(ImageDataR,i,j);       //---red pixel
   }
 //----------------Write Data to Image-----------------
 WritePixels(bmp);
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::ZoomByMatrix(Graphics::TBitmap *bmp)
{
 int i,j;
 int zoom=3;
 int width,height;
 width=bmp->Width*zoom;
 height=bmp->Height*zoom;
 ReadPixels(bmp);
 ResizeMassiveOutput(width,height);
 /*
 FormShowProcess->ProgressBar1->Max=height;
 FormShowProcess->Left=MainForm->Width/2;
 FormShowProcess->Top=MainForm->Height/2;
 FormShowProcess->Show();
 */
 for(int y=0;y<bmp->Height;y++)
 {
  for(int x=0;x<bmp->Width;x++)
  {
   OutputDataR[x*zoom][y*zoom]=ImageDataR[x][y];
   OutputDataG[x*zoom][y*zoom]=ImageDataG[x][y];
   OutputDataB[x*zoom][y*zoom]=ImageDataB[x][y];

   if(x<bmp->Width-1 && y<bmp->Height-1)
   {
    OutputDataR[x*zoom+1][y*zoom+1]=ImageDataR[x][y];
    OutputDataG[x*zoom+1][y*zoom+1]=ImageDataG[x][y];
    OutputDataB[x*zoom+1][y*zoom+1]=ImageDataB[x][y];
   }
   if(x<bmp->Width-1)
   {
    OutputDataR[x*zoom+1][y*zoom]=ImageDataR[x][y];
    OutputDataG[x*zoom+1][y*zoom]=ImageDataG[x][y];
    OutputDataB[x*zoom+1][y*zoom]=ImageDataB[x][y];
   }
   if(y<bmp->Height-1)
   {
    OutputDataR[x*zoom][y*zoom+1]=ImageDataR[x][y];
    OutputDataG[x*zoom][y*zoom+1]=ImageDataG[x][y];
    OutputDataB[x*zoom][y*zoom+1]=ImageDataB[x][y];
   }
   
   if(x>0 && y>0)
   {
    OutputDataR[x*zoom-1][y*zoom-1]=ImageDataR[x][y];
    OutputDataG[x*zoom-1][y*zoom-1]=ImageDataG[x][y];
    OutputDataB[x*zoom-1][y*zoom-1]=ImageDataB[x][y];
   }
   if(x>0)
   {
    OutputDataR[x*zoom-1][y*zoom]=ImageDataR[x][y];
    OutputDataG[x*zoom-1][y*zoom]=ImageDataG[x][y];
    OutputDataB[x*zoom-1][y*zoom]=ImageDataB[x][y];
   }
   if(y>0)
   {
    OutputDataR[x*zoom][y*zoom-1]=ImageDataR[x][y];
    OutputDataG[x*zoom][y*zoom-1]=ImageDataG[x][y];
    OutputDataB[x*zoom][y*zoom-1]=ImageDataB[x][y];
   }
  }
  //FormShowProcess->ProgressBar1->StepIt();
 }
 //FormShowProcess->Close();
 bmp->Width=width;
 bmp->Height=height;
 WritePixels(bmp);
 ResizeMassiveImage(width,height);
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::UnZoomImage()
{
 int x,y;

 ReadPixels(bmp);
 //----------------Write Data to Image-----------------
 for(y=0;y<ImageHeight;y++)
 {
  for(x=0;x<ImageWidth;x++)
  {
   OutputDataB[x/2][y/2]=ImageDataB[x][y];
   OutputDataG[x/2][y/2]=ImageDataG[x][y];
   OutputDataR[x/2][y/2]=ImageDataR[x][y];
  }
 }
 WritePixels(bmp);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ClearImage(Graphics::TBitmap *bmp)
{
 ClearMassiveImage();
 ClearMassiveOutput();
 WritePixels(bmp);
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::NewMassive(int Width, int Height)
{
 ReleaseMassive();
 NewMassiveImage(Width,Height);
 NewMassiveOutput(Width,Height);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::NewMassiveImage(int Width, int Height)
{
 int i;
 ImageWidth=Width;
 ImageHeight=Height;
 ImageDataR=new BYTE*[Width];
 ImageDataG=new BYTE*[Width];
 ImageDataB=new BYTE*[Width];
 for(i=0;i<Width;i++)
 {
  ImageDataR[i]=new BYTE[Height];
  ImageDataG[i]=new BYTE[Height];
  ImageDataB[i]=new BYTE[Height];
 }
}
//------------------------------------------------------------------------------
void __fastcall  CBitmap::NewMassiveOutput(int Width, int Height)
{
 int i;
 OutputWidth=Width;
 OutputHeight=Height;
 OutputDataR=new BYTE*[Width];
 OutputDataG=new BYTE*[Width];
 OutputDataB=new BYTE*[Width];
 for(i=0;i<Width;i++)
 {
  OutputDataR[i]=new BYTE[Height];
  OutputDataG[i]=new BYTE[Height];
  OutputDataB[i]=new BYTE[Height];
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ReleaseMassive()
{
 ReleaseMassiveImage();
 ReleaseMassiveOutput();
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ReleaseMassiveImage()
{
 int i;
 if(ImageDataR!=NULL)
 {
  for(i=0;i<ImageWidth;i++)
  {
   delete[] ImageDataR[i];
  }
  delete[] ImageDataR;
 }
 if(ImageDataG!=NULL)
 {
  for(i=0;i<ImageWidth;i++)
  {
   delete[] ImageDataG[i];
  }
  delete[] ImageDataG;
 }
 if(ImageDataB!=NULL)
 {
  for(i=0;i<ImageWidth;i++)
  {
   delete[] ImageDataB[i];
  }
  delete[] ImageDataB;
 }
 ImageWidth=0;
 ImageHeight=0;
 ImageDataR=NULL;
 ImageDataG=NULL;
 ImageDataB=NULL;
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::ReleaseMassiveOutput()
{
 int i;
 if(OutputDataR!=NULL)
 {
  for(i=0;i<OutputWidth;i++)
  {
   delete[] OutputDataR[i];
  }
  delete[] OutputDataR;
 }
 if(OutputDataG!=NULL)
 {
  for(i=0;i<OutputWidth;i++)
  {
   delete[] OutputDataG[i];
  }
  delete[] OutputDataG;
 }
 if(OutputDataB!=NULL)
 {
  for(i=0;i<OutputWidth;i++)
  {
   delete[] OutputDataB[i];
  }
  delete[] OutputDataB;
 }
 OutputWidth=0;
 OutputHeight=0;
 OutputDataR=NULL;
 OutputDataG=NULL;
 OutputDataB=NULL;
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ResizeMassive(int NewWidth, int NewHeight)
{
 ReleaseMassive();
 NewMassive(NewWidth,NewHeight);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ResizeMassiveImage(int NewWidth, int NewHeight)
{
 ReleaseMassiveImage();
 NewMassiveImage(NewWidth,NewHeight);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ResizeMassiveOutput(int NewWidth, int NewHeight)
{
 ReleaseMassiveOutput();
 NewMassiveOutput(NewWidth,NewHeight);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ClearMassive()
{
 ClearMassiveImage();
 ClearMassiveOutput();
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ClearMassiveImage()
{
 int i,j;
 for(i=0;i<ImageWidth;i++)
 {
  for(j=0;j<ImageHeight;j++)
  {
   ImageDataR[i][j]='ÿ';
   ImageDataG[i][j]='ÿ';
   ImageDataB[i][j]='ÿ';
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ClearMassiveOutput()
{
 int i,j;
 for(i=0;i<OutputWidth;i++)
 {
  for(j=0;j<OutputHeight;j++)
  {
   OutputDataR[i][j]='ÿ';
   OutputDataG[i][j]='ÿ';
   OutputDataB[i][j]='ÿ';
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::CopyMassive()
{
 int x,y;
 for(y=0;y<ImageHeight;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<ImageWidth;x++)
  {
   OutputDataB[x][y]=ImageDataB[x][y];     //---blue pixel
   OutputDataG[x][y]=ImageDataG[x][y];     //---green pixel
   OutputDataR[x][y]=ImageDataR[x][y];     //---red pixel
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ReadPixels(Graphics::TBitmap *bmp)
{
 int x,y;
 for(y=0;y<ImageHeight;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<ImageWidth;x++)
  {
   ImageDataB[x][y]=LinePtr[x*3];     //---blue pixel
   ImageDataG[x][y]=LinePtr[x*3+1];   //---green pixel
   ImageDataR[x][y]=LinePtr[x*3+2];   //---red pixel
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::WritePixels(Graphics::TBitmap *bmp)
{
 int x,y;
 for(y=0;y<OutputHeight;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<OutputWidth;x++)
  {
   LinePtr[x*3]=OutputDataB[x][y];     //---blue pixel
   LinePtr[x*3+1]=OutputDataG[x][y];   //---green pixel
   LinePtr[x*3+2]=OutputDataR[x][y];   //---red pixel
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::WritePixels(Graphics::TBitmap *bmp, byte r, byte g, byte b)
{
 int x,y;
 for(y=0;y<OutputHeight;y++)
 {
  LinePtr=(BYTE*)bmp->ScanLine[y];
  for(x=0;x<OutputWidth;x++)
  {
   if(b==1){
    LinePtr[x*3+2]=1;
   }
   if(g==1)
   {
    LinePtr[x*3]=1;
   }
   if(r==1)
   {
    LinePtr[x*3]=1;
    LinePtr[x*3+1]=1;
   }
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::iRotateImage(TPoint &p)
{
 int t;
 if(iRotate==1 || iRotate==3)
 {
  t=p.x;
  p.x=p.y;
  p.y=t;
 }
 if(iRotate==2 || iRotate==4)
 {
  t=p.x;
  p.x=ImageHeight-p.y-1;
  p.y=ImageWidth-t-1;
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::RotateImage()
{
 int x,y;
 TPoint p;
 ReadPixels(bmp);
 bmp->Width=ImageHeight;
 bmp->Height=ImageWidth;
 ResizeMassiveOutput(ImageHeight,ImageWidth);

 if(iRotate==4)iRotate=0;
 iRotate++;
 for(x=0;x<ImageWidth;x++)
 {
  for(y=0;y<ImageHeight;y++)
  {
   p.x=x;
   p.y=y;
   iRotateImage(p);
   OutputDataR[p.x][p.y]=ImageDataR[x][y];
   OutputDataG[p.x][p.y]=ImageDataG[x][y];
   OutputDataB[p.x][p.y]=ImageDataB[x][y];
  }
 }
 WritePixels(bmp);
 ResizeMassiveImage(ImageHeight,ImageWidth);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::RotateImageOnDeg(int Degree)
{
 UndoRedo->AddUndo(bmp);
 if(Degree==90)RotateImage();
 if(Degree==180)
 {
  RotateImage();
  RotateImage();
 }
 if(Degree==270)
 {
  RotateImage();
  RotateImage();
  RotateImage();
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::DrawShape(int x, int y)
{
 if(ArcImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Arc(PosX,PosY,x,y,PosX,PosY,x,y);
  bmp->Canvas->Arc(PosX,PosY,x,y,PosX,PosY,x,y);
  StorePixel(x,y);
 }
 if(ChordImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Chord(PosX,PosY,x,y,PosX,PosY,x,y);
  bmp->Canvas->Chord(PosX,PosY,x,y,PosX,PosY,x,y);
  StorePixel(x,y);
 }
 if(LineImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->MoveTo(PosX,PosY);
  pCanvas->LineTo(x,y);
  bmp->Canvas->MoveTo(PosX,PosY);
  bmp->Canvas->LineTo(x,y);
  StorePixel(x,y);
 }
 if(EllipseImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Ellipse(PosX,PosY,x,y);
  bmp->Canvas->Ellipse(PosX,PosY,x,y);
  StorePixel(x,y);
 }
 if(RectangleImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->FrameRect(TRect(PosX,PosY,x,y));
  bmp->Canvas->FrameRect(TRect(PosX,PosY,x,y));
  StorePixel(x,y);
 }
 if(FillRectangleImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Rectangle(PosX,PosY,x,y);
  bmp->Canvas->Rectangle(PosX,PosY,x,y);
  StorePixel(x,y);
 }
 if(FillEllipseImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Ellipse(PosX,PosY,x,y);
  bmp->Canvas->Ellipse(PosX,PosY,x,y);
  StorePixel(x,y);
 }
 if(PenImage==true)
 {
  pCanvas->MoveTo(PosX,PosY);
  pCanvas->LineTo(x,y);
  bmp->Canvas->MoveTo(PosX,PosY);
  bmp->Canvas->LineTo(x,y);
  PosX=x;
  PosY=y;
 }
 if(BrushImage==true)
 {
  TColor oldBrush;
  oldBrush=pCanvas->Brush->Color;
  pCanvas->Brush->Color=clBlack;
  pCanvas->Ellipse(PosX,PosY,x+15,y+15);
  bmp->Canvas->Ellipse(PosX,PosY,x+15,y+15);
  pCanvas->Brush->Color=oldBrush;
  PosX=x;
  PosY=y;
 }
 if(TextImage==true)
 {
  /*
  FormInputText->Left=PosX+50;
  FormInputText->Top=PosY+50;
  FormInputText->ShowModal();
  if(FormInputText->B_OK==true)
  {

   pCanvas->TextOutA(x,y,FormInputText->eText->Text);
   bmp->Canvas->TextOutA(x,y,FormInputText->eText->Text);
  }
  */
 }
 if(SelectImage==true)
 {
  RestorePixel();
  ClearPixel(1);
  pCanvas->Rectangle(PosX,PosY,x,y);
  StorePixel(x,y);
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::StorePixel(int x, int y)
{
 if(x>=0 && x<ImageWidth)
 {
  if(y>=0 && y<ImageHeight)
  {
   sPixel=new StoredPixel;
   sPixel->pixel[0]=ImageDataR[x][y];
   sPixel->pixel[1]=ImageDataG[x][y];
   sPixel->pixel[2]=ImageDataB[x][y];
   sPixel->X=x;
   sPixel->Y=y;
   listPixel->Add(sPixel);
  }
 }
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::RestorePixel()
{
 int i;
 int tmp;
 StoredPixel *spF,*spN;
 if(ArcImage==true || ChordImage==true || LineImage==true || EllipseImage==true || RectangleImage==true || FillRectangle==true || FillEllipse==true || SelectImage==true)
 {
  if(listPixel->Count!=0 && listPixel->Count!=1)
  {
   spF=(StoredPixel*)listPixel->Items[0];
   spN=(StoredPixel*)listPixel->Items[1];

   if((spF->X >= spN->X) && (spF->Y <= spN->Y))
    for(int i=spF->X;i>=spN->X;i--)
     for(int j=spF->Y;j<=spN->Y;j++)
     {
      pCanvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
      bmp->Canvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
     }
   if((spF->X <= spN->X) && (spF->Y >= spN->Y))
    for(int i=spF->X;i<=spN->X;i++)
     for(int j=spF->Y;j>=spN->Y;j--)
     {
      pCanvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
      bmp->Canvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
     }
   if((spF->X >= spN->X) && (spF->Y >= spN->Y))
    for(int i=spF->X;i>=spN->X;i--)
     for(int j=spF->Y;j>=spN->Y;j--)
     {
      pCanvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
      bmp->Canvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
     }
   if((spF->X <= spN->X) && (spF->Y <= spN->Y))
    for(int i=spF->X;i<=spN->X;i++)
     for(int j=spF->Y;j<=spN->Y;j++)
     {
      pCanvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
      bmp->Canvas->Pixels[i][j]=(TColor)RGB(ImageDataR[i][j],ImageDataG[i][j],ImageDataB[i][j]);
     }
  }
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ClearPixel(int k)
{
 int i;
 int count=listPixel->Count;
 StoredPixel *sp;
 for(i=k;i<count;i++)
 {
  sp=(StoredPixel*)listPixel->Items[i];
  delete sp;

 }
 for(i=k;k<count;k++)
  listPixel->Delete(i);
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::DrawFilter(int X, int Y)
{
 int x,y;
 int i,j;

 int r=30;

 if(Liquify==true)
 {
  ReadPixels(bmp);
  CopyMassive();
  for(x=X-r;x<X+r;x++)
   for(y=Y-r;y<Y+r;y++)
   {
    if(x>=0 && x<ImageWidth)
     if(y>=0 && y<ImageHeight)
     {
      i=sqrt(abs(y*y-r*r));
      j=sqrt(abs(x*x-r*r));
      OutputDataR[j+1][i+1]=ImageDataR[x][y];
      OutputDataG[j+1][i+1]=ImageDataG[x][y];
      OutputDataB[j+1][i+1]=ImageDataB[x][y];
     }
   }

  WritePixels(bmp);
  pCanvas->CopyRect(TRect(X-r,Y-r,X+r,Y+r),bmp->Canvas,TRect(X-r,Y-r,X+r,Y+r));

 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::SetFilter(AnsiString FilterName)
{
 UndoRedo->AddUndo(bmp);
 if(FilterName=="Mirror")Filter->Mirror(bmp);
 if(FilterName=="Liquify")
 {
  FilterLiquify=true;
 }
 if(FilterName=="Water")Filter->Water(bmp);
 if(FilterName=="Invert")Filter->Invert(bmp);
 if(FilterName=="Threshold")Filter->Threshold(bmp);
 if(FilterName=="Middle")Filter->MiddleSign(bmp);
 if(FilterName=="Histogram")Filter->TransformHistogram(bmp);
 if(FilterName=="Lowpass")Filter->Lowpass(bmp);
 if(FilterName=="Edge")Filter->Edge(bmp);
 if(FilterName=="Blur")Filter->Blur(bmp);
 if(FilterName=="Sharpen")Filter->Sharpen(bmp);
 if(FilterName=="Embossing")Filter->Embossing(bmp);
 if(FilterName=="WaterColour")Filter->WaterColour(bmp);
 ReadPixels(bmp);
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::ConvertToBitmap()
{
 if(FileType=="Jpeg")
 {
  bmp->Width=jpeg->Width;
  bmp->Height=jpeg->Height;
  bmp->Assign(jpeg);
 }
 if(FileType=="Icon")
 {
  bmp->Canvas->Draw(0,0,icon);
 }
 if(FileType=="Gif")
 {
 }
 if(FileType=="Tiff")
 {
 }
 if(FileType=="Png")
 {
 }
 if(FileType=="Emf")
 {
  bmp->Width=MetaFile->Width;
  bmp->Height=MetaFile->Height;
  bmp->Canvas->Draw(0,0,MetaFile);
 }
 if(FileType=="Wmf")
 {
  bmp->Width=MetaFile->Width;
  bmp->Height=MetaFile->Height;
  bmp->Canvas->Draw(0,0,MetaFile);
 }
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::BitmapConvertTo()
{
 TMetafileCanvas *mfc;
 if(FileType=="Jpeg")
 {

  jpeg=new TJPEGImage;
  jpeg->CompressionQuality=100;
  jpeg->Compress();
  jpeg->Assign(bmp);
 }
 if(FileType=="Icon")
 {
  icon=new TIcon;
  icon->Assign(bmp);
 }
 if(FileType=="Gif")
 {
 }
 if(FileType=="Tiff")
 {
 }
 if(FileType=="Png")
 {
 }
 if(FileType=="Emf")
 {
  if(MetaFile==NULL)MetaFile=new TMetafile;
  MetaFile->Enhanced=true;
  MetaFile->Width=bmp->Width;
  MetaFile->Height=bmp->Height;
  mfc=new TMetafileCanvas(MetaFile,0);
  mfc->Draw(0,0,bmp);
  delete mfc;
 }
 if(FileType=="Wmf")
 {
  if(MetaFile==NULL)MetaFile=new TMetafile;
  MetaFile->Enhanced=false;
  MetaFile->Width=bmp->Width;
  MetaFile->Height=bmp->Height;
  mfc=new TMetafileCanvas(MetaFile,0);
  mfc->Draw(0,0,bmp);
  delete mfc;
 } 
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::DisableFlagDraw()
{
 Arc=false;
 Chord=false;
 Line=false;
 Rectangle=false;
 Ellipse=false;
 FillRectangle=false;
 FillEllipse=false;
 Pen=false;
 Brush=false;
 Text=false;
 Zoom=false;
 ZoomBi=false;
 Move=false;
 Draw=false;
 Select=false;
 SelectAll=false;
 //-----------------Filter---
 FilterLiquify=false;
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::DisableFlagImageDraw()
{
 ArcImage=false;
 ChordImage=false;
 LineImage=false;
 RectangleImage=false;
 EllipseImage=false;
 FillRectangleImage=false;
 FillEllipseImage=false;
 PenImage=false;
 BrushImage=false;
 TextImage=false;
 MoveImage=false;
 SelectImage=false;

 //---------------Filter-------------
 Liquify=false;
}
//------------------------------------------------------------------------------

void __fastcall CBitmap::EnableFlagImageDraw()
{
 if(Arc==true)ArcImage=true;
 if(Chord==true)ChordImage=true;
 if(Line==true)LineImage=true;
 if(Rectangle==true)RectangleImage=true;
 if(Ellipse==true)EllipseImage=true;
 if(FillRectangle==true)FillRectangleImage=true;
 if(FillEllipse==true)FillEllipseImage=true;
 if(Pen==true)PenImage=true;
 if(Brush==true)BrushImage=true;
 if(Text==true)TextImage=true;
 if(Move==true)MoveImage=true;
 if(Draw==true)DrawImage=true;
 if(Select==true)SelectImage=true;

 //---------------Filter-------------
 if(FilterLiquify==true)Liquify=true;
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::FractalMandelbrot()
{
 double c1,c2,z1,z2,tmp,X=1,Y=1;
 double ao,au,bo,bu;
 int i,j,Count;
 TRect R;
 R.Left = 0;
 R.Right = ImageWidth/2;
 R.Top = 0;
 R.Bottom = ImageHeight/2;
 ao= 1;
 au= -2;
 bo= 1.5;
 bu= -1.5;
 //direct scaling cause of speed
 X = (ao - au) / (R.Right - R.Left);
 Y = (bo - bu) / (R.Bottom - R.Top);

 c2=bu;
 for(i=0;i<ImageWidth;i++)
 {
  c1=au;
  for(j=0;j<ImageHeight;j++)
  {
   z1=0;
   z2=0;
   Count=0;
   while(((z1*z1+z2*z2<4) && (Count<=90)))
   {
    tmp=z1;
    z1=z1*z1-z2*z2+c1;
    z2=2*tmp*z2+c2;
    Count++;
   }
   bmp->Canvas->Pixels[j][i]=(TColor)(16*Count % 255);
   c1=c1+X;
  }
  c2=c2+Y;
 }
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::FractalNewton()
{
 Complex z;
 Complex z0;
 Complex z_prev;
 Complex n;
 Complex d;
 Complex P1(0,100000);
 int MaxNumberOfIterations=3,MaxPossibleValue=1024.0005;
 double x,y,Count;
 //-----------------------------
 Count=0;
 for(x=0;x<ImageWidth;x++)
  for(y=0;y<ImageHeight;y++)
  {
   z0.setRe(x*2+100);
   z0.setIm(y*2+100);
   z_prev=z0;
   while(Count < MaxNumberOfIterations)
   {
    n=z_prev*z_prev*z_prev-1;
    d=(z_prev*z_prev)*3+P1;
    z=z_prev-n/d;
    z_prev=z;
    Count++;
   }
   Count=0;
   if(n.mod()==0)bmp->Canvas->Pixels[x][y]=(TColor)0;
   else
   {
    if(n.mod()==MaxPossibleValue)bmp->Canvas->Pixels[x][y]=(TColor)1024;
    else bmp->Canvas->Pixels[x][y]=(TColor)n.mod()/(MaxNumberOfIterations*1024);
   }
  }
}
//------------------------------------------------------------------------------
void __fastcall CBitmap::FractalTeylor()
{
// double maxiter=15;
// double tolerance=1e-6;
 double xmax,xdev,xavg;
 double ymax,ydev,yavg;
 double mmax,mdev,mavg;
 double zSum;
 double denominator;
 double point;
}
//------------------------------------------------------------------------------
#pragma package(smart_init)

