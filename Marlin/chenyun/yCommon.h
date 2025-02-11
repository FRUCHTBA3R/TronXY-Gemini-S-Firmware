#pragma once

#include <inttypes.h>
#include "yType.hpp"
#ifdef STM32F4xx
#include "stm32f446zet/stm32.hpp"
#else
#include "stm32f103zet/stm32.hpp"
#endif
#if LCD_CHIP_INDEX == 1
#include "3lcd_driver/ILI94xx.h"
#elif LCD_CHIP_INDEX == 2
#include "3lcd_driver/SSD19xx.h"
#elif LCD_CHIP_INDEX == 3
#include "3lcd_driver/NT35510.h"
#elif LCD_CHIP_INDEX == 4
#include "3lcd_driver/ST7789.h"
#else
#error You must define a lcd.
#endif

/*-->the driver needs to provide:
LCD_WArea(int xStart,int yStart,int xEnd,int yEnd);//1.Screen area writing frame
LCD_RArea(int xStart,int yStart,int xEnd,int yEnd);//2.screen area reading frame
LCD_BatchStart(const color_t* colors,int num,uint8_t autoInc);//4.Write colors in batches. This interface can be executed after executing 1 and 2.
LCD_Busy();//5.Batch write completion judgment
LCD_BatchSyn(const uint16_t*colors,int len,uint8_t autoInc);//6.Write in batches and wait for completion
LCD_WPixel(int x,int y,color_t color);//7.Write the color at the coordinates x and y
LCD_RPixel(int x,int y,color_t& R,color_t& G,color_t& B);//8.Read the color at coordinates x, y and save it into r, g, b components
LCD_Read_RGB_Start(int xStart,int yStart,int xEnd,int yEnd);//9.Batch reading of colors starts
LCD_Read_RGB(color_t& R,color_t& G,color_t& B);//10.Read out one RGB at a time, then use the above method to read RGB in batches
*/
extern color_t *LCD_LBuffer1,*LCD_LBuffer2;//9.The first-level (preparation data) and second-level (display data) cache spaces for one row of pixels on the screen are allocated to two consecutive sections of space, with buffer1 in front
//10.VisualRect needs to be assigned a value to specify the length and width of the screen.
extern uint8_t compress_buff_per_line[];//11.Data space before decompression of a row (maximum value)
extern uint16_t compress_len_per_line[];//12.length of each line
extern uint8_t (*touchChipPos)(int& x,int& y);//13.Get the touch point and return true when touched
extern uint32_t (*nowMs)(void);//14.Current time, unit: milliseconds
extern const PicAttr *defaultUFont;//15.Default unicode font library, assign uw_start_addr, specify the starting position of the language in unicode
extern void (*yWatchdog)(void);//16.In some cases (for example: when displaying a compressed full image), it may take a long time and a watchdog reset function needs to be provided.

extern uint32_t (*EROM_Init)(void); //17.External EROM initialization, note: the EROM here is used to read LCD picture information
extern void (*EROM_ReadStart)(uint32_t addr,void* buff,int len, uint32_t lastreadWait);
extern uint8_t (*EROM_ReadOk)(void);
extern void (*EROM_ReadStop)(uint32_t period);
extern uint8_t (*EROM_SWrite)(uint32_t& addr,uint32_t& nextEraseAddr,const void* data,int len);
extern uint8_t (*EROM_VWrite)(uint32_t addr,const void* data,int len);
extern uint8_t (*EROM_Write)(uint32_t addr,const void* buff,int len,void *exchangeBuff);

#define INFO_STR(x)
