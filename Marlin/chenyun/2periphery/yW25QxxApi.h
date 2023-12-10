#pragma once

#include "../yCommon.h"
//-->The hardware platform is required to provide the following definitions or interfaces
extern void (*w25qMcuInit)(void);//FLASH initialization on MCU
extern void (*w25qCs_Low)(void);//Chip Select
extern void (*w25qCs_High)(void);//No film selection
extern uint8_t (*w25qSpiSendRcv)(const uint8_t *sendDt, bool sendInc,uint8_t *rcvDt,bool rcvInc,int len);
extern void (*w25qBatch)(const uint8_t* sendBuf, uint8_t* rcvBuf, uint32_t nbyte);//Read and write EFlash data in batches
extern uint8_t (*w25qBatchOk)(void);//Completed in batches
extern void (*w25qBatchStop)(uint32_t period);//Abort batch reading and writing

/*******************************************************************************
-->This driver provides the following interfaces
1.EFLASH_Init                      EFlash initialization, returns chip ID
2.EFLAH_Read(addr,buff,len)        Read data of length len bytes from address addr and store it at buff
3.EFlashErase(addr)                Erase a sector from addr, addr must be an integer multiple of the sector size EFLASH_SECTORSIZE
4.EFLAH_Write(addr,buff,len,exchangeBuff) Store data of length len bytes from buff at addr
5.EFLash_SWrite(addr,buff,len)     Quickly write data to FLASH without retaining other data in the sector
And the address must be the first address of the sector, that is, the address is an integer multiple of EFLASH_SECTORSIZE
Common to EN25Qxx and W25Qxx
*******************************************************************************/
//IDEN25Q80 ID 0x1C13,
//IDEN25Q16 ID 0x1C14,
//IDEN25Q32 ID 0x1C15,
//IDEN25Q64 ID 0xC816
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q64 ID  0XEF16
//W25Q128 ID  0XEF17
#define EFLASH_ID                 0xC816
#define EFLASH_SECTORCOUNT        0x800 //Total number of sectors, 64Mbit=8MB=0x800000Byte=0x1000*0x800, that is, number of sectors=0x800
#define EFLASH_SECTORSIZE         0x1000 //Sector size: 4K bytes, when erasing, it is erased in units of sectors
#define EFLASH_BLOCKSIZE          1 //How many sectors are there in each block?
#define W25Q_PAGESIZE             0x100 //Page size, 25Q64 is written in page units

uint32_t W25QxxInit(void);
void W25QxxBatchRead(uint32_t addr,void* buff,int len, uint32_t lastreadWait = 200);
uint8_t W25QxxBatchReadOk(void);
void W25QxxBatchStop(uint32_t period = 200);

//Write data at the specified address and retain other data in the sector area where the address is located.
uint8_t W25QxxWrite(uint32_t addr,const void* buff,int len,void *exchangeBuff);

//Write data at the specified address and do not retain other data in the sector area where the address is located.
//When nextEraseAddr is set to 1, let the function automatically obtain the current erase address corresponding to addr.
uint8_t W25QxxSWrite(uint32_t& addr,uint32_t& nextEraseAddr,const void* data,int len);
uint8_t W25QxxVWrite(uint32_t addr,const void* data,int len);//Write data directly and need to erase in advance
uint8_t W25QxxEraseSector(uint32_t sectorAddr);//Note that erasing can only be done in units of SECTOR

