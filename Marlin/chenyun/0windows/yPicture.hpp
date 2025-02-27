
#pragma once

#include "yScale.hpp"
enum PIC_MODE {
PIC_INTERNAL,
PIC_EXTERNAL,
PIC_LINE_COMPRESS,
PIC_TOTAL_COMPRESS
};
class yPicture : virtual public yWidget
{
	public:
		yPicture(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
		{
			picAttrIdle = nullptr;
			picAttrFocus = nullptr;
			picAttr = nullptr;
			picOffsetX = 0;
			picOffsetY = 0;
			ifBlackTransparent = 0;
			sign.content.picture = 1;
			picMode = PIC_LINE_COMPRESS;
		}
		virtual ~yPicture(){}
		inline virtual uint8_t update(uint8_t force = 0)
		{
			if(yWidget::update(force))return 1;
			if(!focus || focusAllUpdate)updatePicture(force);//Written separately is for flexible calling by successors.
			return 0;
		}
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.picture = 0;
		}
		inline void setPicture(const PicAttr* idle,const PicAttr* focus) {
			picAttr = picAttrIdle = idle;
			picAttrFocus = focus;
			sign.content.picture = 1;
		}
		inline void setPictureOffset(int x,int y) { picOffsetX = x; picOffsetY = y;}
		inline virtual void setfocus(uint8_t tf) {
			if(tf && !focus) {
				if(focusAllUpdate) {
					picAttr = picAttrFocus;
					sign.content.picture = 1;
				}
			}
			else if(!tf && focus) {
				picAttr = picAttrIdle;
				sign.content.picture = 1;
			}
			yWidget::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || (picAttr && sign.content.picture == 0);}
		PIC_MODE picMode;

	protected:
		uint8_t ifBlackTransparent;
		int picOffsetX,picOffsetY;
		const PicAttr *picAttr,*picAttrIdle,*picAttrFocus;
		void updatePicture(uint8_t force);
		void showEBytes(int x,int y);//Display byte image from external ROM - image data is saved in byte form
		void showLineCompress(int x,int y);//Display compressed graphics in external ROM, line
		void showTotalCompress(int x,int y);//Display compressed graphics in external ROM, whole (<=32x32)
		void showIBytes(int x,int y);//Display byte image in IFLASH - image data is saved in byte form
};
