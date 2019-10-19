#include "StdAfx.h"
#include "FileImage.h"

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------FileImage------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileImage::FileImage(void)
{
	image = new Image();

	imageType = NONAME;

	hasPaletteFlag = false;
}

//-------------------------------------------------------------------------------------------------------------
FileImage::FileImage(const string filename)
{
	image = new Image();

	imageType = NONAME;

	hasPaletteFlag = false;

	this->filename = filename;
}

//-------------------------------------------------------------------------------------------------------------
FileImage::~FileImage(void)
{
	if( image != NULL )delete image;
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::flipImage(unsigned char *data, int width, int height, int bits)
{
        unsigned char bTemp;
        unsigned char *pLine1, *pLine2;
        int iLineLen,iIndex;

        iLineLen = width * (bits / 8);

        pLine1 = data;

        pLine2 = &data[iLineLen * (height - 1)];

        for( ;pLine1<pLine2;pLine2-=(iLineLen*2))
        {
             for(iIndex=0;iIndex!=iLineLen;pLine1++,pLine2++,iIndex++)
             {
                    bTemp = *pLine1;
                    *pLine1 = *pLine2;
                    *pLine2 = bTemp;
             }
        }
}

//-------------------------------------------------------------------------------------------------------------
bool FileImage::hasPalette()
{
	return hasPaletteFlag;
}

//-------------------------------------------------------------------------------------------------------------
Image* FileImage::getImage()
{
	return image;
}

//-------------------------------------------------------------------------------------------------------------
int FileImage::getImageType()
{
	return imageType;
}

//-------------------------------------------------------------------------------------------------------------
string FileImage::getFilename()
{
	return filename;
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::setImage(Image *image)
{
	this->image = image;
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::setImageType(int type)
{
	imageType = type;
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::setFilename(const string filename)
{
	this->filename = filename;
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::open()
{
	file.open(filename.c_str(), ios::in);
}

//-------------------------------------------------------------------------------------------------------------
void FileImage::close()
{
	file.close();
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------FileImageFactory-----------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileImageFactory::FileImageFactory(void)
{
}

//-------------------------------------------------------------------------------------------------------------
FileImageFactory::~FileImageFactory(void)
{
}

//-------------------------------------------------------------------------------------------------------------
Image* FileImageFactory::CreateImage(int type, const std::string filename)
{
	return CreateFileImage(type, filename)->getImage();
}

//-------------------------------------------------------------------------------------------------------------
FileImage* FileImageFactory::CreateFileImage(int type, const std::string filename)
{
	switch(type)
	{
		case BMP: return new FileBitmap(filename);
		case GIF: return new FileGIF(filename);
		case JPG: return new FileJPG(filename);
		case PCX: return new FilePCX(filename);
		case PNG: return new FilePNG(filename);
		case TGA: return new FileTGA(filename);
		default: return new FileBitmap(filename);
	}
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FileBitmap---------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileBitmap::FileBitmap(void) : FileImage()
{
	imageType = BMP;
}

//-------------------------------------------------------------------------------------------------------------
FileBitmap::FileBitmap(const string filename) : FileImage(filename)
{
	imageType = BMP;
}

//-------------------------------------------------------------------------------------------------------------
FileBitmap::~FileBitmap()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FileBitmap::hasPalette()
{
	if( header.infoHeader.bits == 8 )return true;

	return false;
}

//-------------------------------------------------------------------------------------------------------------
int FileBitmap::getImageType()
{
	switch(header.infoHeader.bits)
	{
		case 8: return BMP8;
		case 24: return BMP24;
		case 32: return BMP32;
		default: return BMP;
	}
}

//-------------------------------------------------------------------------------------------------------------
void FileBitmap::readHeader()
{
	if( !file )return;

	//read file header
    file.read((char*)&header.fileHeader.sign, sizeof(header.fileHeader.sign));
    file.read((char*)&header.fileHeader.size, sizeof(header.fileHeader.size));
    file.read((char*)&header.fileHeader.reserved1, sizeof(header.fileHeader.reserved1));
    file.read((char*)&header.fileHeader.reserved2, sizeof(header.fileHeader.reserved2));
    file.read((char*)&header.fileHeader.location, sizeof(header.fileHeader.location));

    //read file info header
    file.read((char*)&header.infoHeader.headerSize, sizeof(header.infoHeader.headerSize));
    file.read((char*)&header.infoHeader.width, sizeof(header.infoHeader.width));
    file.read((char*)&header.infoHeader.height, sizeof(header.infoHeader.height));
    file.read((char*)&header.infoHeader.planes, sizeof(header.infoHeader.planes));
    file.read((char*)&header.infoHeader.bits, sizeof(header.infoHeader.bits));
    file.read((char*)&header.infoHeader.compress, sizeof(header.infoHeader.compress));
    file.read((char*)&header.infoHeader.num, sizeof(header.infoHeader.num));
    file.read((char*)&header.infoHeader.horizontal, sizeof(header.infoHeader.horizontal));
    file.read((char*)&header.infoHeader.vertical, sizeof(header.infoHeader.vertical));
    file.read((char*)&header.infoHeader.numColors, sizeof(header.infoHeader.numColors));
    file.read((char*)&header.infoHeader.numIColors, sizeof(header.infoHeader.numIColors));
	
	image->setWidth(header.infoHeader.width);
	image->setHeight(header.infoHeader.height);   

	imageType = getImageType();

	hasPaletteFlag = hasPalette();
}

//-------------------------------------------------------------------------------------------------------------
void FileBitmap::readPalette()
{
	if( !file )return;

	if( hasPaletteFlag )
	{
		file.read((char*)&palette, sizeof(palette));
	}
}

//-------------------------------------------------------------------------------------------------------------
void FileBitmap::readData()
{
	if( !file )file.open(filename.c_str(), ios::in);

	int imageSize = header.infoHeader.width * header.infoHeader.height * (header.infoHeader.bits /8 );

	unsigned char *pixels = new unsigned char[imageSize];      

    file.seekg(header.fileHeader.location);

    file.read((char*)pixels, imageSize);

    flipImage(pixels, header.infoHeader.width, header.infoHeader.height, header.infoHeader.bits);

    if( imageType = BMP8 )
    {
		if( header.infoHeader.compress == 1 )
        {
			unsigned char *data = NULL;
			
			RLEImageCompressor::decompress(pixels, data, imageSize);

			BMPImageConverter::BMP8ToRGB(image, data, (unsigned char**)&palette, header.infoHeader.bits);
        }
		else BMPImageConverter::BMP8ToRGB(image, pixels, (unsigned char**)&palette, header.infoHeader.bits);		
    }

    if( imageType == BMP24 || imageType == BMP32 )BMPImageConverter::BMP24ToRGB(image, pixels, header.infoHeader.bits);        
    
	delete[] pixels;
}

//-------------------------------------------------------------------------------------------------------------
void FileBitmap::read()
{
	open();

	readHeader();

	readPalette();

    readData();

    close();
}

//-------------------------------------------------------------------------------------------------------------
void FileBitmap::write()
{
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FileGIF--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileGIF::FileGIF() : FileImage()
{
	imageType = GIF;
}

FileGIF::FileGIF(const string filename) : FileImage(filename)
{
	imageType = GIF;
}

FileGIF::~FileGIF()
{
}

void FileGIF::readHeader()
{
	if( !file )return;

	file.read((char*)&header.Sign, sizeof(header.Sign));
    file.read((char*)&header.Version, sizeof(header.Version));
    file.read((char*)&header.ScreenWidth, sizeof(header.ScreenWidth));
    file.read((char*)&header.ScreenHeight, sizeof(header.ScreenHeight));
    file.read((char*)&header.Packed, sizeof(header.Packed));
    file.read((char*)&header.BackgroundColor, sizeof(header.BackgroundColor));
    file.read((char*)&header.AspectRatio, sizeof(header.AspectRatio));
}

void FileGIF::readPalette()
{
}

void FileGIF::readData()
{
}

void FileGIF::read()
{
	open();

	readHeader();

	readPalette();

	readData();

	close();
}

void FileGIF::write()
{
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FileJPG--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileJPG::FileJPG() : FileImage()
{
	imageType = JPG;
}

FileJPG::FileJPG(const string filename) : FileImage(filename)
{
	imageType = JPG;
}

FileJPG::~FileJPG()
{
}

void FileJPG::readHeader()
{
}

void FileJPG::readPalette()
{
}

void FileJPG::readData()
{
}

void FileJPG::read()
{
	open();

	readHeader();

	readPalette();

	readData();

	close();
}

void FileJPG::write()
{
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FilePCX--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FilePCX::FilePCX() : FileImage()
{
	imageType = PCX;
}

FilePCX::FilePCX(const string filename) : FileImage(filename)
{
	imageType = PCX;
}

FilePCX::~FilePCX()
{
}

//------------------------------------------------------------------------------
int FilePCX::getImageType()
{
	 int MaxNumColors = (1L << (header.BitsPerPixel * header.NumBitPlanes) );

     if( header.NumBitPlanes == 1 && header.BitsPerPixel == 1 && MaxNumColors == 2 )return PCX_Mono;

     if( header.NumBitPlanes == 1 && header.BitsPerPixel == 2 && MaxNumColors == 4 )return PCX_CGA;

     if( header.NumBitPlanes == 3 && header.BitsPerPixel == 1 && MaxNumColors == 8 )return PCX_EGA;

     if( header.NumBitPlanes == 4 && header.BitsPerPixel == 1 && MaxNumColors == 16 )return PCX_VGA;

     if( header.NumBitPlanes == 1 && header.BitsPerPixel == 8 && MaxNumColors == 256 )return PCX_EVGA;

     if( header.NumBitPlanes == 3 && header.BitsPerPixel == 8 && MaxNumColors == 16777216 )return PCX_EVGA;

     return 0;                                
}

//-------------------------------------------------------------------------------------------------------------
void FilePCX::readHeader()
{
		if( !file )return;
        
        file.read((char*)&header.Manuf, sizeof(header.Manuf));
        file.read((char*)&header.Version, sizeof(header.Version));
        file.read((char*)&header.Encoding, sizeof(header.Encoding));
        file.read((char*)&header.BitsPerPixel, sizeof(header.BitsPerPixel));
        file.read((char*)&header.x1, sizeof(header.x1));
        file.read((char*)&header.y1, sizeof(header.y1));
        file.read((char*)&header.x2, sizeof(header.x2));
        file.read((char*)&header.y2, sizeof(header.y2));
        file.read((char*)&header.HorzRes, sizeof(header.HorzRes));
        file.read((char*)&header.VertRes, sizeof(header.VertRes));
        file.read((char*)&header.Palette, sizeof(header.Palette));
        file.read((char*)&header.Reserved1, sizeof(header.Reserved1));
        file.read((char*)&header.NumBitPlanes, sizeof(header.NumBitPlanes));
        file.read((char*)&header.BytesPerLine, sizeof(header.BytesPerLine));
        file.read((char*)&header.PaletteType, sizeof(header.PaletteType));
        file.read((char*)&header.HorzScreenSize, sizeof(header.HorzScreenSize));
        file.read((char*)&header.VertScreenSize, sizeof(header.VertScreenSize));
        file.read((char*)&header.Reserved2, sizeof(header.Reserved2));

		image->setWidth(header.x2 - header.x1 + 1);
		image->setHeight(header.y2 - header.y1 + 1);

		imageType = getImageType();
}

//-------------------------------------------------------------------------------------------------------------
void FilePCX::readPalette()
{	
        unsigned char byte;

		if( !file )return;

        file.seekg(0, ios::end);                   //go to end file

        if( (int)file.tellg() - 769  < 0 )
        {          
                file.seekg(128, ios::beg);

				hasPaletteFlag = true;

                return;
        }		

        file.seekg( (int)file.tellg() - 769, ios::beg); //move up on 769 byte

        file.read((char*)&byte, sizeof(byte));     //get byte

        if( byte == 10 || byte == 12 || byte == 0xC0)
        {
                file.read((char*)&palette, sizeof(palette)); //read palette	

                hasPaletteFlag = true;
        }
        else hasPaletteFlag = false;
				
		file.seekg(128, ios::beg);
}

//-------------------------------------------------------------------------------------------------------------
void FilePCX::readData()
{
        int i;
        int imageSize;
        unsigned char byte;
        unsigned int  num;

        if( !file )return;

		i = 0;

        imageSize = image->getWidth() * image->getHeight() * header.NumBitPlanes;

        unsigned char *pixels = new unsigned char[imageSize];

        while(/*!file.eof() &&*/ i < imageSize)
        {
                file.read((char*)&byte, sizeof(byte));

                num = byte & 0x3F;

                if( (byte & 0xC0) == 0xC0 )                  //if 1 and 2 bit of byte == 1 (example 11000000)
                {
                        file.read((char*)&byte, sizeof(byte));

                        for(unsigned int k = 0; k < num; k++)
                        {
                                pixels[i] = byte;
                                i++;
                        }
                }
                else
				{ 
					pixels[i] = byte; 
					i++; 
				}
        }

		//Monochrome image -- work
        if( imageType == PCX_Mono )PCXImageConverter::PCXMonoToRGB(image, pixels, header.BytesPerLine);                

		//CGA image -- no work
        if( imageType == PCX_CGA )PCXImageConverter::PCXCgaToRGB(image, pixels, (unsigned char**)&header.Palette);        

		//EGA image -- no work
        if( imageType == PCX_EGA )PCXImageConverter::PCXEgaToRGB(image, pixels, (unsigned char**)&header.Palette, header.BytesPerLine);

		//VGA image -- no work
        if( imageType == PCX_VGA )PCXImageConverter::PCXVgaToRGB(image, pixels, (unsigned char**)&palette, header.BytesPerLine, hasPaletteFlag);    	
        
		//EVGA image
		if( imageType == PCX_EVGA )PCXImageConverter::PCXEvgaToRGB(image, pixels, (unsigned char**)&palette, header.BytesPerLine, header.NumBitPlanes, hasPaletteFlag);
        
		delete[] pixels;
}

//-------------------------------------------------------------------------------------------------------------
void FilePCX::read()
{
        open();

        readHeader();

        readPalette();

        readData();        

		close();
}

//-------------------------------------------------------------------------------------------------------------
void FilePCX::write()
{
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FilePNG--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FilePNG::FilePNG() : FileImage()
{
	imageType = PNG;
}

FilePNG::FilePNG(const string filename) : FileImage(filename)
{
	imageType = PNG;
}

FilePNG::~FilePNG()
{
}

void FilePNG::readHeader()
{
}

void FilePNG::readData()
{
}

void FilePNG::readPalette()
{
}

void FilePNG::read()
{
	open();

	readHeader();

	readPalette();

	readData();

	close();
}

void FilePNG::write()
{
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------------FileTGA--------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FileTGA::FileTGA() : FileImage()
{
	imageType = TGA;
}

//-------------------------------------------------------------------------------------------------------------
FileTGA::FileTGA(const string filename) : FileImage(filename)
{
	imageType = TGA;
}

//-------------------------------------------------------------------------------------------------------------
FileTGA::~FileTGA()
{
}

//-------------------------------------------------------------------------------------------------------------
bool FileTGA::hasPalette()
{
	switch(imageType)
	{
		case TGA_INDEX:      return true;
		case TGA_RGB:	     return false;
		case TGA_RLE_INDEX:  return true;
		case TGA_RLE_RGB:	 return false;
		default: return false;
	}
}

//-------------------------------------------------------------------------------------------------------------
int FileTGA::getImageType()
{
	switch(header.imageType.encoding)
	{
		case 1:  return TGA_INDEX;
		case 2:  return TGA_RGB;
		case 9:  return TGA_RLE_INDEX;
		case 10: return TGA_RLE_RGB;
		default: return TGA;
	}
}

//-------------------------------------------------------------------------------------------------------------
void FileTGA::readHeader()
{
	if (!file )return;

	file.read((char*)&header.imageType.v0, sizeof(header.imageType.v0));
	file.read((char*)&header.imageType.type, sizeof(header.imageType.type));
	file.read((char*)&header.imageType.encoding, sizeof(header.imageType.encoding));
	file.read((char*)&header.paletteInfo.start, sizeof(header.paletteInfo.start));
	file.read((char*)&header.paletteInfo.end, sizeof(header.paletteInfo.end));
	file.read((char*)&header.coord.x1, sizeof(header.coord.x1));
	file.read((char*)&header.coord.y1, sizeof(header.coord.y1));
	file.read((char*)&header.coord.x2, sizeof(header.coord.x2));
	file.read((char*)&header.coord.y2, sizeof(header.coord.y2));
	file.read((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));

	image->setWidth(header.coord.x2 - header.coord.x1 + 1);
	image->setHeight(header.coord.y2 - header.coord.y1 + 1);

	imageType = getImageType();

	hasPaletteFlag = hasPalette();
}

//-------------------------------------------------------------------------------------------------------------
void FileTGA::readPalette()
{
	if( hasPaletteFlag )
	{
		if( !file )return;

		file.seekg(18);
		
		file.read((char*)&palette, sizeof(palette));
	}
}

//-------------------------------------------------------------------------------------------------------------
void FileTGA::readData()
{
	int imageSize = image->getWidth() * image->getHeight() * header.bitsPerPixel / 8;

	unsigned char *pixels = new unsigned char[imageSize];

	file.read((char*)pixels, imageSize);
	
	if( imageType == TGA_INDEX )TGAImageConverter::TGAIndexToRGB(image, pixels, (unsigned char**)&palette, header.bitsPerPixel);

	if( imageType == TGA_RGB )TGAImageConverter::TGARgbToRGB(image, pixels, header.bitsPerPixel);

	if( imageType == TGA_RLE_INDEX )
	{
		unsigned char *data = NULL;

		RLEImageCompressor::decompress(pixels, data, imageSize);	

		TGAImageConverter::TGAIndexToRGB(image, data, (unsigned char**)&palette, header.bitsPerPixel);
	}

	if( imageType == TGA_RLE_RGB )
	{
		unsigned char *data = NULL;

		RLEImageCompressor::decompress(pixels, data,imageSize);	

		TGAImageConverter::TGARgbToRGB(image, data, header.bitsPerPixel);
	}
	delete[] pixels;
}

//-------------------------------------------------------------------------------------------------------------
void FileTGA::read()
{
	open();

	readHeader();

	readPalette();

	readData();

	close();
}

//-------------------------------------------------------------------------------------------------------------
void FileTGA::write()
{
}