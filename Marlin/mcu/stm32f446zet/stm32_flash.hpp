#pragma once

#ifdef STM32F4xx
enum{ 
  FLASH_OK = 0,
  FLASH_BUSY = 1,
  FLASH_TIMEOUT = 2
};

//The FLASH sector size of STM32F4 is not fixed. Starting from 0x08000000, there are 4 16K, 1 64K, and 7 128K. If it is 2M FLASH, the next 1M is in the same order as the first 1M.
#define ADDR_FLASH_SECTOR_0     0x08000000//Sector 0 starting address, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     0x08004000//Sector 1 starting address, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     0x08008000//Sector 2 starting address, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     0x0800C000//Sector 3 starting address, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     0x08010000//Sector 4 starting address, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     0x08020000//Sector 5 starting address, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     0x08040000//Sector 6 starting address, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     0x08060000//Sector 7 starting address, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     0x08080000//Sector 8 starting address, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     0x080A0000//Sector 9 starting address, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    0x080C0000//Sector 10 starting address,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    0x080E0000//Sector 11 starting address,128 Kbytes
#define ADDR_FLASH_SECTOR_12    0x08100000//Sector 12 starting address,16 Kbytes

class IFlash
{
public:
	static inline uint32_t sectorNumOfAddr(uint32_t addr) //Get the sector number where the current address is located
	{
		if(addr < ADDR_FLASH_SECTOR_1)return 0;
		else if(addr < ADDR_FLASH_SECTOR_2)return 1;
		else if(addr < ADDR_FLASH_SECTOR_3)return 2;
		else if(addr < ADDR_FLASH_SECTOR_4)return 3;
		else if(addr < ADDR_FLASH_SECTOR_5)return 4;
		else if(addr < ADDR_FLASH_SECTOR_6)return 5;
		else if(addr < ADDR_FLASH_SECTOR_7)return 6;
		else if(addr < ADDR_FLASH_SECTOR_8)return 7;
		else if(addr < ADDR_FLASH_SECTOR_9)return 8;
		else if(addr < ADDR_FLASH_SECTOR_10)return 9;
		else if(addr < ADDR_FLASH_SECTOR_11)return 10;
		return 11;	
	}
	static inline uint32_t currentSectorAddr(uint32_t addr){ //The starting address of the sector where the target address is located
		if(addr < ADDR_FLASH_SECTOR_1)return FLASH_BASE;
		else if(addr < ADDR_FLASH_SECTOR_2)return ADDR_FLASH_SECTOR_1;
		else if(addr < ADDR_FLASH_SECTOR_3)return ADDR_FLASH_SECTOR_2;
		else if(addr < ADDR_FLASH_SECTOR_4)return ADDR_FLASH_SECTOR_3;
		else if(addr < ADDR_FLASH_SECTOR_5)return ADDR_FLASH_SECTOR_4;
		else if(addr < ADDR_FLASH_SECTOR_6)return ADDR_FLASH_SECTOR_5;
		else if(addr < ADDR_FLASH_SECTOR_7)return ADDR_FLASH_SECTOR_6;
		else if(addr < ADDR_FLASH_SECTOR_8)return ADDR_FLASH_SECTOR_7;
		else if(addr < ADDR_FLASH_SECTOR_9)return ADDR_FLASH_SECTOR_8;
		else if(addr < ADDR_FLASH_SECTOR_10)return ADDR_FLASH_SECTOR_9;
		else if(addr < ADDR_FLASH_SECTOR_11)return ADDR_FLASH_SECTOR_10;
		return ADDR_FLASH_SECTOR_11;	
	}
	static inline uint32_t nextSectorAddr(uint32_t addr){ //Next sector address of target address
		if(addr < ADDR_FLASH_SECTOR_1)return ADDR_FLASH_SECTOR_1;
		else if(addr < ADDR_FLASH_SECTOR_2)return ADDR_FLASH_SECTOR_2;
		else if(addr < ADDR_FLASH_SECTOR_3)return ADDR_FLASH_SECTOR_3;
		else if(addr < ADDR_FLASH_SECTOR_4)return ADDR_FLASH_SECTOR_4;
		else if(addr < ADDR_FLASH_SECTOR_5)return ADDR_FLASH_SECTOR_5;
		else if(addr < ADDR_FLASH_SECTOR_6)return ADDR_FLASH_SECTOR_6;
		else if(addr < ADDR_FLASH_SECTOR_7)return ADDR_FLASH_SECTOR_7;
		else if(addr < ADDR_FLASH_SECTOR_8)return ADDR_FLASH_SECTOR_8;
		else if(addr < ADDR_FLASH_SECTOR_9)return ADDR_FLASH_SECTOR_9;
		else if(addr < ADDR_FLASH_SECTOR_10)return ADDR_FLASH_SECTOR_10;
		else if(addr < ADDR_FLASH_SECTOR_11)return ADDR_FLASH_SECTOR_11;
		return ADDR_FLASH_SECTOR_12;
	}

	/*******************************************************************************
	* Function name    	:vwrite
	* describe      	:To write data of specified length to the specified address in FLASH, the page must be erased first to make it 0xFF.
	* parameter      	:addr The address to be written
						:data is the FLASH data address to be written.
						:The size of the data written by byteSize, in bytes, must be less than the remaining space behind the addr address of the page where addr is located.
	* return      		:-
	* Writer    		：YSZ
	* date of writing  	：2019-12-28
	*******************************************************************************/
	static uint8_t vwrite(uint32_t addr,const void* data,uint32_t byteSize);

	/*******************************************************************************
	* Function name    	:eraseSector
	* describe      	:Check whether the remaining amount of this sector after this address needs to be erased. If necessary, this sector will be completely erased.
	* parameter      	:addr target address
	* return      		:-
	* Writer    		：YSZ
	* date of writing  	：2021-03-02
	*******************************************************************************/
	static uint8_t eraseSector(uint32_t addr);

	/*******************************************************************************
	* Function name    	:read
	* describe      	:Read the data of the specified address and specified length in FLASH
	* parameter      	:addr The address to be read
						:The memory address where the data read by data is stored.
						:size read size
	* return      		:-
	* Writer    		：YSZ
	* date of writing  	：2019-12-28
	*******************************************************************************/
	static void read(uint32_t addr,void* data,uint32_t byteSize);

	/*******************************************************************************
	* Function name    	:swrite
	* describe      	:Writing data of a specified length to a specified address in FLASH will erase the data in the associated sector.
	* parameter      	:addr write address
	            		:nextEraseAddr The address to be erased
						:data is the FLASH data address to be written.
						:byteSize is the size of the data written, in bytes.
	* return      		:-
	* Writer    		：YSZ
	* date of writing  	：2019-12-28
	*******************************************************************************/
	static uint8_t swrite(uint32_t& addr,uint32_t& nextEraseAddr,const void* data,uint32_t byteSize);
};
#endif
