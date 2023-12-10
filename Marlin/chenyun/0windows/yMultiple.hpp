#pragma once

#include "yLabel.hpp"

class yMultiple : public ySimulation, public yWords //Analog icons, multi-image categories
{
	public:
		yMultiple(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yMultiple(){}
		void setMulti(const PicAttr* pics,int num = 1);
		inline virtual uint8_t update(uint8_t force) {//Level: Background->Simulation Icon->Multiple Pictures (or Text)
			if(ySimulation::update(force))return 1;
			if(!focus || focusAllUpdate)updateMulti(force);//The purpose of writing separately is to allow the successor to call updateMulti
			return 0;
		}
		inline virtual void show(uint8_t force) {
			update(force);
			sign.content.scale = 0;
			sign.content.simulation = 0;
			sign.content.text = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			yWords::pureSetFocus(tf);
			ySimulation::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return ySimulation::enUpdate() || (mulPic && sign.content.text == 0);}
	protected:
		const PicAttr* mulPic;
		int mulNum;
		void updateMulti(uint8_t force);
		int multiXScale(const PicAttr* tarp,int num);//Get num multi x lengths (if a newline is encountered early, stop here)
};
