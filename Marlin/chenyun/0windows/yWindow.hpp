#pragma once

#include "yScale.hpp"
typedef struct __attribute__((__packed__)) {
  int x;
  int y;
  short offset_x;
  short offset_y;
} Touch_t;

class yWindow {
	public:
		//Note that the position of the control will be changed here. Therefore, when the control has boundary judgment (such as addChars), you need to call yWindow at the end.
		yWindow(int x, int y, int width, int height, yWidget *components[], int componentsNum, yWindow* parent = nullptr);
		~yWindow();

		yWindow* Parent;
		void refreshComponents();//Refresh this window
		void update();//Refresh windows (including parent windows)

		uint8_t needFresh();
		void clrUpdateSign();//After drawing the window once, clear all the marks that need to be drawn, wait for other applications to mark the corresponding marks before redrawing, and the top window pointer must be executed.
		void setUpdateSign();
		void move(int x,int y);
		yWidget* getComponent(int index){if(index < ComponentNum)return Components[index];return nullptr;}
		int touchDelay;
		static Touch_t para_calibration;
		uint8_t touch(int &x, int &y, uint8_t ifExecute);
		int continueTouchTimes(int dis = 200);//Detects the number of consecutive clicks on the screen (the time between two clicks is less than dis ms), returns a negative number during the click, returns 0 when there is no click, and returns the number of clicks after the click is completed.
		uint8_t hasStopContinueTouch(int dis = 1000);//Stopped continuous clicking
		inline void touchReset(void) {
			touchStep = 0;
			touchDelay = -1;
			focusIndex = -1;
			tempIndex = -1;
		}
		static inline void getTouchPos(int &x, int &y) {
			x = ((x * para_calibration.x) >> 16) + para_calibration.offset_x;
    		y = ((y * para_calibration.y) >> 16) + para_calibration.offset_y;
		}
		
	private:
		volatile uint8_t touchStep;
		int tempIndex;
		int focusIndex;
		WRECT winRect;
		yWidget** Components;
		volatile const int ComponentNum;
		inline void componentOffsetCount(int x,int y)
		{
			for(int i = 0;i<ComponentNum;i++)Components[i]->setRectOffset(x,y);
		}
		inline uint8_t getWinVisible()
		{
			if(yWidget::VisualRect.xStart < winRect.xStart)yWidget::VisualRect.xStart = winRect.xStart;
			if(yWidget::VisualRect.xEnd > winRect.xEnd)yWidget::VisualRect.xEnd=winRect.xEnd;
			if(yWidget::VisualRect.yStart < winRect.yStart)yWidget::VisualRect.yStart = winRect.yStart;
			if(yWidget::VisualRect.yEnd > winRect.yEnd)yWidget::VisualRect.yEnd = winRect.yEnd;
			return !(yWidget::VisualRect.xStart > yWidget::VisualRect.xEnd ||
				yWidget::VisualRect.yStart > yWidget::VisualRect.yEnd);
		}
};

