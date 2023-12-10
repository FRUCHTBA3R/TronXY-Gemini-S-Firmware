#pragma once

#include "yBinary.hpp"

extern const PicAttr Font_En8x16Camb;
class yWords : virtual public yBinary
{
	public:
		yWords(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yWords();
		void setWBuffer(uint16_t size,const char*content);
		void setWBuffer(uint16_t size,const uint16_t*content = nullptr);
		void setWBuffer(uint16_t size,uint16_t c,bool full = true);
		void setChars(const char* src);
		void addChars(const char* src);
		void setChars(const uint16_t *src);
		void addChars(const uint16_t *src);
		void addChar(uint16_t t);
		inline void setWordsYScale(int ystart,int yend) {lbYStart = ystart;lbYEnd = yend;}
		inline void setWordsColor(color_t fr_idle,color_t bg_idle,color_t fr_focus = 0,color_t bg_focus = 0) {
			wordsFrIdle = fr_idle;
			wordsBgIdle = bg_idle;
			wordsFrFocus = fr_focus;
			wordsBgFocus = bg_focus;
		}
		uint8_t wordsOpaque;
		uint8_t _fillMargin;
		uint8_t wxCenter; //Text X automatically centered
		uint8_t textDistance;//Must be before functions such as addChars, because they will use this value
		uint8_t representChar;//If a non-zero value is assigned here, when displaying characters, only this variable will be displayed, and the real characters will not be displayed. It is often used for password display.
		static uint16_t uw_start_addr;//Show international language start address
		//0 if all are displayed
		//If only a certain language is displayed, the starting address is the position of the first character of the language in unicode
		//For example, if only Chinese is displayed, it is 0x4E00, and the Chinese range is 0x4E00~0x9FBB.
		int wordOffsetX,wordOffsetY;//The reason why it cannot be directly changed to wordX is that when the window moves and calls setRectOffset, the positions of all controls will change.
		int verticalDistance;//vertical spacing
		const PicAttr *wEnPic,*wCnPic;
		uint16_t *words;

	protected:
		color_t wordsFrIdle,wordsFrFocus,wordsBgIdle,wordsBgFocus;
		uint16_t wordsLen;
		int lbYStart,lbYEnd;//Y range
		uint8_t putc(uint16_t c);
		void fillMargin();
		void updateWords(uint8_t force);
		void showWords(uint8_t force) { updateWords(force);sign.content.text = 0;}
		inline void pureSetFocus(uint8_t tf) {
			if(tf && !focus) {
				if(focusAllUpdate)sign.content.text = 1;
			}
			else if(!tf && focus) {
				sign.content.text = 1;
			}
		}
		inline virtual uint8_t enUpdate(void) {return sign.content.text == 0 && words;}
		int wordsXScale(const uint16_t* tar);
		int oneWordXSize(uint16_t c);
};

class yLabel : virtual public yWords
{
	public:
		yLabel(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
		virtual ~yLabel(){}
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
			yWords::pureSetFocus(tf);
			yWidget::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || yWords::enUpdate();}
};
