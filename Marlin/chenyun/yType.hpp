#pragma once

#include <inttypes.h>

typedef void (*VoidFun)(void);
typedef uint16_t color_t;

typedef struct
{
	int x;
	int y;
}POS;

typedef struct WINRECT
{
	int  xStart;
	int  yStart;
	int  xEnd;
	int  yEnd;
}WRECT;
	
typedef struct //BMP head
{
	uint16_t bfType;    //File type, BMP format is string BM
	uint32_t bfSize;		//The size of the entire image file, in bytes
	uint16_t bfReserved1;	//Reserved bit
	uint16_t bfReserved2;	//Reserved bit
	uint32_t bfOffBits;  	//Byte offset from file header to actual image data
} bmpHead_t;

typedef struct //BMP information, followed by BMP header
	{
		uint32_t     biSize;//The size of the space occupied by the BMP information header (that is, this structure) (in bytes)
		long    biWidth;//Image width
		long    biHeight;//Picture height (this value can also indicate whether the bitmap is inverted or forward. If it is a positive number [most of the time], it is an inverted bitmap. If it is a negative number, it is a forward bitmap.)
		uint16_t     biPlanes;//Target device color plane number, always 1
		uint16_t     biBitCount;
		//Bitmap type, indicating how many bits are used to represent each pixel, unit: bit/pixel, its value can be 1, 4, 8, 16, 24 or 32
		uint32_t     biCompression;
		//Compression type
		//0-BI_RGB no compression
		//1-BI_RLE8 8bit Run-length encoding, only used for 8-bit bitmaps
		//2-BI_RLE4 4bit Run-length encoding, only used for 4-bit bitmaps
		//3-BI_BITFIELDS bit Domain, only used for 16/32-bit bitmaps
		//4-BI_JPEG		Bitmap with JPEG image (for printers only)
		//5-BI_PNG		Bitmap with PNG image (for printer only)
		uint32_t     biSizeImage;//Image size, in bytes. If biCompression is BI_RGB, it can be set to 0 here.
		long    biXPelsPerMeter;//Horizontal resolution, unit: pixel/meter
		long    biYPelsPerMeter;//Vertical resolution, unit: pixel/meter
		uint32_t     biClrUsed;
		//The actual number of color indexes in the color table used (set to 0 to indicate that all palette items are used)
		//This will determine the size of the palette
		uint32_t     biClrImportant;
		//Indicates the number of color indexes that have an important impact on the image display. If it is 0, it means that they are all important.
		//Refers to the important index in the palette. Early graphics cards may not be able to display all the colors in the palette, so the important colors are placed in front. This amount indicates how many are important.
	}bmpInfo_t;
//The palette can be viewed as an array of the following data types, representing a set of colors
//If there is a palette, each value in the data area represents an array subscript in the palette, and the color represented by the corresponding array element is the color corresponding to that value in the data area.

typedef struct{
	uint8_t ifErom;
	uint8_t zero;//If it is an ascii code font, it is the first character
	uint16_t wNum;//How many characters are included in total?
	int16_t xPixel;//x pixel length (characters must be of valid length), solid color is invalid here
	int16_t yPixel;//y pixel length, solid color is invalid here
	uint16_t bytesPerLine;//How many bytes are there in a row of pixels? Solid color is not valid here.
	int vSpace;//The size of the space occupied by the image data
	uint32_t value;//Picture: address, solid color: when it is 16-bit color, the lower 16 bits are the fill color, when it is 32-bit, it represents the fill color
}PicAttr;

typedef struct {
	int ifErom : 1;
	int former : 1;
	int background : 1;
	int frame : 1;
	int other : 4;
	uint8_t transparent;//transparency value
	color_t frameColor;//border color
	color_t bgStart;//scale starting color
	color_t bgEnd;//scale end color
}ScaleAttr;

typedef struct
{
  bmpHead_t head;
  bmpInfo_t info;
}BMPHead;

enum {
TYPE_BINARY, //Binary color image (ascii font library), vSpace represents the size of a binary image (character), wNum represents the number of images (characters) contained
TYPE_COLOR, //Solid color filling, variable, value1 is the starting color, value2 is the end color
TYPE_PIE, //draw a circle
TYPE_PIC, //Picture, value can find the picture pixels
TYPE_CPIC,//Compressed image
TYPE_SELFFUN //It is a solid color custom drawing, and the value points to the drawing function.
};

typedef struct //16
{//If it is a character, use the horizontal modulus
	struct
	{
		uint8_t ifERom:1;//Whether to use external ROM, if so, 1, otherwise 0
		uint8_t type:3;//See macro definition above
		uint8_t typeTf:1;
		//When type==TYPE_BINARY, 1 Chinese, 0 ascii code
		//When type==TYPE_CPIC, 0 whole, 1 line
		uint8_t black_tf:1;//1 black and transparent
		uint8_t ifFrame:1;//Whether to display borders
		uint8_t former:1;//After setting it to 1, when updating this control, the control below it needs to be redrawn.
	}attr;
	uint8_t zero;
	//If it is an ascii code font, it is the first character
	//If it is a Chinese character library, it is the offset between the glyph code and the Chinese code, usually 3
	//Otherwise, the background transparency is 0~255
	uint16_t wNum;//How many characters are included in total? This must be 1 for ordinary pictures or solid colors.
	int16_t xPixel;//x pixel length (characters must be of valid length), solid color is invalid here
	int16_t yPixel;//y pixel length, solid color is invalid here
	uint16_t bytesPerLine;//How many bytes are there in a row of pixels? Solid color is not valid here.
	//For example, 24*24 Chinese characters, here is 3, because each line has 24 pixels, and each bit represents one pixel, so each line requires 3 bytes to represent
	//If it is a 16-bit color image, each pixel is 2 bytes, then a 200*200 image line will be represented by 400 bytes per line.
	int vSpace;//Picture: the size of the space occupied by the image data, characters: the size of the space occupied by each character, solid color is invalid here
	uint32_t value;//Picture: address, solid color: when it is 16-bit color, the lower 16 bits are the fill color, when it is 32-bit, it represents the fill color
}PICinfo;

typedef struct //16
{//If it is a character, use the horizontal modulus
	uint8_t ifErom;
	uint8_t zero;
	//If it is an ascii code font, it is the first character
	//If it is a Chinese character library, it is the offset between the glyph code and the Chinese code, usually 3
	//Otherwise, the background transparency is 0~255
	uint16_t wNum;//How many characters are included in total? This must be 1 for ordinary pictures or solid colors.
	int16_t xPixel;//x pixel length (characters must be of valid length), solid color is invalid here
	int16_t yPixel;//y pixel length, solid color is invalid here
	uint16_t bytesPerLine;//How many bytes are there in a row of pixels? Solid color is not valid here.
	//For example, 24*24 Chinese characters, here is 3, because each line has 24 pixels, and each bit represents one pixel, so each line requires 3 bytes to represent
	//If it is a 16-bit color image, each pixel is 2 bytes, then a 200*200 image line will be represented by 400 bytes per line.
	int vSpace;//Picture: the size of the space occupied by the image data, characters: the size of the space occupied by each character, solid color is invalid here
	uint32_t value;//Picture: address, solid color: when it is 16-bit color, the lower 16 bits are the fill color, when it is 32-bit, it represents the fill color
}PicInfo;

typedef struct
{
	uint8_t ifOpaque;//Whether the background is transparent
	color_t fr,bg;//Foreground and background colors
	int x,y;//Coordinates when displaying characters (upper left corner)
	const PICinfo*pic;
}BinaryInfo;

#define COLOR16_TO_RGB565(color,R,G,B) do{R = (color) >> 11; G = ((color) >> 5) & 0x003F; B = (color) & 0x001F;}while(0)
#define RGB565_TO_COLOR16(R,G,B) (((R > 0x1F ? (uint16_t)0x001F : (uint16_t)R) << 11) | ((G > 0x3F ? (uint16_t)0x003F : (uint16_t)G) << 5) | (B > 0x1F ? (uint16_t)0x001F : (uint16_t)B))
#define	yMAX(a,b)	(a>b?a:b)
#define	yMIN(a,b)	(a>b?b:a)

#define _NAME_X(x)   #x
#define NAME_X(x)    _NAME_X(x) //Expand the x macro definition into a string
