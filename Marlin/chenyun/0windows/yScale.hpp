
#pragma once
#include "../yCommon.h"

#define WIDGET_FRAME_COLOR               0xEE0E
#define HORIZONTAL_LINE(y,xStart,xEnd)  LCD_WArea(xStart,y,xEnd,y);LCD_BatchStart(LCD_LBuffer2,xEnd - xStart + 1,0)
#define VERTICAL_LINE(x,yStart,yEnd)    LCD_WArea(x,yStart,x,yEnd);LCD_BatchStart(LCD_LBuffer2,yEnd - yStart + 1,0)

enum TouchEvent
{
	tevt_none = 0,
	tevt_touch,
	tevt_untouch,
	tevt_away,
};
class yWidget
{
	public:
		yWidget(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yWidget(){}

	protected:
		uint8_t focus;
		uint8_t focusAllUpdate;//Default is 1
		//After setting it to 0, when calling setfocus, only the widget will be updated, and the inherited components will not be updated. This is mainly for controls that add transparent color when the control is pressed.
		//When lifted, all will be updated
		const ScaleAttr* scaAttrIdle,*scaAttrFocus,*scaAttr;
		int wXStart,wYStart,wXEnd,wYEnd;//The scope of this control

	public:
		union {
			struct {
				int scale:1;
				int simulation:1;
				int picture:1;//Not displayed for the first time, generally used when you need to brush the background for the first time and display the text for the second time.
				int text:1;
				int other:4;
			}content;//Mark here which parts of the update are drawn, see macro definition
			uint8_t all;
		}sign;
		uint8_t colorVertical;
		uint8_t touchChoose;//0:Does not respond to touch. 1. Once touched, it will respond regardless of whether it touches this control. 2. It will only respond if this control is touched.
		uint8_t funParam;
		static WRECT VisualRect;//visible area
		virtual uint8_t update(uint8_t force = 0);//Refresh the interface and return true to indicate that the visible area of ​​the control is not displayed.
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
		}
		void (*fun)(yWidget*w,TouchEvent evt);//This function will be called immediately after a touch event occurs
		uint8_t (*funNext)();//After a touch occurs, after calling fun, calling this function outside may release this control.
		inline virtual void setfocus(uint8_t tf) {
			if(tf && !focus) {
				focus = 1;
				scaAttr = scaAttrFocus;
				sign.content.scale = 1;
			}
			else if(!tf && focus) {
				focus = 0;
				scaAttr = scaAttrIdle;
				sign.content.scale = 1;
			}
		}
		inline void disableFocusAllUpdate(bool en){if(en)focusAllUpdate = 0;else focusAllUpdate = 1;}
		inline virtual uint8_t enUpdate(void) { return !!scaAttr && sign.content.scale == 0; }
		void setRectOffset(int x,int y);
		//Find the intersection of wgRect and VisualRect
		inline uint8_t boundIntersect(int& xStart,int& yStart,int& xEnd,int& yEnd)
		{
			xStart = yMAX(wXStart, VisualRect.xStart);
			xEnd = yMIN(wXEnd, VisualRect.xEnd);
			yStart = yMAX(wYStart, VisualRect.yStart);
			yEnd = yMIN(wYEnd, VisualRect.yEnd);
			return (xEnd < xStart || yStart > yEnd);
		}
		inline uint8_t range(int x,int y,int r = 0){
			return (x >= wXStart + r && x <= wXEnd - r) && (y >= wYStart + r && y <= wYEnd - r);
		}

	protected:
		inline void horizontalLine(color_t color,int xStart,int xEnd,int y)
			{//Draw a horizontal line on the screen
				if(y < wYStart || y < VisualRect.yStart || y > wYEnd || y > VisualRect.yEnd)return;
				if(xStart < wXStart)xStart = wXStart;
				if(xStart < VisualRect.xStart)xStart = VisualRect.xStart;
				if(xEnd > wXEnd)xEnd = wXEnd;
				if(xEnd > VisualRect.xEnd)xEnd = VisualRect.xEnd;
				if(xStart > xEnd)return;
				while(LCD_Busy()){}
				LCD_LBuffer2[0] = color;//You must use global variables to save the color. Otherwise, the color will be released after the function returns, and the color transferred by DMA will not be accurate.
				HORIZONTAL_LINE(y,xStart,xEnd);
			}
		inline void verticalLine(color_t color,int x,int yStart,int yEnd)
			{//在屏幕上绘制一条竖线
				if(x < VisualRect.xStart || x < wXStart || x > VisualRect.xEnd || x > wXEnd)return;
				if(yStart < wYStart)yStart = wYStart;
				if(yStart < VisualRect.yStart)yStart = VisualRect.yStart;
				if(yEnd > wYEnd)yEnd = wYEnd;
				if(yEnd > VisualRect.yEnd)yEnd = VisualRect.yEnd;
				if(yStart > yEnd)return;
				while(LCD_Busy()){}
				LCD_LBuffer2[0] = color;//You must use global variables to save the color. Otherwise, the color will be released after the function returns, and the color transferred by DMA will not be accurate.
				VERTICAL_LINE(x,yStart,yEnd);
			}
		inline void frame(color_t color,int xStart,int yStart,int xEnd,int yEnd) {
			verticalLine(color,xStart,yStart,yEnd);
			verticalLine(color,xEnd,yStart,yEnd);
			horizontalLine(color,xStart,xEnd,yStart);
			horizontalLine(color,xStart,xEnd,yEnd);
		}
		void rect(color_t color,int xStart,int yStart,int xEnd,int yEnd);
		void horizonRect(color_t color_start,color_t color_end);
		void verticalRect(color_t color_start,color_t color_end);
		void line(color_t color,int xStart,int yStart,int xEnd,int yEnd);//draw line

	protected:
		//Find the intersection of x, y and VisualRect
		static inline uint8_t boundIntersect2(int& xStart,int& yStart,int& xEnd,int& yEnd)
		{
			if(xStart < VisualRect.xStart)xStart = VisualRect.xStart;
			if(xEnd > VisualRect.xEnd)xEnd = VisualRect.xEnd;
			if(yStart < VisualRect.yStart)yStart = VisualRect.yStart;
			if(yEnd > VisualRect.yEnd)yEnd = VisualRect.yEnd;
			return (xEnd < xStart || yStart > yEnd);
		}
		//Find the intersection of x and y with wgRect and VisualRect
		inline uint8_t boundIntersect3(int* xStart,int* yStart,int* xEnd,int* yEnd)
		{
			if(wXStart < VisualRect.xStart)
			{
				if(*xStart < VisualRect.xStart)*xStart = VisualRect.xStart;
			}
			else
			{
				if(*xStart < wXStart)*xStart = wXStart;
			}
			if(wYStart < VisualRect.yStart)
			{
				if(*yStart < VisualRect.yStart)*yStart = VisualRect.yStart;
			}
			else
			{
				if(*yStart < wYStart)*yStart = wYStart;
			}
			if(wXEnd > VisualRect.xEnd)
			{
				if(*xEnd > VisualRect.xEnd)*xEnd = VisualRect.xEnd;
			}
			else
			{
				if(*xEnd > wXEnd)*xEnd = wXEnd;
			}
			if(wYEnd > VisualRect.yEnd)
			{
				if(*yEnd > VisualRect.yEnd)*yEnd = VisualRect.yEnd;
			}
			else
			{
				if(*yEnd > wYEnd)*yEnd = wYEnd;
			}
			return (*xStart > *xEnd || *yStart > *yEnd);
		}
};
