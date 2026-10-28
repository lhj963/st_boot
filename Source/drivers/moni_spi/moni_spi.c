#include "moni_spi.h"

/**
cs
mosi
miso
clk
*/
typedef struct tagMONISPI
{
	SETFUNC pSetCLKOutputMode;
	SETFUNC pSetMOSIOutputMode;
	SETFUNC pSetMISOIutputMode;

	SETVALUEFUNC pSetCLK;
	SETVALUEFUNC pSetMOSI;

	READFUNC pReadMISO;

	char CPOL;	//时钟极性  0:时钟空闲时为低电平  1:时钟空闲时为高电平
	char CPHA;	//时钟相位  0:时钟周期上升沿采集数据 下降沿输出数据     1:时钟周期下降沿采集数据 上升沿输出数据
	char IsMSBFirst;		//是否先传最高位
}MONISPI;




MONISPI s_astMONISPI[MAX_SPI_CNT] = {0};



int moni_spi_init(int num,
	SETFUNC pSetCLKOutputMode,
	SETFUNC pSetMOSIOutputMode,
	SETFUNC pSetMISOIutputMode,

	SETVALUEFUNC pSetCLK,
	SETVALUEFUNC pSetMOSI,

	READFUNC pReadMISO,
	char CPOL,
	char CPHA,
	char IsMSBFirst
	)
{
	if (num >= MAX_SPI_CNT)
	{
		return -1;
	}

	s_astMONISPI[num].pSetCLKOutputMode = pSetCLKOutputMode;
	s_astMONISPI[num].pSetMOSIOutputMode = pSetMOSIOutputMode;
	s_astMONISPI[num].pSetMISOIutputMode = pSetMISOIutputMode;

	s_astMONISPI[num].pSetCLK = pSetCLK;
	s_astMONISPI[num].pSetMOSI = pSetMOSI;

	s_astMONISPI[num].pReadMISO = pReadMISO;

	s_astMONISPI[num].CPOL = CPOL;
	s_astMONISPI[num].CPHA = CPHA;
	s_astMONISPI[num].IsMSBFirst = IsMSBFirst;

	//设置引脚输入输出模式
	if (s_astMONISPI[num].pSetCLKOutputMode) s_astMONISPI[num].pSetCLKOutputMode();
	if (s_astMONISPI[num].pSetMOSIOutputMode) s_astMONISPI[num].pSetMOSIOutputMode();
	if (s_astMONISPI[num].pSetMISOIutputMode) s_astMONISPI[num].pSetMISOIutputMode();

	//初始化各引脚状态
	if (s_astMONISPI[num].CPOL)		//极性为1是 空闲状态为高电平
	{
		if (s_astMONISPI[num].pSetCLK) s_astMONISPI[num].pSetCLK(1);
	}
	else							//极性为0是 空闲状态为低电平
	{
		if (s_astMONISPI[num].pSetCLK) s_astMONISPI[num].pSetCLK(0);
	}

	if (s_astMONISPI[num].pSetMOSI) s_astMONISPI[num].pSetMOSI(1);
	return 0;
}


void moni_spi_write_byte(int num,unsigned char dat)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	unsigned char cpol = s_astMONISPI[num].CPOL;
	unsigned char cpha = s_astMONISPI[num].CPHA;
	unsigned char is_msb_first = s_astMONISPI[num].IsMSBFirst;

	for (i = 0; i < 8; i++)
	{
		if (is_msb_first)
		{
			temp = dat & (1 << (7 - i));
		}
		else
		{
			temp = dat & (1 << i);
		}

		if (cpol == 0)		//极性为0
		{
			if (cpha == 0) 	//相位为0 在第一个边沿放入数据
			{
				if (temp)
				{
					if (s_astMONISPI[num].pSetMOSI)
					s_astMONISPI[num].pSetMOSI(1);
				}
				else
				{
					if (s_astMONISPI[num].pSetMOSI)
					s_astMONISPI[num].pSetMOSI(0);
				}

				if (s_astMONISPI[num].pSetCLK)
				s_astMONISPI[num].pSetCLK(1);
				if (s_astMONISPI[num].pSetCLK)
				s_astMONISPI[num].pSetCLK(0);

			}
			#if 1
			else			//相位为1 在第二个边沿放入数据
			{
				if (s_astMONISPI[num].pSetCLK)
				s_astMONISPI[num].pSetCLK(1);
				if (temp)
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(1);
				}
				else
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(0);
				}

				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);

			}
			#endif
		}
#if 1
		else				//极性为1
		{
			if (cpha == 0)		//相位为0 在第一个边沿放入数据
			{
				if (temp)
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(1);
				}
				else
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(0);
				}
				
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(1);

			}
			else				//相位为1 在第二个边沿放入数据
			{
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);
				if (temp)
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(1);
				}
				else
				{
					if (s_astMONISPI[num].pSetMOSI) 
					s_astMONISPI[num].pSetMOSI(0);
				}
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(1);
			}
		}
#endif
	}

}


unsigned char moni_spi_read_byte(int num)
{
	unsigned char i = 0;
	unsigned char dat = 0;
	unsigned char temp = 0;
	unsigned char cpol = s_astMONISPI[num].CPOL;
	unsigned char cpha = s_astMONISPI[num].CPHA;
	unsigned char is_msb_first = s_astMONISPI[num].IsMSBFirst;


	for (i = 0; i < 8; i++)
	{
		if (cpol == 0)			//极性为0	空闲状态电平为0
		{
			if (cpha == 0)		//相位为0 第一个边沿将数据读入
			{
				if (s_astMONISPI[num].pSetCLK)
				{
					s_astMONISPI[num].pSetCLK(1);
				}
				if (s_astMONISPI[num].pReadMISO)
				{
					temp = s_astMONISPI[num].pReadMISO();
				}
				if (s_astMONISPI[num].pSetCLK)
				{
					s_astMONISPI[num].pSetCLK(0);
				}
			}
			else				//相位为1 第二个边沿将数据读入
			{
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(1);
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);
				if (s_astMONISPI[num].pReadMISO) 
				temp = s_astMONISPI[num].pReadMISO();
			}
		}
		else					//极性为1 空闲状态电平为1
		{
			if (cpha == 0)		//相位为0 第一个边沿将数据读入
			{
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);
				if (s_astMONISPI[num].pReadMISO) 
				temp = s_astMONISPI[num].pReadMISO();
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(1);
			}
			else				//相位为1 第二个边沿将数据读入
			{
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(0);
				if (s_astMONISPI[num].pSetCLK) 
				s_astMONISPI[num].pSetCLK(1);
				if (s_astMONISPI[num].pReadMISO) 
				temp = s_astMONISPI[num].pReadMISO();
			}

		}

		if (is_msb_first)
		{
			if (temp)
			{
				dat |= (1 << (7 - i));
			}
		}
		else
		{
			if (temp)
			{
				dat |= (1 << i);
			}
		}	
	}

	return dat;
}




