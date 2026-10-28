#include "update.h"


//指定地址存放版本号 厂商标识等信息
const  char ver_info[]  __attribute__ ((at(SOFTWARE_INFO_ADDR))) = 
"<" MANUFACTURER_FLAG ">" "<" BOOT_VERSION ">" "<" __DATE__ ">" "<" __TIME__ ">"; 



typedef void (*EntryFunc)(void);


unsigned char XOR_Check(INT8U *pdat,INT32U len)
{
	unsigned int i = 0;
	unsigned char temp = pdat[0];

	if (len == 1) return pdat[0];
	
	for (i = 1; i < len; i++)
	{
		temp ^= pdat[i];
	}
	return temp;
}

void stm32_flash_read(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize)
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



//is_intel:是内部还是外部FLASH
int export_bin_file(char is_intel,unsigned int readlen)
{
	unsigned int offset = 0;
	unsigned int slen = 0;
	//static INT8U pbuf[2048] = {0};
	static unsigned char  pbuf[2048] = {0};
	//INT8U aucAck[16] = {0};
	unsigned int ulTotalBytes = readlen * 1024;
	unsigned int addr = 0;
	//INT32U rlen = 0;

	if (readlen == 0) return 1;

	//pbuf = get_big_mem();

	if (is_intel)
	{
		addr = 20 * 1024;
	}
	else
	{
		addr = 0;
	}

	//BINFILE
	memcpy(pbuf,"BINFILE",strlen("BINFILE"));
	offset = strlen("BINFILE");

	while (ulTotalBytes)
	{
		if (ulTotalBytes > 1024)
		{
			slen = 1024;
		}
		else
		{
			slen = ulTotalBytes;
		}

		pbuf[offset + 0] = slen >> 8;
		pbuf[offset + 1] = slen;

		if (is_intel)
		{
			stm32_flash_read(addr,slen,pbuf + offset + 2,1024);
		}
		else
		{
			//spi_flash_read(addr,slen,pbuf + offset + 2,1024);
		}
		
		pbuf[offset + 2 + slen] = XOR_Check(pbuf,slen + offset + 2);
		DBG_SendData(pbuf,offset + 2 + slen + 1);
		//lfos_sleep(400);
		delayms_by_timer(400);

		addr += slen;
		ulTotalBytes -= slen;

#if 0
		//死等上位机应答
		while ((rlen = ReadUsart1(aucAck,2,1000)) == 0)
		{
			lfos_sleep(50);
		}
		if (_FindChar(aucAck,rlen,ACK))		//应答才发第二包 否则继续发送该包
		{
			addr += slen;
			ulTotalBytes -= slen;
			//while (ReadDBGUsart(0,aucAck,2,10)) lfos_sleep(10);	//把接收区里面的数据清空
		}
#endif
	}
	//free_big_mem(pbuf);

	DBG_Print(LEVEL0,"%s","Import OK.\r\n");
	return 0;
}


//跳转到驱动层
void JumpToApp(void)
{
	uint32_t JumpAddress = 0;
	uint32_t SpAddress = 0;
	EntryFunc func;

	//先关中断
	cpu_int_dis();
	//export_bin_file(1,94);

	JumpAddress = *(__IO uint32_t*) (DRIVER_START_ADDR + 4);
	SpAddress = *(__IO uint32_t*)DRIVER_START_ADDR;

	DBG_Print(LEVEL0,"\r\nJump to Driver(Reset:%08X SP:%08X)...\r\n",JumpAddress,SpAddress);
	delayms(500);	//稍微延时 等待串口打印完毕

	func = (EntryFunc)JumpAddress;

  	SysTick->CTRL  &= ~(SysTick_CTRL_ENABLE_Msk);    
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	//重新设置中断向量表
	SCB->VTOR = DRIVER_START_ADDR;

	__set_MSP(SpAddress);
	func();
}

static const unsigned short crc16tab[256]= {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

unsigned short CheckCRC16(void *pdat,unsigned int len)
{
	unsigned char *buf = (unsigned char *)pdat;
    unsigned int counter = 0;
    unsigned short crc = 0;

    for ( counter = 0; counter < len; counter++)
    {
        crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(unsigned char *)buf++)&0x00FF];
    }
    return crc;
}


void *_FindChar(void *pdat,unsigned int datlen,unsigned char ucObj)
{
	unsigned int i = 0;
	unsigned char *pSrc = (unsigned char *)pdat;

	if (datlen == 0) datlen = strlen((char *)pSrc);
	for (i = 0; i < datlen; i++)
	{
		if (*(pSrc+i) == ucObj) return (pSrc+i);
	}
	return 0;
}

unsigned char xor_check(void *ptr,unsigned int len)
{
	unsigned char *pdat = (unsigned char *)ptr;
	unsigned int i = 0;
	INT8U temp = 0;

	if ((ptr == 0) || (len == 0))
	{
		return 0;
	}
	temp = pdat[0];
	if (len == 1) return pdat[0];
	
	for (i = 1; i < len; i++)
	{
		temp ^= pdat[i];
	}
	return temp;
}

#define	SOH		0x01
#define STX		0x02

#define EOT		0x04
#define ACK		0x06
#define NAK		0x15
#define CAN		0x18


#define  XMODEM_START_FLAG 'C'

#define XMODEM_PACK_SIZE (1 + 2 + 1024 + 2)
#define XMODEM_DATA_LEN  1024

unsigned char pagebuf[FLASH_PAGE_SIZE + 1] = {0};

unsigned char ucStatusFlag = 0;
unsigned char s_last_xmodem_bag_id = 0;



int CheckPackIsOk(void *pHead)
{
	INT16U calccrc = 0;
	INT16U realcrc = 0;
	INT8U *ptr = (INT8U *)pHead;
	INT8U num = 0;

	num = ptr[1];

	realcrc = (ptr[3 + XMODEM_DATA_LEN] << 8) + ptr[3 + XMODEM_DATA_LEN + 1];
	calccrc = CheckCRC16(ptr + 3,XMODEM_DATA_LEN);

	//DBG_Print(0,"<CheckPackIsOk>calc crc:%04X real crc:%04X\r\n",calccrc,realcrc);
	if (realcrc == calccrc)
	{
		if (num != (s_last_xmodem_bag_id+1))
		{
			return 0;
		}
		s_last_xmodem_bag_id = num;	
		return 1;
	}

	return 0;
}



typedef struct tagDate
{
	INT8U year;
	INT8U month;
	INT8U day;
	INT8U hour;
	INT8U min;
	INT8U sec;
}Date;


typedef enum tagUpdateStatus
{
	UPDATE_STATUS_NO = 0x12,			//未升级
	UPDATE_STATUS_START = 0x34,			//启动
	UPDATE_STATUS_FILE_OK = 0x56,		//升级文件校验通过
	UPDATE_STATUS_UPDATE_OK = 0x78,		//升级完成 BOOT检测到UPDATE_STATUS_FILE_OK 这个状态 
										//就会升级APP 然后将状态置为UPDATE_STATUS_UPDATE_OK
	UPDATE_STATUS_UPDATE_FALSE = 0x90,
}UpdateStatus;


typedef struct tagUpdateInfo
{
	UpdateStatus eUpdateStatus;						//升级状态
	INT8U ucUpdateWay;						//升级方式(xmodem FTP TCP等方式)
	INT32U ulStartAddr;						//在FLASH中存放的起始地址
	INT32U ulEndAddr;						//结束地址
	INT32U ulTotalBytes;					//总大小
	INT16U usTotalPackCnt;						//总包数
	Date stStartTime;				//起始时间
	INT32U ulStartTime;				//起始时间
	Date stEndTime;					//结束时间
	INT32U ulEndTime;				//结束时间
	INT32U ulTakeTimes;				//FTP耗时多少
	INT8S szReportPhone[20];				//升级成功汇报短信号码
	INT8S szServerAddr[32];
	INT16U usServerPort;
	INT8S szUpdateFileName[32];
}UpdateInfo;

UpdateInfo stUpdateInfo;
unsigned char is_driver_file_flag = 0;	//判断是否是驱动文件

/**
函数功能：获取pSubStr1和pSubStr2之间的字符串 
入口参数:
		str:源字符串
		pSubStr1:起始子字符串
		pSubStr2:结尾子字符串
		outbuflen:传入的缓冲区大小
出口参数:
		pOutBuf:调用者传入的缓冲区 用于接收pSubStr1与pSubStr2之间的内容
返回值:如果存在则返回pSubStr1的指针 否则返回NULL
调用示例：GetSubString("<ServerIP:192.168.1.19>","<ServerIP:",">",sub);
		执行结果：sub = "192.168.1.19"
 */
char *GetSubString(char *str,char *pSubStr1,char *pSubStr2,char *pOutBuf,unsigned int outbuflen)
{
	char *pTemp1 = 0;
	char *pTemp2 = 0;
	unsigned int templen = 0;

	if ((str == 0) || (pSubStr1 == 0) || (pOutBuf == 0) || (outbuflen == 0))
	{
		return 0;
	}

	pTemp1 = strstr(str,pSubStr1);
	//未找到第一个字符串
	if (pTemp1 == 0) return 0;

	//如果第二个子字符串传入的是0 或者 为空值 那么返回结果就默认为取第一个字符串到结尾之间的数据
	if (pSubStr2 && strlen(pSubStr2))
	{
		pTemp2 = strstr(pTemp1 + strlen((char *)pSubStr1),pSubStr2);
	}
	else
	{
		pTemp2 = str + strlen(str);
	}
	if (pTemp2)
	{
		templen = pTemp2 - (pTemp1 + strlen((char *)pSubStr1));
		templen = (outbuflen >= templen) ? templen : outbuflen;
		memset(pOutBuf,0,outbuflen);
		if (templen) memcpy(pOutBuf,pTemp1 + strlen((char *)pSubStr1),templen);

		return pTemp1;
	}
	return 0;
}

//检验文件版本号是否正确
char is_app_ver_ok(void)
{
	INT32U addr = stUpdateInfo.ulStartAddr;
	char *ptr1 = 0;
	char *ptr2 = 0;

	char sv[64] = {0};		//软件版本
	char manufacturer[16] = {0};	//厂商标识
	char old_drv_sv[64] = {0};		//old driver ver
	char tempbuf[16] = {0};

	//读出升级APP的版本信息
	//spi_flash_read(addr + APP_SOFTWARE_INFO_OFFSET,100,pagebuf,sizeof(pagebuf));
	memcpy(pagebuf,(unsigned char *)(addr + SOFTWARE_INFO_OFFSET),100);
	memcpy(pagebuf + 110,(unsigned char *)(DRIVER_START_ADDR + SOFTWARE_INFO_OFFSET),100);

	pagebuf[100] = 0;
	pagebuf[110 + 100] = 0;

	ptr1 = GetSubString((char *)pagebuf,"<",">",manufacturer,sizeof(manufacturer));
	if (ptr1 == 0)
	{
		return 0;
	}
	//厂商代码
	if (strcmp(manufacturer,MANUFACTURER_FLAG))
	{
		return 0;
	}
	ptr2 = GetSubString(ptr1 + 1,"<",">",sv,sizeof(sv));
	if (ptr2 == 0)
	{
		return 0;
	}

	//LF_DRIVER_FILE_FLAG1 和 软件版本名称同时命中 才认为是驱动文件
	if (memcmp(sv,LF_DRIVER_FILE_FLAG,strlen(LF_DRIVER_FILE_FLAG)) == 0)
	{
		//spi_flash_read(addr + LF_DRIVER_FILE_FLAG1_OFFSET,100,pagebuf,sizeof(pagebuf));
		memcpy(pagebuf,(unsigned char *)(addr + LF_DRIVER_FILE_FLAG1_OFFSET),100);
		
		if ((*(unsigned int *)pagebuf) == LF_DRIVER_FILE_FLAG1)
		{
			is_driver_file_flag = 1;
		}
		else
		{
			is_driver_file_flag = 0;
			DBG_Print(LEVEL0,"the file is not driver file"
			"[driver file flag1 must:%08X this file flag1:%08X]\r\n",
			LF_DRIVER_FILE_FLAG1,(*(unsigned int *)pagebuf));
		}
	}
	else
	{
		is_driver_file_flag = 0;
	}

	if (is_driver_file_flag)
	{
		ptr1 = GetSubString((char *)pagebuf + 110,"<",">",manufacturer,sizeof(manufacturer));
		if (ptr1 == 0)
		{
			return 1;
		}
		//厂商代码
		if (strcmp(manufacturer,MANUFACTURER_FLAG))
		{
			return 1;
		}
		ptr2 = GetSubString(ptr1 + 1,"<",">",old_drv_sv,sizeof(old_drv_sv));
		if (ptr2 == 0)
		{
			return 1;
		}

		//sv  old_drv_sv
		//BYSD_DRIVER_NXP_V1.0.3
		//BYSD_DRIVER_GD32_V1.0.3
		//BYSD_DRIVER_ST32_V1.0.3
		//BYSD_DRIVER_ST32_V2.0.3

		//check cpu type
		GetSubString(sv + strlen("BYSD_DRIVER"),"_","_",manufacturer,sizeof(manufacturer));
		GetSubString(old_drv_sv + strlen("BYSD_DRIVER"),"_","_",tempbuf,sizeof(tempbuf));
		if (strcmp(manufacturer,tempbuf))
		{
			DBG_Print(LEVEL0,"drv cpu type is not match(old:%s new:%s)\r\n",old_drv_sv,sv);
			return 0;
		}

		//check big version
		GetSubString(sv + strlen("BYSD_DRIVER"),"_V",".",manufacturer,sizeof(manufacturer));
		GetSubString(old_drv_sv + strlen("BYSD_DRIVER"),"_V",".",tempbuf,sizeof(tempbuf));
		if (strcmp(manufacturer,tempbuf))
		{
			DBG_Print(LEVEL0,"drv big version is not match(old:%s new:%s)\r\n",old_drv_sv,sv);
			return 0;
		}
	}
	return 1;
}

char is_update_file_ok(void)
{
	unsigned int rlen = 0;
	unsigned int tlen = stUpdateInfo.ulTotalBytes - 4;
	unsigned long addr = 0;
	unsigned char temp[4] = {0};
	unsigned int crc32 = 0;
	unsigned int read_crc32 = 0;

	if (stUpdateInfo.ulTotalBytes <= 4)
	{
		return 0;
	}

	if (is_app_ver_ok() == 0)
	{
		return 0;
	}

	addr = stUpdateInfo.ulStartAddr;

	while (tlen)
	{
		if (tlen > FLASH_PAGE_SIZE)
		{
			rlen = FLASH_PAGE_SIZE;
		}
		else
		{
			rlen = tlen;
		}

		memcpy(pagebuf,(unsigned char *)addr,rlen);

		crc32 = calc_crc32(crc32,pagebuf,rlen);		

		addr += rlen;
		tlen -= rlen;
	}

	memcpy(temp,(unsigned char *)addr,4);
	read_crc32 = (temp[0] << 24) + (temp[1] << 16) + (temp[2] << 8) + temp[3];
	if (crc32 != read_crc32)
	{
		DBG_Print(LEVEL0,"crc32 check err.update false.(calc:%08X read:%08X)\r\n",
							crc32,read_crc32);
		return 0;
	}
	return 1;
}

//返回值0表示失败 1表示成功
char CarryApp(void)
{
	INT32U slen = 0;
	INT32U addr = stUpdateInfo.ulStartAddr;
	INT32U len = stUpdateInfo.ulTotalBytes;

#if 0
	if (!is_spi_flash_ok())
	{
		return 0;
	}
#endif

	enter_update_mode();

	if (is_driver_file_flag)
	{
		IAP_ProgramInit(DRIVER_START_ADDR,APP_END_ADDR);
	}
	else
	{
		IAP_ProgramInit(APP_START_ADDR,APP_END_ADDR);
	}

	DBG_Print(LEVEL0,"carry app to cpu flash.(external flash start addr:%08X filesize:%uKB)\r\n",
	stUpdateInfo.ulStartAddr,(stUpdateInfo.ulTotalBytes + 1023) / 1024);
	
	while (len)
	{
		if (len >= FLASH_PAGE_SIZE)
		{
			slen = FLASH_PAGE_SIZE;
		}
		else
		{
			slen = len;
		}

		//读出来
		//spi_flash_read(addr,slen,pagebuf,FLASH_PAGE_SIZE);
		memcpy(pagebuf,(unsigned char *)addr,slen);
		
		//DBG_Print(LEVEL0,"addr:%08X slen:%d\r\n",addr,slen);
		//DBG_PrintBuf(LEVEL0,0,s_readbuf,slen);
		
		//写进去 整页写入 最后一包可以不用整页
		IAP_ProgramWrite(pagebuf,FLASH_PAGE_SIZE);

		len -= slen;
		addr += slen;
	}
	return 1;
}

void check_remote_update(void)
{
	memcpy(&stUpdateInfo,(unsigned char *)UPDATE_INFO_START_ADDR,sizeof(stUpdateInfo));
	//spi_flash_read(UPDATE_INFO_START_ADDR,sizeof(stUpdateInfo),&stUpdateInfo,sizeof(stUpdateInfo));

	DBG_Print(LEVEL3,"------------------------Update Info------------------------\r\n"
					 "Update Server:%s:%d DownloadFile:%s\r\n"
					 "Store Address In Flash:0x%08X ~ 0x%08X\r\n"
					 "TotalSize:%u TotalPackCnt:%u\r\n"
					 "Time:%02d/%02d/%02d %02d:%02d:%02d ~ %02d/%02d/%02d %02d:%02d:%02d\r\n"
					 "Take Times:%us status:%02X way:%d\r\n"
					 "-----------------------------------------------------------\r\n",
					stUpdateInfo.szServerAddr,stUpdateInfo.usServerPort,stUpdateInfo.szUpdateFileName,
					stUpdateInfo.ulStartAddr,stUpdateInfo.ulEndAddr,
					stUpdateInfo.ulTotalBytes,stUpdateInfo.usTotalPackCnt,
					stUpdateInfo.stStartTime.year,stUpdateInfo.stStartTime.month,
					stUpdateInfo.stStartTime.day,stUpdateInfo.stStartTime.hour,
					stUpdateInfo.stStartTime.min,stUpdateInfo.stStartTime.sec,
	
					stUpdateInfo.stEndTime.year,stUpdateInfo.stEndTime.month,
					stUpdateInfo.stEndTime.day,stUpdateInfo.stEndTime.hour,
					stUpdateInfo.stEndTime.min,stUpdateInfo.stEndTime.sec,
					stUpdateInfo.ulTakeTimes,stUpdateInfo.eUpdateStatus,
					stUpdateInfo.ucUpdateWay
					 );

	//检测到需要升级APP
	if (stUpdateInfo.eUpdateStatus == UPDATE_STATUS_FILE_OK)
	{
		//将程序搬移到APP存储区
		if (is_update_file_ok())
		{
			CarryApp();
			stUpdateInfo.eUpdateStatus = UPDATE_STATUS_UPDATE_OK;
		}
		else
		{
			stUpdateInfo.eUpdateStatus = UPDATE_STATUS_UPDATE_FALSE;
		}


		stm32_flash_erase_sector(UPDATE_INFO_START_ADDR / ONE_SECTOR_SIZE);
		stm32_flash_write(UPDATE_INFO_START_ADDR,&stUpdateInfo,sizeof(stUpdateInfo));
		
#if 0
		DBG_Print(LEVEL0,"------------------------Update Info------------------------\r\n"
						 "Update Server:%s:%d DownloadFile:%s\r\n"
						 "Store Address In W25Q32:0x%08X ~ 0x%08X\r\n"
						 "TotalSize:%u TotalPackCnt:%u\r\n"
						 "Time:%02d/%02d/%02d %02d:%02d:%02d ~ %02d/%02d/%02d %02d:%02d:%02d\r\n"
						 "Take Times:%us status:%02X way:%d\r\n"
						 "-----------------------------------------------------------\r\n",
						stUpdateInfo.szServerAddr,stUpdateInfo.usServerPort,stUpdateInfo.szUpdateFileName,
						stUpdateInfo.ulStartAddr,stUpdateInfo.ulEndAddr,
						stUpdateInfo.ulTotalBytes,stUpdateInfo.usTotalPackCnt,
						stUpdateInfo.stStartTime.year,stUpdateInfo.stStartTime.month,
						stUpdateInfo.stStartTime.day,stUpdateInfo.stStartTime.hour,
						stUpdateInfo.stStartTime.min,stUpdateInfo.stStartTime.sec,
		
						stUpdateInfo.stEndTime.year,stUpdateInfo.stEndTime.month,
						stUpdateInfo.stEndTime.day,stUpdateInfo.stEndTime.hour,
						stUpdateInfo.stEndTime.min,stUpdateInfo.stEndTime.sec,
						stUpdateInfo.ulTakeTimes,stUpdateInfo.eUpdateStatus,
						stUpdateInfo.ucUpdateWay
						 );
#endif
		JumpToApp();
	}
}



void monitor_xmodem(void *buf,unsigned int len)
{
	char *ptr = 0;
	char *headptr = 0;
	unsigned int rxlen = 0;
	static unsigned char last_bag = 0;
	static unsigned int idx = 0;
	static unsigned long swlen = 0;
	static unsigned char s_first_bag_flag = 1;

	if ((len == 0) || (buf == 0)) return ;
	ptr = (char *)buf;
	rxlen = len;
	if (rxlen >= XMODEM_PACK_SIZE)
	{
		headptr = (char *)_FindChar(ptr,rxlen,STX);
		if (headptr)
		{
			if (CheckPackIsOk(headptr))
			{
				if (s_first_bag_flag)
				{
					s_first_bag_flag = 0;
					//寻找驱动文件标识
					if (
					(headptr[3 + LF_DRIVER_FILE_FLAG1_OFFSET + 0] +
					(headptr[3 + LF_DRIVER_FILE_FLAG1_OFFSET + 1] << 8) +
					(headptr[3 + LF_DRIVER_FILE_FLAG1_OFFSET + 2] << 16) +
					(headptr[3 + LF_DRIVER_FILE_FLAG1_OFFSET + 3] << 24)
					)
					== LF_DRIVER_FILE_FLAG1
					)
					{
						IAP_ProgramInit(DRIVER_START_ADDR,APP_END_ADDR);
					}
					else
					{
						IAP_ProgramInit(APP_START_ADDR,APP_END_ADDR);
					}
				}
				ucStatusFlag = 1;
				memcpy(pagebuf + idx * XMODEM_DATA_LEN,headptr + 3,XMODEM_DATA_LEN);
				idx++;
				if (idx == (FLASH_PAGE_SIZE / XMODEM_DATA_LEN))
				{
					idx = 0;
#if 0
					if (is_spi_flash_ok())
					{
						spi_flash_write(s_addr,pagebuf,FLASH_PAGE_SIZE);
					}
					else
					{
						IAP_ProgramWrite(pagebuf,FLASH_PAGE_SIZE);
					}
#else
					cpu_int_dis();
					IAP_ProgramWrite(pagebuf,FLASH_PAGE_SIZE);
					cpu_int_en();
#endif
					swlen += FLASH_PAGE_SIZE;
					last_bag = 1;
				}
				else
				{
					last_bag = 0;
				}
				DBG_SendChar(ACK);
			}
			else
			{
				DBG_SendChar(NAK);
			}
		}
	}
	else if ((ptr[0] == EOT) && (rxlen == 1))	//结束
	{
		s_first_bag_flag = 1;
		if (last_bag == 0)
		{
		#if 0
			if (is_spi_flash_ok())
			{
				spi_flash_write(s_addr,pagebuf,FLASH_PAGE_SIZE);
			}
			else
			{
				IAP_ProgramWrite(pagebuf,FLASH_PAGE_SIZE);
			}
		#else
			cpu_int_dis();
			IAP_ProgramWrite(pagebuf,FLASH_PAGE_SIZE);
			cpu_int_en();
		#endif


			swlen += FLASH_PAGE_SIZE;	
		}

		JumpToApp();
	}
	else
	{
		//DBG_SendChar(NAK);
	}
}


void check_usart_update(void)
{
#if 1
	JumpToApp();
#else
	static unsigned char cuu_buf[2048] = {0};
	unsigned int rlen = 0;
	int i = 0;
	//char is_intel = 0;
	//char is_extern = 0;
	//char tempbuf[8] = {0};

	IAP_ProgramInit(DRIVER_START_ADDR,APP_END_ADDR);

	for (i = 0; i < 3; i++)
	{
		DBG_SendChar(XMODEM_START_FLAG);
		delayms_by_timer(500);

		memset(cuu_buf,0,sizeof(cuu_buf));
		rlen = ReadDBGUsart(0,cuu_buf,sizeof(cuu_buf),0);

		monitor_xmodem(cuu_buf,rlen);
		if (ucStatusFlag)
		{
			break;
		}
	}

	if (ucStatusFlag == 0)
	{
		JumpToApp();
	}
	else
	{
		enter_update_mode();
	}

	while (1)
	{
		memset(cuu_buf,0,sizeof(cuu_buf));
		rlen = ReadDBGUsart(0,cuu_buf,sizeof(cuu_buf),0);

		if (rlen)
		{
			monitor_xmodem(cuu_buf,rlen);
		}

		//Delay(10);
	}
#endif
}

char s_update_mode = 0;

void enter_update_mode(void)
{
	s_update_mode = 1;
}

char is_update_mode(void)
{
	return s_update_mode;
}

void delayms(unsigned long t)
{
	volatile unsigned long i = 0;
	for (i = 0; i < t; i++);
}


