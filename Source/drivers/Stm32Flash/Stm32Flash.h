#ifndef __STM32FLASH_H__
#define __STM32FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "Drivers.h"


#define FLASH_PAGE_SIZE    ((uint16_t)0x800)


#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08000000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08003000)



extern void Stm32FlashWriteTest(void);

extern void Stm32FlashReadTest(void);

extern void stm32_flash_disp(unsigned long ulStartAddr,unsigned long ulEndAddr);


extern int IAP_ProgramInit(unsigned int StartAddress,unsigned int EndAddress);

extern int IAP_ProgramWrite(void *pdat,unsigned int ulDatLen);


extern int Stm32FlashWritePage(uint32_t StartAddress,void *pdat);


extern void stm32_flash_write(unsigned long addr,void *buf,unsigned int len);
extern void stm32_flash_read1(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize);
extern void stm32_flash_erase_sector(unsigned long sector_id);

#ifdef __cplusplus
}
#endif

#endif




