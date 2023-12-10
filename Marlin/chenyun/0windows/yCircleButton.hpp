#pragma once

#include "yFigure.hpp"
#include "yIcon.hpp"
#include "yMultiple.hpp"

class yCircleButton : public yMultiple
{
    public:
        yCircleButton(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
		{
            circleR = (width > height ? height : width) / 2;
            circleDis = 1;
            circleX = wXStart + width / 2;
            circleY = wYStart + height / 2;
        }
        virtual ~yCircleButton(){}
        virtual uint8_t update(uint8_t force);
        inline virtual void show(uint8_t force = 0) {
            update(force);
            sign.content.scale = 0;
            sign.content.simulation = 0;
            sign.content.text = 0;
        }
        int circleX,circleY; //Circle center coordinates
        int circleR;//circle radius
        int circleDis;//Circumferential thickness
    private:
		void midCircle(color_t color,int r,int x,int y,int dis = 1);//Draw a circle: center x, y, radius r, edge thickness dis
		void pollCircle(color_t color_start,color_t color_end,int r,int dis,int xStart,int yStart,int xEnd,int yEnd);//Draw a circle: radius r, thickness dis
};

class yRoundedBase : virtual public yWidget
{
    public:
        yRoundedBase(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
        {
            rounded_r = 2;
        }
        virtual ~yRoundedBase(){}
        inline void setRoundedRadius(int rs = 1) {rounded_r = rs;}
        virtual uint8_t update(uint8_t force = 0);
    protected:
        void updateRounded(color_t color_start,color_t color_end);
        int rounded_r;
};

class yRoundedSimulation : virtual public yFigure,virtual public yRoundedBase //Rounded rectangle button
{
    public:
        yRoundedSimulation(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
        virtual ~yRoundedSimulation(){}
        virtual uint8_t update(uint8_t force);//Level: rounded corners -> text (or multiple images)
};

class yRoundedPicture : virtual public yIcon, virtual public yRoundedBase
{
    public:
        yRoundedPicture(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
        virtual ~yRoundedPicture(){}
        virtual uint8_t update(uint8_t force);//Level: rounded corners->image->text
};
