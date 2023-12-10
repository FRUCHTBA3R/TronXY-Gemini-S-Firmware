#pragma once
#if LCD_CHIP_INDEX == 1

#if TRONXY_UI == UI_SIM320X480
#define WIN_LMAX                                  320 //The window length must be greater than or equal to the LCD length. Large windows can be used on small LCDs. The picture size must be <= window size.
#define WIN_WMAX                                  480 //The window width must be greater than or equal to the LCD width. Large windows can be used on small LCDs.
#define	LCD_LMAX                                  WIN_LMAX
#define	LCD_WMAX                                  WIN_WMAX
#else
#define WIN_LMAX                                  480 //The window length must be greater than or equal to the LCD length. Large windows can be used on small LCDs. The picture size must be <= window size.
#define WIN_WMAX                                  320 //The window width must be greater than or equal to the LCD width. Large windows can be used on small LCDs.
#define	LCD_LMAX                                  WIN_LMAX
#define	LCD_WMAX                                  WIN_WMAX
#endif
#define	LCDDIR_INVERT_RB                          0x08	//Red and blue exchange
#define	LCDDIR_HVCHANGE                           0x20	//When the fifth bit is 1, it is horizontal screen
#define	LCDDIR_REVERSE_W                          0x40	//Bit 6 determines the width direction
#define	LCDDIR_REVERSE_L                          0x80	//Bit 7 determines the long direction

void LCD_Init(unsigned char dir = LCDDIR_HVCHANGE | LCDDIR_INVERT_RB | LCDDIR_REVERSE_W | LCDDIR_REVERSE_L);
void LCD_Driver_Init(unsigned char dir = LCDDIR_HVCHANGE | LCDDIR_INVERT_RB | LCDDIR_REVERSE_W | LCDDIR_REVERSE_L);
void LCD_SetDir(unsigned char dir);

//Different chips may have different RGB combinations
#define LCD_Area(xStart,yStart,xEnd,yEnd) \
	LCD_WReg(0x2A);/*x*/\
	LCD_WData((xStart) >> 8);\
	LCD_WData((xStart) & 0xFF);\
	LCD_WData((xEnd) >> 8);\
	LCD_WData((xEnd) & 0xFF);\
	LCD_WReg(0x2B);/*y*/\
	LCD_WData((yStart) >> 8);\
	LCD_WData((yStart) & 0xFF);\
	LCD_WData((yEnd) >> 8);\
	LCD_WData((yEnd) & 0xFF)

inline void LCD_WArea(int xStart,int yStart,int xEnd,int yEnd) {
	LCD_Area(xStart,yStart,xEnd,yEnd);
	LCD_WReg(0x2C);
}

inline void LCD_WPixel(int x,int y,uint16_t color) {
	LCD_Area(x,y,x,y);
	LCD_WReg(0x2C);
	LCD_WData(color);
}

#define LCD_RPixel(x,y,R,G,B) \
	do{ LCD_Area(x,y,x,y);\
	LCD_WReg(0x2E);\
	LCD_RData(B);/*dummy*/\
	LCD_RData(R);/*RG*/ G = R & 0x00FF; G >>= 2; R >>= 11;\
	LCD_RData(B);/*B*/ B >>= 11;}while(0)

#endif