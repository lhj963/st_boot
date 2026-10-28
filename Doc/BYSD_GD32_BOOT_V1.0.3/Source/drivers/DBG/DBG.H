#ifndef __DBG_H__
#define __DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __USE_UCOS__
#define __USE_UCOS__			0
#endif

#ifndef __USE_LFOS__
#define __USE_LFOS__			0
#endif


#define LEVEL0		0
#define LEVEL1		1
#define LEVEL2		2
#define LEVEL3		3
#define LEVEL4		4		//频率大概为2秒 3秒的信息 4级
#define LEVEL5		5		//1秒一条的信息 5级或5级以上
#define LEVEL6		6
#define LEVEL7		7
#define LEVEL8		8
#define LEVEL9		9

#define LEVEL_GPS	(LEVEL9 + 1)	//只打印GPS模块输出的信息
#define LEVEL_GPRS	(LEVEL9 + 2)	//只打印GPRS模块输出的信息
#define LEVEL_CAN	(LEVEL9 + 3)	//只打印CAN模块输出的信息


#define MAX_DBG_CNT 4


typedef void (*DBGUsartInit)(unsigned long bps,char cParity);
typedef unsigned int (*DBGUsartSend_unlock)(void *buf,unsigned int len);
typedef unsigned int (*DBGUsartRead)(void *buf,unsigned int ulBufSize,unsigned int ulTimeoutMs);


/**
函数功能:调试串口初始化
入口参数:
	num:标识第几路串口
	pDBGUsartInitFunc:串口初始化函数指针
	bps:波特率
	cParity:0无校验 1奇校验 2偶校验
	pDBGUsartSend_unlock:串口发送函数指针
	pDBGUsartRead:读串口函数指针
出口参数:
	无
返回值:无
*/
extern int DBG_Init(unsigned char num,
				DBGUsartInit pDBGUsartInitFunc,
				unsigned long bps,char cParity,
				DBGUsartSend_unlock pDBGUsartSend_unlock,
				DBGUsartRead pDBGUsartRead
				);

extern unsigned int ReadDBGUsart(unsigned char DBG_PortNum,void *buf,
					   				   unsigned int ulBufSize,unsigned int ulTimeoutMs);

extern void DBG_ChangeParam(unsigned char num,unsigned long bps,char cParity);


extern void Set_DBG_Level(int iLevel);

extern int Get_DBG_Level(void);

extern int DBG_Print(int iLevel,void *str,...);

extern void DBG_PrintBuf(int iLevel,void *tip,void *str,unsigned int length);

extern unsigned char DBG_SendChar(unsigned char ch);

extern void DBG_SendData(void *pdat,unsigned int len);



#ifdef __cplusplus
}
#endif

#endif


