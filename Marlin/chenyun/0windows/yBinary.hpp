
#pragma once

#include "yScale.hpp"

class yBinary : virtual public yWidget
{
	public:
		yBinary(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yBinary(){}

	protected:
		uint8_t binOpaque;
		color_t binFrStart,binFrEnd,binBg;
		int binX,binY;
		const PicAttr *binAttr;
		void showED8b( //Display the external two-bit image and return the end point position of x
			int xStart,int yStart,int xEnd,int yEnd,//Visual range (the intersection of glyph range and VisualRect)
			uint32_t eAddr, //Binary color code external FLASH address
			int distance = 1);//Next bigram spacing
		void getPureED8bScale(int& xStart,int& xEnd,uint32_t eAddr);//The eaddr here is not necessarily binAttr->value. When displaying characters, it should be the character font address.
		void showID8b(//Display the memory two-bit map and return the end point position of x
			int xStart,int yStart,int xEnd,int yEnd,//Visual range (the intersection of glyph range and VisualRect)
			const uint8_t *idat,//Binary color internal FLASH address
			int distance = 1);//Next bigram spacing
		void getPureID8bScale(int& xStart,int& xEnd,const uint8_t* idat);
		void horizonIBinary();//Display horizontal class bivariate diagram
		void verticalIBinary();//Display vertical class binary diagram
};

class ySimulation : virtual public yBinary
{
	public:
		ySimulation(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~ySimulation(){}
		inline virtual uint8_t update(uint8_t force = 0)
		{
			if(yWidget::update(force))return 1;
			if(!focus || focusAllUpdate)updateSimulation(force);//Separation is for flexible calling by successors
			return 0;
		}
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.simulation = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			if(tf && !focus) {
				if(focusAllUpdate) {
					simAttr = simAttrFocus;
					sign.content.simulation = 1;
				}
			}
			else if(!tf && focus) {
				simAttr = simAttrIdle;
				sign.content.simulation = 1;
			}
			yWidget::setfocus(tf);
		}
		inline void setSimulation(const PicAttr* idle,const PicAttr* focus) {
			simAttr = simAttrIdle = idle;
			simAttrFocus = focus;
			sign.content.simulation = 1;
		}
		inline void setSimulationOffset(int x,int y) { simOffsetX = x; simOffsetY = y;}
		inline void setSimulationFrColor(color_t idle_start,color_t idle_end,color_t focus_start = 0,color_t focus_end = 0) {
			simIdleFrStart = idle_start;
			simIdleFrEnd = idle_end;
			simFocusFrStart = focus_start;
			simFocusFrEnd = focus_end;
		}
		inline void setSimulationBgColor(color_t idle,color_t focus = 0) {
			simIdleBg = idle;
			simFocusBg = focus;
		}
		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || (simAttr && sign.content.simulation == 0);}
		uint8_t simOpaque;
	protected:
		void updateSimulation(uint8_t force);
		color_t simIdleFrStart,simIdleFrEnd,simFocusFrStart,simFocusFrEnd;
		color_t simIdleBg,simFocusBg;
		const PicAttr *simAttr,*simAttrIdle,*simAttrFocus;
		int simOffsetX,simOffsetY;
};

