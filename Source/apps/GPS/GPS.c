#include "GPS.h"

typedef struct tagGPS
{
	INT8U ucGpsMode;		//模式指示(A=自主定位，D=差分，E=估算，N=数据无效)
	INT8U ucGpsStatus;		//
	INT8U ucPositionStatus;	//定位状态'A' 'V'
	INT32U ulLat;		//纬度
	INT8U ucNS;		//南北纬
	INT32U ulLong;		//经度
	INT8U ucEW;		//东西经
	INT16U usGpsSpeed;	//单位:0.1Km/h  速度扩大10倍
	INT16U usAngle;		//方向角

	INT16U usPDOP;		//扩大10倍 综合位置精度因子(0.5 - 99.9)
	INT16U usHDOP;		//扩大10倍 水平精度因子(0.5 - 99.9)
	INT16U usVDOP;		//扩大10倍 垂直精度因子(0.5 - 99.9)

}GPS;

static GPS s_stGPS = {0};

//获取GPS速度
INT16U GetGpsSpeed(void)
{
	return s_stGPS.usGpsSpeed;
}

INT16U GetAngle(void)
{
	return s_stGPS.usAngle;
}

INT8U GetEW(void)
{
	return s_stGPS.ucEW;
}

INT8U GetNS(void)
{
	return s_stGPS.ucNS;
}

//获取经度
INT32U GetLong(void)
{
	return s_stGPS.ulLong;
}

//获取纬度
INT32U GetLat(void)
{
	return s_stGPS.ulLat;
}

void DispGpsInfo(void)
{
	DBG_Print(LEVEL5,"%c Lat:%u(%c) Long:%u(%c) GPSSpeed:%d\r\n"
				"PDOP:%d HDOP:%d VDOP:%d\r\n",
	((s_stGPS.ucPositionStatus == 'A') || (s_stGPS.ucPositionStatus == 'V')) ? s_stGPS.ucPositionStatus : 'V' ,
	s_stGPS.ulLat,
	((s_stGPS.ucNS == 'N') || (s_stGPS.ucNS == 'S')) ? s_stGPS.ucNS : 'N',
	s_stGPS.ulLong,
	((s_stGPS.ucEW == 'E') || (s_stGPS.ucEW == 'W')) ? s_stGPS.ucEW : 'E',
	s_stGPS.usGpsSpeed,s_stGPS.usPDOP,s_stGPS.usHDOP,s_stGPS.usVDOP);
}


int GGA_Analyze(void *buf)
{
	char *ptr = (char *)buf;
	char *pTemp = 0;
	char *pHead = 0;
	char *pTail = 0;
	char szTemp[24] = {0};
	unsigned char i = 0;
	unsigned int uiSectionCnt = 0;

	if (ptr == 0)
	{
		return -1;
	}

	pHead = strstr(ptr,"GGA");
	if (pHead == 0)
	{
		return -2;
	}
	pTail = strstr(pHead,"*");
	if (pTail == 0)
	{
		DBG_Print(LEVEL0,"<GGA_Analyze>not find *(%s)\r\n",ptr);
		return -3;
	}

	//逗号出现了几次 就表示有多少个字段
	uiSectionCnt = FindSubArrayCnt(pHead,pTail - pHead,",",1);

	for (i = 1; i <= uiSectionCnt; i++)
	{
		if (i == uiSectionCnt)
		{
			pTemp = GetSubString(pHead,",","*",szTemp,sizeof(szTemp) - 1);
		}
		else
		{
			pTemp = GetSubString(pHead,",",",",szTemp,sizeof(szTemp) - 1);
		}
		if (pTemp)
		{
			pHead = pTemp + 1;
		}
		else
		{
			break;
		}
		switch (i)
		{
		case 1:
		{
			DBG_Print(LEVEL7,"<GGA>UTC:%s\r\n",szTemp);
		}
		break;
		case 2:
		{
			DBG_Print(LEVEL7,"<GGA>Lat:%s\r\n",szTemp);
			s_stGPS.ulLat = atof(szTemp) * 1000000ul;
		}
		break;
		case 3:
		{
			DBG_Print(LEVEL7,"<GGA>NS:%s\r\n",szTemp);
			s_stGPS.ucNS = szTemp[0];
		}
		break;
		case 4:
		{
			DBG_Print(LEVEL7,"<GGA>Long:%s\r\n",szTemp);
			s_stGPS.ulLong = atof(szTemp) * 1000000ul;
		}
		break;
		case 5:
		{
			DBG_Print(LEVEL7,"<GGA>EW:%s\r\n",szTemp);
			s_stGPS.ucEW = szTemp[0];
		}
		break;
		case 6:
		{
			DBG_Print(LEVEL7,"<GGA>Gps Status:%s\r\n",szTemp);
		}
		break;
		case 7:
		{
			DBG_Print(LEVEL7,"<GGA>Start num:%s\r\n",szTemp);
		}
		break;
		case 8:
		{
			DBG_Print(LEVEL7,"<GGA>HDOP:%s\r\n",szTemp);
		}
		break;
		case 9:	//海拔高度
		{
			DBG_Print(LEVEL7,"<GGA>haibagaodu:%s\r\n",szTemp);
		}
		break;
		case 10:	//固定字符'M'
		{
			DBG_Print(LEVEL7,"<GGA>M:%s\r\n",szTemp);
		}
		break;
		case 11:	//地球椭球面相对大地水准面的高度
		{
			DBG_Print(LEVEL7,"<GGA>tuoqiumiangaodu:%s\r\n",szTemp);
		}
		break;
		case 12:	//固定字符'M'
		{
			DBG_Print(LEVEL7,"<GGA>M:%s\r\n",szTemp);
		}
		break;
		case 13:	//差分时间(从最近一次接收到差分信号开始的秒数，如果不是差分定位将为空)
		{
			DBG_Print(LEVEL7,"<GGA>Cha fen Time:%s\r\n",szTemp);
		}
		break;
		case 14:
		{
			DBG_Print(LEVEL7,"<GGA>Cha fen zhan ID:%s\r\n",szTemp);
		}
		break;
		default:break;
		}
	}

	return 0;
}

int GSA_Analyze(void *buf)
{
	char *ptr = (char *)buf;
	char *pTemp = 0;
	char *pHead = 0;
	char *pTail = 0;
	char szTemp[24] = {0};
	unsigned char i = 0;
	unsigned int uiSectionCnt = 0;

	if (ptr == 0)
	{
		return -1;
	}

	pHead = strstr(ptr,"GSA");
	if (pHead == 0)
	{
		return -2;
	}
	pTail = strstr(pHead,"*");
	if (pTail == 0)
	{
		DBG_Print(LEVEL0,"<GSA_Analyze>not find *(%s)\r\n",ptr);
		return -3;
	}

	//逗号出现了几次 就表示有多少个字段
	uiSectionCnt = FindSubArrayCnt(pHead,pTail - pHead,",",1);

	for (i = 1; i <= uiSectionCnt; i++)
	{
		if (i == uiSectionCnt)
		{
			pTemp = GetSubString(pHead,",","*",szTemp,sizeof(szTemp) - 1);
		}
		else
		{
			pTemp = GetSubString(pHead,",",",",szTemp,sizeof(szTemp) - 1);
		}
		if (pTemp)
		{
			pHead = pTemp + 1;
		}
		else
		{
			break;
		}
		switch (i)
		{
		case 1:
		{
			DBG_Print(LEVEL7,"<GSA>mode:%s\r\n",szTemp);
		}
		break;
		case 2:
		{
			DBG_Print(LEVEL7,"<GSA>type:%s\r\n",szTemp);

		}
		break;
		case 3:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 4:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 5:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 6:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 7:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 8:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 9:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 10:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 11:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 12:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 13:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;
		case 14:
		{
			DBG_Print(LEVEL7,"<GSA>PRN:%s\r\n",szTemp);
		}
		break;

		case 15:
		{
			DBG_Print(LEVEL7,"<GSA>PDOP:%s\r\n",szTemp);
			s_stGPS.usPDOP = atof(szTemp) * 10u;
		}
		break;
		case 16:
		{
			DBG_Print(LEVEL7,"<GSA>HDOP:%s\r\n",szTemp);
			s_stGPS.usHDOP = atof(szTemp) * 10u;
		}
		break;
		case 17:
		{
			DBG_Print(LEVEL7,"<GSA>VDOP:%s\r\n",szTemp);
			s_stGPS.usVDOP = atof(szTemp) * 10u;
		}
		break;

		default:break;
		}
	}

	return 0;

}


int GSV_Analyze(void *buf)
{
	char *ptr = (char *)buf;
	char *pTemp = 0;
	char *pHead = 0;
	char *pTail = 0;
	char szTemp[24] = {0};
	unsigned char i = 0;
	unsigned int uiSectionCnt = 0;

	if (ptr == 0)
	{
		return -1;
	}

	pHead = strstr(ptr,"GSV");
	if (pHead == 0)
	{
		return -2;
	}
	pTail = strstr(pHead,"*");
	if (pTail == 0)
	{
		DBG_Print(LEVEL0,"<GSV_Analyze>not find *(%s)\r\n",ptr);
		return -3;
	}

	//逗号出现了几次 就表示有多少个字段
	uiSectionCnt = FindSubArrayCnt(pHead,pTail - pHead,",",1);

	for (i = 1; i <= uiSectionCnt; i++)
	{
		if (i == uiSectionCnt)
		{
			pTemp = GetSubString(pHead,",","*",szTemp,sizeof(szTemp) - 1);
		}
		else
		{
			pTemp = GetSubString(pHead,",",",",szTemp,sizeof(szTemp) - 1);
		}
		
		if (pTemp)
		{
			pHead = pTemp + 1;
		}
		else
		{
			break;
		}

		switch (i)
		{
		case 1:
		{
			DBG_Print(LEVEL7,"<GSV>gsv cnt:%s\r\n",szTemp);
		}
		break;
		case 2:
		{
			DBG_Print(LEVEL7,"<GSV>gsv idx:%s\r\n",szTemp);

		}
		break;
		case 3:
		{
			DBG_Print(LEVEL7,"<GSV>visible star total num:%s\r\n",szTemp);
		}
		break;
		case 4:		//卫星号
		{
			DBG_Print(LEVEL7,"<GSV>star no.:%s\r\n",szTemp);

		}
		break;
		case 5:		//卫星仰角
		{
			DBG_Print(LEVEL7,"<GSV>star yangjiao:%s\r\n",szTemp);

		}
		break;
		case 6:		//卫星方位角
		{
			DBG_Print(LEVEL7,"<GSV>star fangweijiao:%s\r\n",szTemp);
		}
		break;
		case 7:		//信噪比
		{
			DBG_Print(LEVEL7,"<GSV>xinzaobi:%s\r\n",szTemp);
		}
		break;
		case 8:		//卫星号
		{
			DBG_Print(LEVEL7,"<GSV>star no.:%s\r\n",szTemp);

		}
		break;
		case 9:		//卫星仰角
		{
			DBG_Print(LEVEL7,"<GSV>star yangjiao:%s\r\n",szTemp);

		}
		break;
		case 10:		//卫星方位角
		{
			DBG_Print(LEVEL7,"<GSV>star fangweijiao:%s\r\n",szTemp);
		}
		break;
		case 11:		//信噪比
		{
			DBG_Print(LEVEL7,"<GSV>xinzaobi:%s\r\n",szTemp);
		}
		break;

		case 12:		//卫星号
		{
			DBG_Print(LEVEL7,"<GSV>star no.:%s\r\n",szTemp);

		}
		break;
		case 13:		//卫星仰角
		{
			DBG_Print(LEVEL7,"<GSV>star yangjiao:%s\r\n",szTemp);

		}
		break;
		case 14:		//卫星方位角
		{
			DBG_Print(LEVEL7,"<GSV>star fangweijiao:%s\r\n",szTemp);
		}
		break;
		case 15:		//信噪比
		{
			DBG_Print(LEVEL7,"<GSV>xinzaobi:%s\r\n",szTemp);
		}
		break;

		case 16:		//卫星号
		{
			DBG_Print(LEVEL7,"<GSV>star no.:%s\r\n",szTemp);

		}
		break;
		case 17:		//卫星仰角
		{
			DBG_Print(LEVEL7,"<GSV>star yangjiao:%s\r\n",szTemp);

		}
		break;
		case 18:		//卫星方位角
		{
			DBG_Print(LEVEL7,"<GSV>star fangweijiao:%s\r\n",szTemp);
		}
		break;
		case 19:		//信噪比
		{
			DBG_Print(LEVEL7,"<GSV>xinzaobi:%s\r\n",szTemp);
		}
		break;

		default:break;
		}
	}

	return 0;

}


int RMC_Analyze(void *buf)
{
	char *ptr = (char *)buf;
	char *pTemp = 0;
	char *pHead = 0;
	char *pTail = 0;
	char szTemp[24] = {0};
	unsigned char i = 0;
	unsigned int uiSectionCnt = 0;

	if (ptr == 0)
	{
		return -1;
	}

	pHead = strstr(ptr,"RMC");
	if (pHead == 0)
	{
		return -2;
	}
	pTail = strstr(pHead,"*");
	if (pTail == 0)
	{
		DBG_Print(LEVEL0,"<RMC_Analyze>not find *(%s)\r\n",ptr);
		return -3;
	}

	//逗号出现了几次 就表示有多少个字段
	uiSectionCnt = FindSubArrayCnt(pHead,pTail - pHead,",",1);

	for (i = 1; i <= uiSectionCnt; i++)
	{
		if (i == uiSectionCnt)
		{
			pTemp = GetSubString(pHead,",","*",szTemp,sizeof(szTemp) - 1);
		}
		else
		{
			pTemp = GetSubString(pHead,",",",",szTemp,sizeof(szTemp) - 1);
		}
		if (pTemp)
		{
			pHead = pTemp + 1;
		}
		else
		{
			break;
		}
		switch (i)
		{
		case 1:
		{
			DBG_Print(LEVEL7,"<RMC>UTC:%s\r\n",szTemp);
		}
		break;
		case 2:
		{
			DBG_Print(LEVEL7,"<RMC>Position Status:%s\r\n",szTemp);
			s_stGPS.ucPositionStatus = szTemp[0];
		}
		break;
		case 3:
		{
			DBG_Print(LEVEL7,"<RMC>Lat:%s\r\n",szTemp);
			s_stGPS.ulLat = atof(szTemp) * 1000000ul;
		}
		break;
		case 4:
		{
			DBG_Print(LEVEL7,"<RMC>NS:%s\r\n",szTemp);
			s_stGPS.ucNS = szTemp[0];
		}
		break;
		case 5:
		{
			DBG_Print(LEVEL7,"<RMC>Long:%s\r\n",szTemp);
			s_stGPS.ulLong = atof(szTemp) * 1000000ul;
		}
		break;
		case 6:
		{
			DBG_Print(LEVEL7,"<RMC>EW:%s\r\n",szTemp);
			s_stGPS.ucEW = szTemp[0];
		}
		break;
		case 7:
		{
			DBG_Print(LEVEL7,"<RMC>Gps Speed:%s\r\n",szTemp);
			s_stGPS.usGpsSpeed = atof(szTemp) * 10;
		}
		break;
		case 8:
		{
			DBG_Print(LEVEL7,"<RMC>Angle:%s\r\n",szTemp);
			s_stGPS.usAngle = atoi(szTemp);
		}
		break;
		case 9:
		{
			DBG_Print(LEVEL7,"<RMC>Date(ddmmyy):%s\r\n",szTemp);
		}
		break;
		case 10:	//磁偏角
		{
			DBG_Print(LEVEL7,"<RMC>cipianjiao:%s\r\n",szTemp);
		}
		break;
		case 11:	//磁偏角方向
		{
			DBG_Print(LEVEL7,"<RMC>cipianjiaofangxiang:%s\r\n",szTemp);
		}
		break;
		case 12:	//模式指示(A=自主定位，D=差分，E=估算，N=数据无效)
		{
			DBG_Print(LEVEL7,"<RMC>mode:%s\r\n",szTemp);
		}
		break;
		default:break;
		}
	}

	return 0;
}

int GPS_Analyze(void *buf)
{
	DBG_Print(LEVEL_GPS,"%s",(char *)buf);
	DBG_Print(LEVEL5,"%s",(char *)buf);
	GSV_Analyze(buf);
	GGA_Analyze(buf);
	GSA_Analyze(buf);
	RMC_Analyze(buf);
	return 0;
}




int GPS_Init(int bps,int iParity)
{
	GpsUsartInit( bps, iParity);
	return 0;
}

//是否定位
char IsPosition(void)
{
	return (s_stGPS.ucPositionStatus == 'A') ? 1 : 0;
}

