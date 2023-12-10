#pragma once

#include "yLabel.hpp"

class yVariant : virtual public yWords
{
	public:
		yVariant(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr) {
			fixedEdge = 1;
		}
		virtual ~yVariant(){}
		virtual uint8_t update(uint8_t force = 0) {
			if(yWidget::update(force))return 1;
			if(!focus || focusAllUpdate)updateWords(force);
			return 0;
		}
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.text = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			yWidget::setfocus(tf);
			yWords::pureSetFocus(tf);
		}

		uint8_t fixedEdge;//1-When colorVertical is true, the upper side, otherwise the left side is fixed; 0-when colorVertical is true, the lower side, otherwise the right side is fixed;
		void changeBorder(int v);//fixedEdge determines the fixed edge, what changes here is the corresponding variable edge
};
