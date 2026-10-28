#include "Store.h"
#include "stdlib.h"
#include "string.h"

#define READ_WRITE_STORE_FLAG	0xAA55

typedef struct tagStoreHardwareInterface
{
	StoreHWInitProc pFuncInit;
	StoreHWWriteProc pFuncWrite;
	StoreHWReadProc pFuncRead;
	StoreHWEraseProc pFuncEraseSector;
	unsigned int ulOneSectorSize;		//一个扇区有多少个字节
}StoreHardwareInterface;

StoreHardwareInterface s_stStoreHWI = {0};





//存储块结构体
typedef struct tagStoreBlock
{
	INT32U usStartSectorID;	//起始扇区号
	INT32U usSectorCnt;		//扇区个数
	INT16U usOneDataUnitSize;		//一个数据SIZE

	INT32U ulCap;				//该存储块的总容量(单位是:条数)
	INT32U ulUsed;				//已用记录条数
	INT32U ulFree;				//剩余可用
	INT32U ulAllExist;			//总记录条数 包括删除标记的数据

	INT32U ulWriteIdx;		//在该存储块中存储索引
	INT32U ulReadIdx;		//读取指针
	//INT32U ulDelIdx;		//删除已读数据索引 将已读数据置删除标志
	INT32U ulStartIdx;		//整个数据存储块的起始索引

	INT8U ucAlign;			//按多少字节对齐
}StoreBlock;

static StoreBlock s_astStoreBlock[MAX_STORE_BLOCK_CNT + 1] = {0};


typedef struct tagStoreReadWriteIndex
{
	INT32U flag;
	INT32U ulReadIdx[MAX_STORE_BLOCK_CNT];		//读索引
	INT32U ulWriteIdx[MAX_STORE_BLOCK_CNT];		//写索引
}StoreReadWriteIndex;

static StoreReadWriteIndex s_astIdx = {0};


#define DATA_OK_FLAG		0xAA		//数据有效标志
#define DATA_DEL_FLAG		0xBB		//数据删除标志


#define DATA_OK_FLAG_OFFSET		0
#define DATA_DEL_FLAG_OFFSET	1

char use_store_acce_service_flag = 0;

char is_use_store_acce_service(void)
{
	return use_store_acce_service_flag;
}

void set_use_store_acce_service(char val)
{
	use_store_acce_service_flag = val;
}


#if __USE_UCOS__
static OS_SEM sem_str = {0};

static int store_create_sem(void)
{
	static char cFlag = 0;
	OS_ERR err;

	if (cFlag == 0)
	{
		cFlag = 1;
		OSSemCreate(&sem_str,"sem_str",1,&err);
		if (err != OS_ERR_NONE)
		{
			return err;
		}
	}
	return 0;
}

static void store_wait_sem(void)
{
	OS_ERR err;

	OSSemPend(&sem_str,0,(OS_OPT  )OS_OPT_PEND_BLOCKING,(CPU_TS  )0,&err);
}

static void store_post_sem(void)
{
	OS_ERR	err;

	OSSemPost(&sem_str,(OS_OPT  )OS_OPT_POST_1,&err);
}
#elif __USE_LFOS__
static LFOS_SEM sem_str = {0};

static int store_create_sem(void)
{
	static char cFlag = 0;

	if (cFlag == 0)
	{
		cFlag = 1;
		lfos_create_sem(&sem_str,"sem_str",1);
	}
	return 0;
}

static void store_wait_sem(void)
{
	lfos_sem_pend(&sem_str,0);
}

static void store_post_sem(void)
{
	lfos_sem_post(&sem_str);
}


#else
static int store_create_sem(void)
{

	return 0;
}

static void store_wait_sem(void)
{

}

static void store_post_sem(void)
{

}

#endif

static unsigned int get_one_sector_size(void)
{
	return s_stStoreHWI.ulOneSectorSize;
}

static void erase_sector(unsigned int sector_id)   
{
	if (s_stStoreHWI.pFuncEraseSector)
	{
		s_stStoreHWI.pFuncEraseSector(sector_id);
	}
}

static unsigned int read_sector(unsigned int usSectorID,
									unsigned int usOffsetInSector,
									unsigned int usNumRead,void *buf,unsigned int len)
{
	unsigned int rlen = usNumRead;
	unsigned int OneSectorSize = get_one_sector_size();

	if ((buf == 0) || (len == 0))
	{
		return 0;
	}

	if (rlen >= len)
	{
		rlen = len;
	}

	if (rlen > (OneSectorSize - usOffsetInSector))
	{
		rlen = OneSectorSize - usOffsetInSector;
	}

	if (s_stStoreHWI.pFuncRead)
	{
		s_stStoreHWI.pFuncRead(usSectorID * OneSectorSize + usOffsetInSector,rlen,buf,len);
	}

	return rlen;
}

static unsigned int write_sector(unsigned int usSectorID,
									  unsigned int usOffsetInSector,
									  void *buf,unsigned int len)
{
	unsigned int temp = 0;
	unsigned int wbyte = 0;

	if ((buf == 0) || (len == 0)) return 0;

	temp = get_one_sector_size() - usOffsetInSector;
	if (len >= temp)
	{
		wbyte = temp;
	}
	else
	{
		wbyte = len;
	}
	//如果在偏移为0的地方 需要进行一次擦除动作
	if (usOffsetInSector == 0)
	{
		erase_sector(usSectorID);
	}

	if (s_stStoreHWI.pFuncWrite)
	{
		s_stStoreHWI.pFuncWrite((usSectorID * get_one_sector_size()) + usOffsetInSector,buf,wbyte);
	}

	return wbyte;
}


/**
函数功能:反向遍历存储的数据记录 返回记录条数(包括已读的记录)
入口参数:
	usStoreBlockNo:数据存储块序号
	max_cnt:反向遍历多少条数据
	buf:接收一条数据的缓冲区
	buflen:缓冲区size
	handler:回调函数 用于处理读取的数据
出口参数:
	pOutReadStartIdx:正向起始读索引
说明:例如 reverse_traversal(0,0,buf,buflen,handler,&ulStartIdx);
		  反向处理数据块0的所有数据 起始索引存放入ulStartIdx中
*/
unsigned long reverse_traversal(unsigned int usStoreBlockNo,unsigned long max_cnt,
				void *buf,unsigned int buflen,
				void (*handler)(unsigned long index,void *buf,unsigned int buflen),
				unsigned long *pOutReadStartIdx)
{
	unsigned long i = 0;
	unsigned long temp = 0;
	unsigned long ulTailIdx = 0;
	unsigned long ulTempReadIdx = 0;
	unsigned int cap = 0;
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned char dat[16] = {0};
	unsigned char ucAlign = 0;
	unsigned long cnt = 0;
	unsigned int rlen = 0;

	if ((usStoreBlockNo >= MAX_STORE_BLOCK_CNT) || (buf == 0) || (buflen == 0))
	{
		return 0;
	}

	if ((s_astStoreBlock[usStoreBlockNo].ulCap == 0) || (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0))
	{
		return 0;
	}
	ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;
	cap = s_astStoreBlock[usStoreBlockNo].ulCap;
	ulTailIdx = s_astStoreBlock[usStoreBlockNo].ulWriteIdx;
	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	if (max_cnt)
	{
		temp = (max_cnt >= cap) ? cap : max_cnt;
	}
	else
	{
		temp = cap;
	}

	for (i = 0; i < temp; i++)
	{
		if (ulTailIdx >= (1 + i))
		{
			ulTempReadIdx = ulTailIdx - 1 - i;
		}
		else
		{
			ulTempReadIdx = ulTailIdx + cap - 1 - i;
		}
		usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulTempReadIdx / cntpersector);
		usOffset = (ulTempReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

		store_wait_sem();
		read_sector(usSectorNo,usOffset,ucAlign * 2,dat,sizeof(dat));
		rlen = read_sector(usSectorNo,usOffset + 2 * ucAlign,
		s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign,
		buf,buflen);
		store_post_sem();

		if ((dat[DATA_OK_FLAG_OFFSET * ucAlign] == DATA_OK_FLAG)
		&& ((dat[DATA_DEL_FLAG_OFFSET * ucAlign] == DATA_DEL_FLAG) || (dat[DATA_DEL_FLAG_OFFSET * ucAlign] == 0xFF))
		)
		{
			cnt++;
			if (handler)
			{
				handler(i,buf,rlen);
			}
		}
		else
		{
			ulTempReadIdx++;
			if (ulTempReadIdx >= cap)
			{
				ulTempReadIdx = 0;
			}
			break;
		}
	}
	if (pOutReadStartIdx)
	{
		*pOutReadStartIdx = ulTempReadIdx;
	}
	return cnt;
}

//max_cnt遍历多少条
unsigned long store_view_history(unsigned int usStoreBlockNo,char IsForward,
				unsigned long max_cnt,
				void *buf,unsigned int buflen,
				void (*handler)(unsigned long index,void *buf,unsigned int buflen)
				)
{
	unsigned long i = 0;
	unsigned long cnt = 0;
	unsigned long ulStartIdx = 0;
	unsigned long tempidx = 0;
	unsigned long cap = 0;
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned int rlen = 0;
	unsigned char ucAlign = 0;
	unsigned char dat[16] = {0};

	if (IsForward)			//正向遍历
	{
		cnt = reverse_traversal(usStoreBlockNo,max_cnt,buf,buflen,0,&ulStartIdx);
		if (cnt == 0) return 0;
		cap = s_astStoreBlock[usStoreBlockNo].ulCap;
		ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;

		cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

		for (i = 0; i < cnt; i++)
		{
			tempidx = (ulStartIdx + i);
			if (tempidx >= cap)
			{
				tempidx -= cap;
			}
			
			usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (tempidx / cntpersector);
			usOffset = (tempidx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

			store_wait_sem();
			read_sector(usSectorNo,usOffset,ucAlign * 2,dat,sizeof(dat));
			rlen = read_sector(usSectorNo,usOffset + 2 * ucAlign,
			s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign,
			buf,buflen);

			store_post_sem();
			//判断数据的有效性
			if ((dat[DATA_OK_FLAG_OFFSET * ucAlign] == DATA_OK_FLAG)
			&& ((dat[DATA_DEL_FLAG_OFFSET * ucAlign] == DATA_DEL_FLAG) || (dat[DATA_DEL_FLAG_OFFSET * ucAlign] == 0xFF))
			)
			{
				if (handler)
				{
					handler(i,buf,rlen);
				}
			}
		}
		return cnt;
	}
	else					//反向遍历
	{
		return reverse_traversal(usStoreBlockNo,max_cnt,buf,buflen,handler,0);
	}
}


unsigned int ReadStoreBlock(unsigned int usStoreBlockNo,unsigned int idx,void *buf,unsigned int buflen)
{
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned long ulReadIdx = 0;

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT) || (buf == 0) || (buflen == 0))
	{
		return 0;
	}
	if ((s_astStoreBlock[usStoreBlockNo].ulCap == 0) || (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0))
	{
		return 0;
	}

	//idx超标
	if (idx >= s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		return 0;
	}
	ulReadIdx = idx;

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulReadIdx / cntpersector);
	usOffset = (ulReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	return read_sector(usSectorNo,usOffset,s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize,
	buf,buflen);
}



/**
函数块:创建数据存储块
入口函数:
	usStoreBlockNo:数据存储块编号 0-15
	usStartSectorID:起始扇区编号 0-511
	usSectorCnt:扇区数量	1-512
	usOneDataUnitSize:一个数据单元占用多少SIZE 0-4096 如果传入0 表示该数据库是按连续读写的方式
出口函数:
返回值:
说明:
*/
int CreateStoreBlock(unsigned int usStoreBlockNo,unsigned int usStartSectorID,
							unsigned int usSectorCnt,unsigned int usOneDataUnitSize,
							unsigned char ucAlign)
{
	unsigned char dat[16] = {0};
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int cntpersector = 0;
	char cCurDataFlag = 0;
	char cLastDataFlag = 3;
	unsigned int OneSectorSize = get_one_sector_size();
	unsigned char ucAlign1 = ucAlign;

	if (ucAlign1 == 0) ucAlign1 = 2;

	if ((usOneDataUnitSize + 2 * ucAlign1) > OneSectorSize)
	{
		return -3;
	}
	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT) || (usSectorCnt == 0))
	{
		return -1;
	}
	//表示该块号被占用
	if (s_astStoreBlock[usStoreBlockNo].usSectorCnt)
	{
		return -2;
	}
	//0表示连续读写
	if (usOneDataUnitSize == 0)
	{
		s_astStoreBlock[usStoreBlockNo].usStartSectorID = usStartSectorID;
		s_astStoreBlock[usStoreBlockNo].usSectorCnt = usSectorCnt;
		s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize = 0;
		return 0;
	}

	s_astStoreBlock[usStoreBlockNo].ucAlign = ucAlign1;		//按多少字节对齐
	s_astStoreBlock[usStoreBlockNo].usStartSectorID = usStartSectorID;
	s_astStoreBlock[usStoreBlockNo].usSectorCnt = usSectorCnt;
	s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize = usOneDataUnitSize + 2 * ucAlign1;

	s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize = ((s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize + ucAlign - 1) / ucAlign) * ucAlign;

	if (s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize < 256)
	{
		s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize = 256;
	}

	//前两个字节放删除 写入标志
	cntpersector = OneSectorSize / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	s_astStoreBlock[usStoreBlockNo].ulCap = (cntpersector * usSectorCnt);
	s_astStoreBlock[usStoreBlockNo].ulUsed = 0;
	s_astStoreBlock[usStoreBlockNo].ulFree = 0;

	s_astStoreBlock[usStoreBlockNo].ulWriteIdx = 0;
	s_astStoreBlock[usStoreBlockNo].ulReadIdx = 0;
	//s_astStoreBlock[usStoreBlockNo].ulStartIdx = 0;

	if (is_use_store_acce_service() && (usStoreBlockNo < MAX_STORE_BLOCK_CNT))
	{
		if ((s_astIdx.ulReadIdx[usStoreBlockNo] >= s_astStoreBlock[usStoreBlockNo].ulCap)
		|| (s_astIdx.ulWriteIdx[usStoreBlockNo] >= s_astStoreBlock[usStoreBlockNo].ulCap))
		{
			s_astIdx.ulReadIdx[usStoreBlockNo] = s_astIdx.ulWriteIdx[usStoreBlockNo] = 0;
		}
		s_astStoreBlock[usStoreBlockNo].ulReadIdx = s_astIdx.ulReadIdx[usStoreBlockNo];
		s_astStoreBlock[usStoreBlockNo].ulWriteIdx = s_astIdx.ulWriteIdx[usStoreBlockNo];
		DBG_Print(LEVEL2,"createblock %u readidx:%u writeidx:%u\r\n",usStoreBlockNo,
		s_astIdx.ulReadIdx[usStoreBlockNo],s_astIdx.ulWriteIdx[usStoreBlockNo]);
	}
	else
	{
		//统计数据块中记录条数 和 剩余容量
		for (i = 0; i < usSectorCnt; i++)
		{
			for (j = 0; j < cntpersector; j++)
			{
				read_sector(i+usStartSectorID,j * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize,
				ucAlign1 * 2,dat,sizeof(dat));
				//判断数据是否有效标志
				if ((dat[DATA_OK_FLAG_OFFSET * ucAlign1] == DATA_OK_FLAG) 
				&& (dat[DATA_DEL_FLAG_OFFSET * ucAlign1] == 0xFF)
				)
				{
					cCurDataFlag = 1;	//数据有效
					//s_astStoreBlock[usStoreBlockNo].ulUsed++;
					s_astStoreBlock[usStoreBlockNo].ulAllExist++;
				}
				else
				{
					cCurDataFlag = 0;		//数据无效
					//s_astStoreBlock[usStoreBlockNo].ulFree++;
		
					if ((dat[DATA_OK_FLAG_OFFSET * ucAlign1] == DATA_OK_FLAG) 
						&& (dat[DATA_DEL_FLAG_OFFSET * ucAlign1] == DATA_DEL_FLAG))
					{
						s_astStoreBlock[usStoreBlockNo].ulAllExist++;
					}
				}
		
				//数据有效性发生跳变
				if (cCurDataFlag != cLastDataFlag)
				{
					cLastDataFlag = cCurDataFlag;
					if (cCurDataFlag == 1)	//有效则保存ReadIdx
					{
						s_astStoreBlock[usStoreBlockNo].ulReadIdx = i * cntpersector + j;
						DBG_Print(LEVEL2,"StoreBlock%d sector:%u offset:%u effective:%u\r\n",
						usStoreBlockNo,
						i+usStartSectorID,j * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize,
						s_astStoreBlock[usStoreBlockNo].ulReadIdx);
					}
					else					//无效则保存WriteIdx
					{
						s_astStoreBlock[usStoreBlockNo].ulWriteIdx = i * cntpersector + j;
						DBG_Print(LEVEL2,"StoreBlock%d sector:%u offset:%u invalid:%u\r\n",
						usStoreBlockNo,
						i+usStartSectorID,j * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize,
						s_astStoreBlock[usStoreBlockNo].ulWriteIdx);
					}
				}
		
			}
		}

	}


	//计算已用空间和空闲空间
	if (s_astStoreBlock[usStoreBlockNo].ulReadIdx > s_astStoreBlock[usStoreBlockNo].ulWriteIdx)
	{
		s_astStoreBlock[usStoreBlockNo].ulUsed = s_astStoreBlock[usStoreBlockNo].ulWriteIdx +
												s_astStoreBlock[usStoreBlockNo].ulCap - 
												s_astStoreBlock[usStoreBlockNo].ulReadIdx;
	}
	else if (s_astStoreBlock[usStoreBlockNo].ulReadIdx < s_astStoreBlock[usStoreBlockNo].ulWriteIdx)
	{
		s_astStoreBlock[usStoreBlockNo].ulUsed = s_astStoreBlock[usStoreBlockNo].ulWriteIdx - 
										s_astStoreBlock[usStoreBlockNo].ulReadIdx;
	}
	else
	{
		s_astStoreBlock[usStoreBlockNo].ulUsed = 0;
	}

	s_astStoreBlock[usStoreBlockNo].ulFree = s_astStoreBlock[usStoreBlockNo].ulCap - 
										s_astStoreBlock[usStoreBlockNo].ulUsed;	
	DBG_Print(LEVEL2,"<StoreBlock%02d>StartSectorID:%lu SectorCnt:%lu WriteIdx:%lu ReadIdx:%lu used:%u free:%u cap:%lu\r\n",
	usStoreBlockNo,usStartSectorID,usSectorCnt,
	s_astStoreBlock[usStoreBlockNo].ulWriteIdx,s_astStoreBlock[usStoreBlockNo].ulReadIdx,
	s_astStoreBlock[usStoreBlockNo].ulUsed,s_astStoreBlock[usStoreBlockNo].ulFree,
	s_astStoreBlock[usStoreBlockNo].ulCap);
	return 0;
}

/**
函数块:反向读取一个数据单元
入口函数:
	usStoreBlockNo:数据存储块编号 0-15
	index:倒数第几个数据单元 从0开始
	buf:接收数据的缓冲区
	buflen:缓冲区大小
出口函数:
	无
返回值:
	表示读取了多少个字节 0表示失败
说明:
*/
int ReadOneData_Reverse(unsigned int usStoreBlockNo,unsigned int index,void *buf,unsigned int buflen)
{
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned int ulReadIdx = 0;
	unsigned int ret = 0;
	unsigned char ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT) || (buf == 0) || (buflen == 0))
	{
		return 0;
	}
	if ((s_astStoreBlock[usStoreBlockNo].ulCap == 0) || (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0))
	{
		return 0;
	}

	if (ucAlign == 0) ucAlign = 1;

	store_wait_sem();

	index %= s_astStoreBlock[usStoreBlockNo].ulCap;

	if (s_astStoreBlock[usStoreBlockNo].ulWriteIdx >= (1 + index))
	{
		ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulWriteIdx - 1 - index;
	}
	else
	{
		ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulWriteIdx + 
					s_astStoreBlock[usStoreBlockNo].ulCap - 1 - index;
	}

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulReadIdx / cntpersector);
	usOffset = (ulReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	DBG_Print(LEVEL3,"<ReadOneData_Reverse>index:%lu WriteIdx:%lu ReadIdx:%lu FactRead idx:%lu\r\n",
	index,s_astStoreBlock[usStoreBlockNo].ulWriteIdx,s_astStoreBlock[usStoreBlockNo].ulReadIdx,ulReadIdx);

	ret = read_sector(usSectorNo,usOffset + 2 * ucAlign,
	s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign,
	buf,buflen);
	store_post_sem();
	return ret;
}

char IsInSameSector(unsigned int idxdes,unsigned int idxsrc,unsigned int cntpersector)
{
	unsigned int usSectorDes = 0;
	unsigned int usSectorSrc = 0;

	if (cntpersector == 0) return 0;

	usSectorDes = idxdes / cntpersector;
	usSectorSrc = idxsrc / cntpersector;

	if (usSectorDes == usSectorSrc)
	{
		return 1;
	}
	return 0;
}

int store_fast_read(unsigned int usStoreBlockNo,unsigned long offset,unsigned int WantToRead,
							void *pdat,unsigned int datlen)
{
	unsigned long addr = 0;
	unsigned int rb = 0;

	if ((usStoreBlockNo >= MAX_STORE_BLOCK_CNT) || (pdat == 0) || (datlen == 0))
	{
		return 0;
	}

	if (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0)
	{
		return 0;
	}

	addr = s_stStoreHWI.ulOneSectorSize * s_astStoreBlock[usStoreBlockNo].usStartSectorID + offset;

	if (WantToRead > datlen)
	{
		rb = datlen;
	}
	else
	{
		rb = WantToRead;
	}
	store_wait_sem();
	if (s_stStoreHWI.pFuncRead)
	{
		s_stStoreHWI.pFuncRead(addr,rb,pdat,datlen);
	}
	store_post_sem();
	return rb;
}

int _store_fast_write(char is_int,unsigned int usStoreBlockNo,unsigned long offset,void *pdat,unsigned int datlen)
{
	unsigned long addr = 0;
	unsigned long nextaddr = 0;
	unsigned long endaddr = 0;
	unsigned long pos = 0;
	unsigned long len = 0;

	if ((usStoreBlockNo >= MAX_STORE_BLOCK_CNT) || (pdat == 0) || (datlen == 0))
	{
		return 0;
	}

	if (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0)
	{
		return 0;
	}
	addr = s_stStoreHWI.ulOneSectorSize * s_astStoreBlock[usStoreBlockNo].usStartSectorID + offset;
	endaddr = (s_astStoreBlock[usStoreBlockNo].usStartSectorID + s_astStoreBlock[usStoreBlockNo].usSectorCnt) * s_stStoreHWI.ulOneSectorSize;

	if (is_int == 0)
	{
		store_wait_sem();
	}

	while (datlen)
	{
		//不能写出界
		if (addr >= endaddr)
		{
			break;
		}
		//边界擦除
		if (addr % s_stStoreHWI.ulOneSectorSize == 0)
		{
			if (s_stStoreHWI.pFuncEraseSector)
			{
				s_stStoreHWI.pFuncEraseSector(addr / s_stStoreHWI.ulOneSectorSize);
			}
		}

		nextaddr = (addr / s_stStoreHWI.ulOneSectorSize + 1) * s_stStoreHWI.ulOneSectorSize;
		if ((addr + datlen) > nextaddr)
		{
			len = nextaddr - addr;
		}
		else
		{
			len = datlen;
		}
		if (s_stStoreHWI.pFuncWrite)
		{
			s_stStoreHWI.pFuncWrite(addr,(unsigned char *)pdat+pos,len);
		}
		datlen = datlen - len;
		pos += len;
		addr += len;
	}

	if (is_int == 0)
	{
		store_post_sem();
	}
	return pos;
}

int store_fast_write(unsigned int usStoreBlockNo,unsigned long offset,void *pdat,unsigned int datlen)
{
	return _store_fast_write(0,usStoreBlockNo,offset,pdat,datlen);
}

int store_fast_write_int(unsigned int usStoreBlockNo,unsigned long offset,void *pdat,unsigned int datlen)
{
	return _store_fast_write(1,usStoreBlockNo,offset,pdat,datlen);
}

void update_read_write_index(unsigned int usStoreBlockNo)
{
	if (usStoreBlockNo >= MAX_STORE_BLOCK_CNT)
	{
		return ;
	}

	s_astIdx.ulReadIdx[usStoreBlockNo] = s_astStoreBlock[usStoreBlockNo].ulReadIdx;
	s_astIdx.ulWriteIdx[usStoreBlockNo] = s_astStoreBlock[usStoreBlockNo].ulWriteIdx;
	StoreOneData(MAX_STORE_BLOCK_CNT,&s_astIdx,sizeof(s_astIdx));
	DBG_Print(LEVEL2,"<update_read_write_index>[%d]readidx:%u writeidx:%u\r\n",usStoreBlockNo,s_astIdx.ulReadIdx[usStoreBlockNo],
	s_astIdx.ulWriteIdx[usStoreBlockNo]);
}

void save_read_write_index(void)
{
	StoreOneData(MAX_STORE_BLOCK_CNT,&s_astIdx,sizeof(s_astIdx));
}

void disp_read_write_index(void)
{
	unsigned char i = 0;

	DBG_Print(LEVEL2,"<disp_read_write_index>(%08X)\r\n",s_astIdx.flag);
	for (i = 0; i < MAX_STORE_BLOCK_CNT; i++)
	{
		DBG_Print(LEVEL2,"[%d]readidx:%u writeidx:%u\r\n",i,
		s_astIdx.ulReadIdx[i],s_astIdx.ulWriteIdx[i]);
	}
}

void load_read_write_index(void)
{
	ReadOneData_Reverse(MAX_STORE_BLOCK_CNT,0,&s_astIdx,sizeof(s_astIdx));

	if (s_astIdx.flag != READ_WRITE_STORE_FLAG)
	{
		ReadOneData_Reverse(MAX_STORE_BLOCK_CNT,1,&s_astIdx,sizeof(s_astIdx));
		if (s_astIdx.flag != READ_WRITE_STORE_FLAG)
		{
			memset(&s_astIdx,0,sizeof(s_astIdx));
			s_astIdx.flag = READ_WRITE_STORE_FLAG;
			save_read_write_index();
		}
	}

	disp_read_write_index();
}

int StoreOneData(unsigned int usStoreBlockNo,void *pdat,unsigned int datlen)
{
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned long ulWriteIdx = 0;
	unsigned long ulReadIdx = 0;
	unsigned long ulStartIdx = 0;
	unsigned char datok[16] = {0};
	unsigned char ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;
	unsigned int remain = 0;

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT) || (pdat == 0) || (datlen == 0))
	{
		return -1;
	}

	if ((s_astStoreBlock[usStoreBlockNo].ulCap == 0) 
	|| (s_astStoreBlock[usStoreBlockNo].usSectorCnt == 0)
	|| (s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize == 0))
	{
		return -2;
	}
	
	store_wait_sem();
	if (ucAlign == 0) ucAlign = 1;
	if (datlen > (s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign))
	{
		datlen = s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign;
	}

	ulStartIdx = s_astStoreBlock[usStoreBlockNo].ulStartIdx;
	ulWriteIdx = s_astStoreBlock[usStoreBlockNo].ulWriteIdx;
	ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulReadIdx;

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulWriteIdx / cntpersector);
	usOffset = (ulWriteIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	//判断临界
	if ((usOffset == 0)
	&& s_astStoreBlock[usStoreBlockNo].ulAllExist
	&& (ulStartIdx >= ulWriteIdx))
	{
		remain = cntpersector - (ulStartIdx % cntpersector);
		s_astStoreBlock[usStoreBlockNo].ulStartIdx += remain;
		
		if (s_astStoreBlock[usStoreBlockNo].ulStartIdx >= s_astStoreBlock[usStoreBlockNo].ulCap)
		{
			s_astStoreBlock[usStoreBlockNo].ulStartIdx = 0;
		}

		if (s_astStoreBlock[usStoreBlockNo].ulAllExist >= remain)
		{
			s_astStoreBlock[usStoreBlockNo].ulAllExist -= remain;
		}
	}

	//判断写临界 要擦除一个扇区的内容 所以如果读索引在该扇区上 需要将读索引更新到下一个扇区
	if ((usOffset == 0) 
	&& s_astStoreBlock[usStoreBlockNo].ulUsed
	&& (ulReadIdx >= ulWriteIdx))
	{
		if (IsInSameSector(ulReadIdx,ulWriteIdx,cntpersector))
		{
			remain = cntpersector - (ulReadIdx % cntpersector);
			s_astStoreBlock[usStoreBlockNo].ulReadIdx += remain;

			if (s_astStoreBlock[usStoreBlockNo].ulReadIdx >= s_astStoreBlock[usStoreBlockNo].ulCap)
			{
				s_astStoreBlock[usStoreBlockNo].ulReadIdx = 0;
			}

			//s_astStoreBlock[usStoreBlockNo].ulStartIdx = s_astStoreBlock[usStoreBlockNo].ulReadIdx;
			s_astStoreBlock[usStoreBlockNo].ulFree += remain;
			if (s_astStoreBlock[usStoreBlockNo].ulUsed >= remain)
			{
				s_astStoreBlock[usStoreBlockNo].ulUsed -= remain;
			}
		}
		#if 0
		//判断 如果写索引在读索引和删除索引之间 则删除索引要越过写索引 进行删除操作		
		if (IsInSameSector(s_astStoreBlock[usStoreBlockNo].ulDelIdx,ulWriteIdx,cntpersector))
		{
			s_astStoreBlock[usStoreBlockNo].ulDelIdx = 
			((s_astStoreBlock[usStoreBlockNo].ulWriteIdx / cntpersector) + 1) * cntpersector;
		}
		//不能超过ReadIdx
		if (s_astStoreBlock[usStoreBlockNo].ulDelIdx > s_astStoreBlock[usStoreBlockNo].ulReadIdx)
		{
			s_astStoreBlock[usStoreBlockNo].ulDelIdx = s_astStoreBlock[usStoreBlockNo].ulReadIdx;
		}
		#endif
	}

	//写入数据有效标志
	memset(datok,DATA_OK_FLAG,ucAlign);
	write_sector(usSectorNo,usOffset,datok,ucAlign);

	//写入用户数据
	write_sector(usSectorNo,usOffset + ucAlign * 2,pdat,datlen);

	//空闲计数减一 已用计数加一
	if (s_astStoreBlock[usStoreBlockNo].ulFree)
	{
		s_astStoreBlock[usStoreBlockNo].ulFree--;
	}
	if (s_astStoreBlock[usStoreBlockNo].ulUsed < s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulUsed++;		//数据记录条数加一
	}

	if ((s_astStoreBlock[usStoreBlockNo].ulWriteIdx + 1) < s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulWriteIdx++;
	}
	else
	{
		s_astStoreBlock[usStoreBlockNo].ulWriteIdx = 0;
	}

	if (s_astStoreBlock[usStoreBlockNo].ulAllExist < s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulAllExist++;
	}
	else
	{
		s_astStoreBlock[usStoreBlockNo].ulAllExist = s_astStoreBlock[usStoreBlockNo].ulCap;
	}
	store_post_sem();

	//存入一条数据后 如果写索引和读索引相等了 说明该存储块满了 
	//为了防止掉电后能找到头尾指针 则不能让该存储块满 读索引要后移一个位置
	if (s_astStoreBlock[usStoreBlockNo].ulWriteIdx == s_astStoreBlock[usStoreBlockNo].ulReadIdx)
	{
		//强制读出一个数据出来 防止头尾相接 掉电后找不到头尾指针
		ReadOneDataOk(usStoreBlockNo);
	}

	DBG_Print(LEVEL3,"<StoreOneData>(%d)write idx:%u(last:%u) read idx:%u "
					"free:%u used:%u cap:%u\r\n",
	usStoreBlockNo,
	s_astStoreBlock[usStoreBlockNo].ulWriteIdx,ulWriteIdx,
	s_astStoreBlock[usStoreBlockNo].ulReadIdx,
	s_astStoreBlock[usStoreBlockNo].ulFree,s_astStoreBlock[usStoreBlockNo].ulUsed,
	s_astStoreBlock[usStoreBlockNo].ulCap);
	if (is_use_store_acce_service())
	{
		if (usStoreBlockNo != MAX_STORE_BLOCK_CNT)
		{
			update_read_write_index(usStoreBlockNo);
		}
	}

	return 0;
}

int ReadOneData(unsigned int usStoreBlockNo,void *buf,unsigned int buflen)
{
	unsigned char temp[16] = {0};
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned long ulReadIdx = 0;
	int ret = 0;
	unsigned char ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT) || (buf == 0) || (buflen == 0))
	{
		return -1;
	}

	//无数据
	if ((s_astStoreBlock[usStoreBlockNo].ulUsed == 0)
	|| (s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize == 0))
	{
		return -2;
	}

	store_wait_sem();
	ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulReadIdx;

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulReadIdx / cntpersector);
	usOffset = (ulReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	if (ucAlign == 0) ucAlign = 1;
	//判断数据有效性
	read_sector(usSectorNo,usOffset,2 * ucAlign,temp,sizeof(temp));
	store_post_sem();
	if ((temp[DATA_OK_FLAG_OFFSET * ucAlign] == DATA_OK_FLAG)
	&& (temp[DATA_DEL_FLAG_OFFSET * ucAlign] == 0xFF))
	{
		store_wait_sem();
		read_sector(usSectorNo, usOffset + 2 * ucAlign,
		s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize - 2 * ucAlign, buf,buflen);
		store_post_sem();
		DBG_Print(LEVEL3,"<ReadOneData>(%d)write idx:%u read idx:%u\r\n",
		usStoreBlockNo,s_astStoreBlock[usStoreBlockNo].ulWriteIdx,ulReadIdx);
		ret = 0;
	}
	else	//数据无效则进行下一个数据的读
	{
		DBG_Print(LEVEL0,"<ReadOneData>(%d)read idx:%lu FormatErr.(%02X %02X)\r\n",
		usStoreBlockNo,ulReadIdx,temp[DATA_OK_FLAG_OFFSET * ucAlign],
		temp[DATA_DEL_FLAG_OFFSET * ucAlign]);

		ReadOneDataOk(usStoreBlockNo);
		ret = -3;
	}
	return ret;
}

#if 0
//写入已读标记 ulDelIdx紧跟ulReadIdx
//返回值:0 表示 无数据可删 非0:表示有数据可删
char MarkAlreadyReadFlag(unsigned int usStoreBlockNo)
{
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned long ulReadIdx = 0;
	unsigned char datdelflag[16] = {0};
	unsigned char ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;

	if ((usStoreBlockNo >= MAX_STORE_BLOCK_CNT))
	{
		return 0;
	}

	//无可删除的数据
	if (s_astStoreBlock[usStoreBlockNo].ulReadIdx == s_astStoreBlock[usStoreBlockNo].ulDelIdx)
	{
		return 0;
	}

	ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulDelIdx;

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulReadIdx / cntpersector);
	usOffset = (ulReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	if (ucAlign == 0) ucAlign = 1;
	//写入数据删除标志
	memset(datdelflag,DATA_DEL_FLAG,ucAlign);
	write_sector(usSectorNo,usOffset + DATA_DEL_FLAG_OFFSET * ucAlign,datdelflag,ucAlign);

	s_astStoreBlock[usStoreBlockNo].ulDelIdx++;
	if (s_astStoreBlock[usStoreBlockNo].ulDelIdx >= s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulDelIdx = 0;
	}

	DBG_Print(LEVEL3,"<MarkAlreadyReadFlag>(%d)write idx:%u read idx:%u del idx:%u free:%d used:%u cap:%u\r\n",
	usStoreBlockNo,s_astStoreBlock[usStoreBlockNo].ulWriteIdx,
	s_astStoreBlock[usStoreBlockNo].ulReadIdx,s_astStoreBlock[usStoreBlockNo].ulDelIdx,
	s_astStoreBlock[usStoreBlockNo].ulFree,s_astStoreBlock[usStoreBlockNo].ulUsed,
	s_astStoreBlock[usStoreBlockNo].ulCap);
	return 1;
}
#endif

void ReadOneDataOk(unsigned int usStoreBlockNo)
{
	unsigned long ulReadIdx = 0;
	unsigned int usSectorNo = 0;
	unsigned int usOffset = 0;
	unsigned int cntpersector = 0;
	unsigned char datdelflag[16] = {0};
	unsigned char ucAlign = s_astStoreBlock[usStoreBlockNo].ucAlign;

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT))
	{
		return ;
	}
	//无数据
	if ((s_astStoreBlock[usStoreBlockNo].ulUsed == 0)
	|| (s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize == 0))
	{
		return ;
	}

	store_wait_sem();
	ulReadIdx = s_astStoreBlock[usStoreBlockNo].ulReadIdx;

	cntpersector = get_one_sector_size() / s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;
	usSectorNo = s_astStoreBlock[usStoreBlockNo].usStartSectorID + (ulReadIdx / cntpersector);
	usOffset = (ulReadIdx % cntpersector) * s_astStoreBlock[usStoreBlockNo].usOneDataUnitSize;

	if (ucAlign == 0) ucAlign = 1;
	//写入数据删除标志
	memset(datdelflag,DATA_DEL_FLAG,ucAlign);
	write_sector(usSectorNo,usOffset + DATA_DEL_FLAG_OFFSET * ucAlign,datdelflag,ucAlign);

	//读指针后移
	s_astStoreBlock[usStoreBlockNo].ulReadIdx++;
	if (s_astStoreBlock[usStoreBlockNo].ulReadIdx >= s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulReadIdx = 0;
	}
	if (s_astStoreBlock[usStoreBlockNo].ulUsed)
	{
		s_astStoreBlock[usStoreBlockNo].ulUsed--;
	}
	if (s_astStoreBlock[usStoreBlockNo].ulFree < s_astStoreBlock[usStoreBlockNo].ulCap)
	{
		s_astStoreBlock[usStoreBlockNo].ulFree++;
	}
	store_post_sem();

	DBG_Print(LEVEL3,"<ReadOneDataOk>(%d)write idx:%u read idx:%u(last:%u) "
	"free:%d used:%u cap:%u\r\n",
	usStoreBlockNo,s_astStoreBlock[usStoreBlockNo].ulWriteIdx,
	s_astStoreBlock[usStoreBlockNo].ulReadIdx,ulReadIdx,
	s_astStoreBlock[usStoreBlockNo].ulFree,s_astStoreBlock[usStoreBlockNo].ulUsed,
	s_astStoreBlock[usStoreBlockNo].ulCap);
	//MarkAlreadyReadFlag(usStoreBlockNo);	

	if (is_use_store_acce_service())
	{
		if (usStoreBlockNo != MAX_STORE_BLOCK_CNT)
		{
			update_read_write_index(usStoreBlockNo);
		}
	}
}

void EmptyStoreBlock(unsigned int usStoreBlockNo)
{
	unsigned int i = 0;
	unsigned char tempbuf[16] = {0};

	if ((usStoreBlockNo > MAX_STORE_BLOCK_CNT))
	{
		return ;
	}
	s_astStoreBlock[usStoreBlockNo].ulReadIdx = 0;
	s_astStoreBlock[usStoreBlockNo].ulWriteIdx = 0;
	//s_astStoreBlock[usStoreBlockNo].ulDelIdx = 0;
	s_astStoreBlock[usStoreBlockNo].ulFree = s_astStoreBlock[usStoreBlockNo].ulCap;
	s_astStoreBlock[usStoreBlockNo].ulUsed = 0;

	for (i = 0; i < s_astStoreBlock[usStoreBlockNo].usSectorCnt; i++)
	{
		read_sector(s_astStoreBlock[usStoreBlockNo].usStartSectorID + i,0,
		sizeof(tempbuf),tempbuf,sizeof(tempbuf));
		//该扇区头16个字节都为0xFF 则认为该扇区不需要擦除
		if (memcmp(tempbuf,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF",16))
		{
			erase_sector(s_astStoreBlock[usStoreBlockNo].usStartSectorID + i);
		}
		else
		{
			read_sector(s_astStoreBlock[usStoreBlockNo].usStartSectorID + i,sizeof(tempbuf),
			sizeof(tempbuf),tempbuf,sizeof(tempbuf));
			if (memcmp(tempbuf,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF",16))
			{
				erase_sector(s_astStoreBlock[usStoreBlockNo].usStartSectorID + i);
			}
		}
	}

	if ((usStoreBlockNo == MAX_STORE_BLOCK_CNT) && is_use_store_acce_service())
	{
		for (i = 0; i < MAX_STORE_BLOCK_CNT; i++)
		{
			s_astStoreBlock[i].ulReadIdx = 0;
			s_astStoreBlock[i].ulWriteIdx = 0;
			s_astStoreBlock[i].ulFree = s_astStoreBlock[i].ulCap;
			s_astStoreBlock[i].ulUsed = 0;
			update_read_write_index(i);
		}
	}
	
}

//查询数据存储块的容量
unsigned long GetStoreBlockCap(unsigned int usStoreBlockNo)
{
	if (usStoreBlockNo >= MAX_STORE_BLOCK_CNT)
	{
		return 0;
	}
	return s_astStoreBlock[usStoreBlockNo].ulCap;
}

unsigned long GetStoreBlockUsed(unsigned int usStoreBlockNo)
{
	if (usStoreBlockNo >= MAX_STORE_BLOCK_CNT)
	{
		return 0;
	}
	return s_astStoreBlock[usStoreBlockNo].ulUsed;
}

unsigned long GetStoreBlockFree(unsigned int usStoreBlockNo)
{
	if (usStoreBlockNo >= MAX_STORE_BLOCK_CNT)
	{
		return 0;
	}
	return s_astStoreBlock[usStoreBlockNo].ulFree;
}


int store_init(StoreHWInitProc pFuncInit,
					StoreHWWriteProc pFuncWrite,
					StoreHWReadProc pFuncRead,
					StoreHWEraseProc pFuncEraseSector,
					unsigned int ulOneSectorSize)
{
	s_stStoreHWI.pFuncInit = pFuncInit;
	s_stStoreHWI.pFuncWrite = pFuncWrite;
	s_stStoreHWI.pFuncRead = pFuncRead;
	s_stStoreHWI.pFuncEraseSector = pFuncEraseSector;
	s_stStoreHWI.ulOneSectorSize = ulOneSectorSize;

	if (s_stStoreHWI.pFuncInit)
	{
		s_stStoreHWI.pFuncInit();
	}
	return store_create_sem();
}

//开机加速服务
void store_acce_config(unsigned int usStartSectorID,unsigned int usSectorCnt)
{
	set_use_store_acce_service(1);
	CreateStoreBlock(MAX_STORE_BLOCK_CNT,usStartSectorID,usSectorCnt,
	sizeof(s_astIdx),2);
	load_read_write_index();	
}

void empty_acce_store_block(void)
{
	if (is_use_store_acce_service())
	{
		EmptyStoreBlock(MAX_STORE_BLOCK_CNT);
		DBG_Print(0, "empty_acce_store_block\r\n");
	}
}




