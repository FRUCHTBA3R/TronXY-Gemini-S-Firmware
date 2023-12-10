#pragma once

#include "yFigure.hpp"
#include "yPicture.hpp"
#define ALIGN_CONTENT_LENGTH  9 //1 newline character, M10086; 8 alignment characters
class yFigureSd : public yFigure
{
    public:
        yFigureSd(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
        {
            sdfileName = nullptr;
            picSign = nullptr; //Figure identification
            picOffsetFromFile = 0; //The location of the picture information in the SD file (you can quickly find the picture)
            picXOffset = 0;
            picYOffset = 0;
        }
        virtual ~yFigureSd();
        virtual uint8_t update(uint8_t force = 0);
        // inline virtual void setfocus(uint8_t tf) {
        //     yFigure::setfocus(tf);
        // }
        uint8_t updateSdpic(uint8_t force = 0);
        void setSdpicInfo(const char* name,const char*sign, uint32_t offset, int width, int height);
        void clearSdpicInfo();
        inline void setSdpicOffset(int x,int y) {picXOffset = x; picYOffset = y;}
        //Detect whether there is an sdpic. If so, return its image offset. When 0xFFFFFFFE is returned, the file cannot be opened. When 0xFFFFFFFF is returned, there is no sdpic.
        static uint32_t sdpicCheck(const char*fname,const char* sign,uint32_t picOffset);
        static void exeSdpic(const char*fname,int xsize,int ysize, uint32_t& foffset, void (*)(const void*,int));
    private:
        char *sdfileName, *picSign;
        int picXOffset, picYOffset;
        int picXSize, picYSize;
        uint32_t picOffsetFromFile;
};
