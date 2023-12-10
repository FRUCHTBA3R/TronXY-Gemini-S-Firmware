#pragma once

#include "yLabel.hpp"

typedef struct
{
	int lineHighest;
	uint16_t* word;
}TPAD;

class yTablet : virtual public yWords
{
	public:
		yTablet(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr){
			Column = 0;
			Row = 0;
			Pad = 0;
			margin = 1;
		}
		virtual ~yTablet(){freePad();}
		virtual uint8_t update(uint8_t force = 0);
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.text = 0;
		}

		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || (Pad && sign.content.text == 0);}
		void addChars(const char*str);//Add string to Notepad
		void addChars(const uint16_t*tar);
		void setBuffSpace(int row,int column);
		int margin;//text distance from border

	private:
		uint8_t Column,Row;//How many columns and rows are there in total?
		uint8_t curRow,curColumn;//Cursor position: row and column
		int curXPixel;//Cursor column pixel position (used to calculate whether it crosses the boundary)
		TPAD *Pad;
		void freePad();
		void allocPad();//This function should be called after setting whether utf16 is true
		void lineFeed();//newline
};

