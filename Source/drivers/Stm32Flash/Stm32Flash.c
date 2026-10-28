#include "Stm32Flash.h"


void stm32_flash_disp(unsigned long ulStartAddr,unsigned long ulEndAddr)
{
	char tip[32] = {0};
	uint32_t temp = 0;
	uint32_t Address = 0x00;
	uint8_t dat[4] = {0};
	//uint32_t ulStartAddr = BANK1_WRITE_START_ADDR;
	//uint32_t ulEndAddr = BANK1_WRITE_END_ADDR;

	/* Check the correctness of written data */
	Address = ulStartAddr;

	while((Address < ulEndAddr))
	{
		temp = (*(__IO uint32_t*) Address);
		dat[0] = temp;
		dat[1] = temp >> 8;
		dat[2] = temp >> 16;
		dat[3] = temp >> 24;

		if ((Address % FLASH_PAGE_SIZE) == 0)
		{
			memset(tip,0,sizeof(tip));
			snprintf(tip,sizeof(tip),"%08X~%08X:\r\n",Address,Address + FLASH_PAGE_SIZE);
			DBG_Print(0,"%s",tip);
		}
		DBG_PrintBuf(0,0,dat,4);
		Address += 4;
	}
}


void Stm32FlashReadTest(void)
{
	char tip[32] = {0};
	uint32_t temp = 0;
	uint32_t Address = 0x00;
	uint8_t dat[4] = {0};
	uint32_t ulStartAddr = BANK1_WRITE_START_ADDR;
	uint32_t ulEndAddr = BANK1_WRITE_END_ADDR;

	/* Check the correctness of written data */
	Address = ulStartAddr;

	while((Address < ulEndAddr))
	{
		temp = (*(__IO uint32_t*) Address);
		dat[0] = temp;
		dat[1] = temp >> 8;
		dat[2] = temp >> 16;
		dat[3] = temp >> 24;

		if ((Address % FLASH_PAGE_SIZE) == 0)
		{
			memset(tip,0,sizeof(tip));
			snprintf(tip,sizeof(tip),"%08X~%08X:\r\n",Address,Address + FLASH_PAGE_SIZE);
			DBG_Print(0,"%s",tip);
		}
		DBG_PrintBuf(0,0,dat,4);
		Address += 4;
	}
}

void Stm32FlashWriteTest(void)
{
	uint32_t EraseCounter = 0x00;
	uint32_t Address = 0x00;
	uint32_t Data = 0x1234ABCD;
	uint32_t NbrOfPage = 0x00;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	DBG_Print(0,"Stm32 Flash Write Test Start...\r\n");
	/* Porgram FLASH Bank1 ********************************************************/	   
	  /* Unlock the Flash Bank1 Program Erase controller */
	  FLASH_UnlockBank1();
	
	  /* Define the number of page to be erased */
	  NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
	
	  /* Clear All pending flags */
	  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	
	  /* Erase the FLASH pages */
	  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	  {
		FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
	  }
	  
	  /* Program Flash Bank1 */
	  Address = BANK1_WRITE_START_ADDR;
	
	  while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
	  {
		FLASHStatus = FLASH_ProgramWord(Address, Data);
		Address = Address + 4;
	  }

	  FLASH_LockBank1();
	  DBG_Print(0,"Stm32 Flash Write Test Finish.\r\n");
}

void stm32_flash_write(unsigned long addr,void *buf,unsigned int len)
{
	unsigned char *ptr = (unsigned char *)buf;
	unsigned short temp = 0;

	if ((buf == 0) || (len == 0)) return ;
	FLASH_UnlockBank1();

	while (len >= 2)
	{
		temp = *(unsigned short *)ptr;
		FLASH_ProgramHalfWord(addr, temp);
		len -= 2;
		addr += 2;
		ptr += 2;
	}
	if (len == 1)
	{
		temp = (unsigned short)(ptr[0]) | 0xFF00;
		FLASH_ProgramHalfWord(addr, temp);
	}
	FLASH_LockBank1();
}

void stm32_flash_read1(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize)
{
	unsigned long temp = 0;
	unsigned int rb = 0;
	unsigned char *ptr = (unsigned char *)buf;

	if (wantToReadBytes > bufsize)
	{
		wantToReadBytes = bufsize;
	}
	
	while (1)
	{
		temp = *(unsigned long *)addr;
		addr += 4;
		if (rb < wantToReadBytes)
		{
			if ((wantToReadBytes - rb) >= 4)
			{
				memcpy(ptr+rb,&temp,4);
			}
			else
			{
				memcpy(ptr+rb,&temp,wantToReadBytes - rb);
			}
			rb += 4;
		}
		else
		{
			break;
		}
	}
}



void stm32_flash_erase_sector(unsigned long sector_id)
{
	/* Porgram FLASH Bank1 ********************************************************/	   
	  /* Unlock the Flash Bank1 Program Erase controller */
	  FLASH_UnlockBank1();
	  /* Clear All pending flags */
	  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	  FLASH_ErasePage(sector_id * FLASH_PAGE_SIZE);

	  FLASH_LockBank1();

	return ;
}


int Stm32FlashWritePage(uint32_t StartAddress,void *pdat)
{
	uint32_t EraseCounter = 0x00, Address = 0x00;
	uint32_t Data = 0;
	uint32_t NbrOfPage = 0x00;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	uint8_t *ptr = (uint8_t *)pdat;

	if (pdat == 0) return -1;
	/* Porgram FLASH Bank1 ********************************************************/	   
	  /* Unlock the Flash Bank1 Program Erase controller */
	  FLASH_UnlockBank1();
	
	  /* Define the number of page to be erased */
	  NbrOfPage = 1;
	
	  /* Clear All pending flags */
	  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 

	  /* Erase the FLASH pages */
	  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	  {
		FLASHStatus = FLASH_ErasePage(StartAddress);
	  }

	  /* Program Flash Bank1 */
	  Address = StartAddress;
	
	  while((Address < (StartAddress + FLASH_PAGE_SIZE)) && (FLASHStatus == FLASH_COMPLETE))
	  {
		Data = *((uint32_t *)ptr);
		FLASHStatus = FLASH_ProgramWord(Address, Data);
		Address = Address + 4;
		ptr += 4;
	  }

	  FLASH_LockBank1();

	return 0;
}

static uint32_t s_WriteCnt = 0;
static uint32_t s_IapStartAddress = 0;
static uint32_t s_IapEndAddress = 0;


int IAP_ProgramInit(unsigned int StartAddress,unsigned int EndAddress)
{
	s_IapStartAddress = StartAddress;
	s_IapEndAddress = EndAddress;
	s_WriteCnt = 0;
	return 0;
}

int IAP_ProgramWrite(void *pdat,unsigned int ulDatLen)
{
	if (ulDatLen < FLASH_PAGE_SIZE) return -1;
	if (s_IapEndAddress && 
		((s_IapStartAddress + s_WriteCnt * FLASH_PAGE_SIZE) >= s_IapEndAddress))
	{
		return -2;
	}

	Stm32FlashWritePage(s_IapStartAddress + s_WriteCnt * FLASH_PAGE_SIZE,pdat);
	s_WriteCnt++;
	return s_WriteCnt;
}

