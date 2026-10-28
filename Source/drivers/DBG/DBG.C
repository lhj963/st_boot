#include "DBG.H"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

static char buf[2048] = {0};
static int s_ulLevel = LEVEL0;

typedef struct tagDBGUsart
{
	DBGUsartInit pDBGUsartInitFunc;		//串口初始化函数指针
	DBGUsartSend_unlock pDBGUsartSend;	//串口发送函数指针
	DBGUsartRead pDBGUsartRead;

	unsigned long bps;									//波特率
	char cParity;
}DBGUsart;


DBGUsart s_astDBGUsart[MAX_DBG_CNT] = {0};
unsigned long s_ulDBGUsartUsedFlag = 0;


#if __USE_UCOS__
static OS_SEM sem_dbg_tx = {0};
static OS_SEM sem_dbg_rx = {0};

static int create_sem(void)
{
	static char cFlag = 0;
	OS_ERR err;

	if (cFlag == 0)
	{
		cFlag = 1;
		OSSemCreate(&sem_dbg_tx,"dbg_tx",1,&err);
		if (err != OS_ERR_NONE)
		{
			return err;
		}
		OSSemCreate(&sem_dbg_rx,"dbg_rx",0,&err);
		if (err != OS_ERR_NONE)
		{
			return err;
		}
	}
	return 0;
}

static void WaitDbgTxSemNew(void)
{
	OS_ERR err;

	//s_astDBGUsart[0].pDBGUsartSend("wait sem.",strlen("wait sem."));
	OSSemPend(&sem_dbg_tx,0,(OS_OPT  )OS_OPT_PEND_BLOCKING,(CPU_TS  )0,&err);
	//s_astDBGUsart[0].pDBGUsartSend("wait sem. OK",strlen("wait sem. OK"));
}

static void PostDbgTxSemNew(void)
{
	OS_ERR	err;

	OSSemPost(&sem_dbg_tx,(OS_OPT  )OS_OPT_POST_1,&err);
}
#elif __USE_LFOS__
static LFOS_SEM sem_dbg_tx = {0};
//static LFOS_SEM sem_dbg_rx = {0};

static int create_sem(void)
{
	static char cFlag = 0;

	if (cFlag == 0)
	{
		cFlag = 1;
		lfos_create_sem(&sem_dbg_tx,"dbg_tx",1);
	}
	return 0;
}

static void WaitDbgTxSemNew(void)
{
	lfos_sem_pend(&sem_dbg_tx,0);
}

static void PostDbgTxSemNew(void)
{
	lfos_sem_post(&sem_dbg_tx);
}


#else
static int create_sem(void)
{

	return 0;
}

static void WaitDbgTxSemNew(void)
{

}

static void PostDbgTxSemNew(void)
{

}

#endif

int DBG_Init(unsigned char num,
				DBGUsartInit pDBGUsartInitFunc,
				unsigned long bps,char cParity,
				DBGUsartSend_unlock pDBGUsartSend_unlock,
				DBGUsartRead pDBGUsartRead
				)
{
	s_astDBGUsart[num].pDBGUsartInitFunc = pDBGUsartInitFunc;
	s_astDBGUsart[num].pDBGUsartSend = pDBGUsartSend_unlock;
	s_astDBGUsart[num].pDBGUsartRead = pDBGUsartRead;
	s_astDBGUsart[num].bps = bps;
	s_astDBGUsart[num].cParity = cParity;
	if (s_astDBGUsart[num].pDBGUsartInitFunc)
	{
		s_astDBGUsart[num].pDBGUsartInitFunc(bps,cParity);
		//s_astDBGUsart[num].pDBGUsartSend("hello",5);
	}
	/* 写入串口被占用标志 */
	s_ulDBGUsartUsedFlag |= (1 << num);
	return create_sem();
}


static void _DBG_SenDataNew(void *buf,int len)
{
	unsigned char i = 0;

	for (i = 0; i < MAX_DBG_CNT; i++)
	{
		if (s_ulDBGUsartUsedFlag & (1 << i))
		{
			if (s_astDBGUsart[i].pDBGUsartSend)
			{
				s_astDBGUsart[i].pDBGUsartSend(buf,len);
			}
		}
	}
}

unsigned int ReadDBGUsart(unsigned char DBG_PortNum,void *buf,
								unsigned int ulBufSize,unsigned int ulTimeoutMs)
{
	if (DBG_PortNum >= MAX_DBG_CNT) return 0;
	if (s_astDBGUsart[DBG_PortNum].pDBGUsartRead)
	{
		return s_astDBGUsart[DBG_PortNum].pDBGUsartRead(buf,ulBufSize,ulTimeoutMs);
	}
	return 0;
}

//打印等级检测
int IsLevelCheckOk(int iLevel)
{
#if __USE_UCOS__
	unsigned char ucDbgLevel = 0;
	unsigned char ucPrio = 0;

	if (iLevel == LEVEL0)
	{
		return 1;
	}

	//s_ulLevel低8位打印等级 高八位优先级
	ucDbgLevel = s_ulLevel & 0xFF;
	ucPrio = s_ulLevel >> 8;

	if (ucPrio)		//有优先级要求
	{
		if (OSPrioCur != ucPrio)
		{
			return 0;
		}
		if (ucDbgLevel < iLevel)
		{
			return 0;
		}
		return 1;
	}

#endif
	if (iLevel == LEVEL0)
	{
		return 1;
	}

	if ((s_ulLevel == LEVEL_GPRS) && (iLevel == LEVEL_GPRS))
	{
		return 1;
	}
	else if ((s_ulLevel == LEVEL_GPS) && (iLevel == LEVEL_GPS))
	{
		return 1;
	}
	else if ((s_ulLevel == LEVEL_CAN) && (iLevel == LEVEL_CAN))
	{
		return 1;
	}
	else
	{
		if (s_ulLevel > LEVEL9)
		{
			return 0;
		}
		if ((iLevel > s_ulLevel))
		{
			return 0;
		}

	}

	return 1;
}


void Set_DBG_Level(int iLevel)
{
	s_ulLevel = iLevel;
}

int Get_DBG_Level(void)
{
	return s_ulLevel;
}

int DBG_Print(int iLevel,void *str,...)
{
	unsigned int len = 0;
	va_list ap;

	if (str == 0) return 0;

	//检测打印等级
	if (IsLevelCheckOk(iLevel) == 0)
	{
		return 0;
	}

	WaitDbgTxSemNew();
	va_start(ap,str);
	len = vsnprintf(buf,sizeof(buf) - 1,(char *)str,ap);
	va_end(ap);
	if (len >= (int)sizeof(buf)) len = sizeof(buf) - 1;
	_DBG_SenDataNew(buf,len);
	PostDbgTxSemNew();
	return len;
}


void DBG_PrintBuf(int iLevel,void *tip,void *str,unsigned int length)
{
	unsigned int len = 0;
	unsigned int i = 0;
	unsigned char *ptr = (unsigned char *)str;

	if ((str == 0) || (length == 0)) return ;

	//检测打印等级
	if (IsLevelCheckOk(iLevel) == 0)
	{
		return ;
	}

	WaitDbgTxSemNew();

	//tip
	if (tip && strlen((char *)tip)) _DBG_SenDataNew(tip,strlen((char *)tip));

	for (i = 0; i < length; i++)
	{
		if (len >= (sizeof(buf) - 5))
		{
			_DBG_SenDataNew(buf,len);
			len = 0;
		}

		if ((i % 16 == 0) && i)
		{
			len += snprintf(buf + len,sizeof(buf) - len,"\r\n");
		}
		len += snprintf(buf + len,sizeof(buf) - len,"%02X ",*(ptr + i));
	}
	if (len) _DBG_SenDataNew(buf,len);
	_DBG_SenDataNew("\r\n",2);
	PostDbgTxSemNew();
}

unsigned char DBG_SendChar(unsigned char ch)
{
	unsigned char temp[2] = {0};

	temp[0] = ch;
	WaitDbgTxSemNew();
	_DBG_SenDataNew(temp,1);
	PostDbgTxSemNew();

	return ch;
}

void DBG_SendData(void *pdat,unsigned int len)
{
	WaitDbgTxSemNew();
	_DBG_SenDataNew(pdat,len);
	PostDbgTxSemNew();
}

void DBG_ChangeParam(unsigned char num,unsigned long bps,char cParity)
{
	char cFlag = 0;

	if (s_astDBGUsart[num].bps != bps)
	{
		s_astDBGUsart[num].bps = bps;
		cFlag = 1;
	}
	
	if (s_astDBGUsart[num].cParity != cParity)
	{
		s_astDBGUsart[num].cParity = cParity;
		cFlag = 1;
	}
	if (cFlag)
	{
		DBG_Init(num,s_astDBGUsart[num].pDBGUsartInitFunc,bps,cParity,
		s_astDBGUsart[num].pDBGUsartSend,s_astDBGUsart[num].pDBGUsartRead);
	}
}




