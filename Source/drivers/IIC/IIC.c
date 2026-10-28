#include "IIC.h"
//////////////////////////////////////////////////////////////////////////////////	 
//IIC驱动 代码	   								  
//////////////////////////////////////////////////////////////////////////////////



typedef struct tagIICInterface
{
	DelayFunc pDelayFunc;
	SetSDAFunc pSetSDAFunc;
	SetSCLFunc pSetSCLFunc;
	ReadSDAFunc pReadSDAFunc;
	SetSDAOutputFunc pSetSDAOutputFunc;
	SetSDAInputFunc pSetSDAInputFunc;
	SetSCLOutputFunc pSetSCLOutputFunc;
}IICInterface;



IICInterface s_astIIC[MAX_IIC_CNT] = {0};

//初始化IIC
void IIC_Init(int num,
					DelayFunc pDelayFunc,
					SetSDAFunc pSetSDAFunc,
					SetSCLFunc pSetSCLFunc,
					ReadSDAFunc pReadSDAFunc,
					SetSDAOutputFunc pSetSDAOutputFunc,
					SetSDAInputFunc pSetSDAInputFunc,
					SetSCLOutputFunc pSetSCLOutputFunc
				)
{
	s_astIIC[num].pDelayFunc = pDelayFunc;
	s_astIIC[num].pSetSDAFunc = pSetSDAFunc;
	s_astIIC[num].pSetSCLFunc = pSetSCLFunc;
	s_astIIC[num].pReadSDAFunc = pReadSDAFunc;
	s_astIIC[num].pSetSDAOutputFunc = pSetSDAOutputFunc;
	s_astIIC[num].pSetSDAInputFunc = pSetSDAInputFunc;
	s_astIIC[num].pSetSCLOutputFunc = pSetSCLOutputFunc;
	//初始化为高电平
	if (s_astIIC[num].pSetSCLOutputFunc) s_astIIC[num].pSetSCLOutputFunc();
	if (s_astIIC[num].pSetSDAOutputFunc) s_astIIC[num].pSetSDAOutputFunc();
	if (s_astIIC[num].pSetSDAFunc) s_astIIC[num].pSetSDAFunc(1);
	if (s_astIIC[num].pSetSCLFunc) s_astIIC[num].pSetSCLFunc(1);
}

static void SDA_OUT(int num)
{
	if (s_astIIC[num].pSetSDAOutputFunc) s_astIIC[num].pSetSDAOutputFunc();
}

static void SDA_IN(int num)
{
	if (s_astIIC[num].pSetSDAInputFunc) s_astIIC[num].pSetSDAInputFunc();
}

static void SetIIC_SDA(int num,unsigned int val)
{
	if (s_astIIC[num].pSetSDAFunc) s_astIIC[num].pSetSDAFunc(val);
}

static void SetIIC_SCL(int num,unsigned int val)
{
	if (s_astIIC[num].pSetSCLFunc) s_astIIC[num].pSetSCLFunc(val);
}

static void delay_us(int num,unsigned int t)
{
	if (s_astIIC[num].pDelayFunc) s_astIIC[num].pDelayFunc(t);
}

static unsigned char ReadIIC_SDA(int num)
{
	if (s_astIIC[num].pReadSDAFunc) return s_astIIC[num].pReadSDAFunc();

	return 1;
}



//产生IIC起始信号
void IIC_Start(int num)
{
	SDA_OUT(num);     //sda线输出
	SetIIC_SDA(num,1);
	SetIIC_SCL(num,1);
	delay_us(num,4);
	SetIIC_SDA(num,0);//START:when CLK is high,DATA change form high to low 
	delay_us(num,4);
	SetIIC_SCL(num,0);//钳住I2C总线，准备发送或接收数据 
}
//产生IIC停止信号
void IIC_Stop(int num)
{
	SDA_OUT(num);//sda线输出
	SetIIC_SCL(num,0);
	SetIIC_SDA(num,0);//STOP:when CLK is high DATA change form low to high
	delay_us(num,4);
	SetIIC_SCL(num,1); 
	SetIIC_SDA(num,1);//发送I2C总线结束信号
	delay_us(num,4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
unsigned char IIC_Wait_Ack(int num)
{
	unsigned char ucErrTime=0;

	SDA_IN(num);      //SDA设置为输入  
	SetIIC_SDA(num,1);
	delay_us(num,1);   
	SetIIC_SCL(num,1);
	delay_us(num,1);
	while(ReadIIC_SDA(num))
	{
		ucErrTime++;
		if(ucErrTime > 250)
		{
			IIC_Stop(num);
			DBG_Print(LEVEL0,"%s","<IIC_Wait_Ack>Time Out.\r\n");
			return 1;
		}
	}
	SetIIC_SCL(num,0);//时钟输出0 	   
	return 0;
} 
//产生ACK应答
void IIC_Ack(int num)
{
	SetIIC_SCL(num,0);
	SDA_OUT(num);
	SetIIC_SDA(num,0);
	delay_us(num,2);
	SetIIC_SCL(num,1);
	delay_us(num,2);
	SetIIC_SCL(num,0);
}
//不产生ACK应答    
void IIC_NAck(int num)
{
	SetIIC_SCL(num,0);
	SDA_OUT(num);
	SetIIC_SDA(num,1);
	delay_us(num,2);
	SetIIC_SCL(num,1);
	delay_us(num,2);
	SetIIC_SCL(num,0);
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(int num,unsigned char txd)
{                        
	unsigned char t;

	SDA_OUT(num); 	    
	SetIIC_SCL(num,0);//拉低时钟开始数据传输
	delay_us(num,2);
	for(t = 0; t < 8; t++)
	{              
		//IIC_SDA=(txd&0x80)>>7;
		if((txd & 0x80) >> 7)
			SetIIC_SDA(num,1);
		else
			SetIIC_SDA(num,0);
		txd <<= 1; 	  
		delay_us(num,2);   //对TEA5767这三个延时都是必须的
		SetIIC_SCL(num,1);
		delay_us(num,2); 
		SetIIC_SCL(num,0);	
		delay_us(num,2);
	}
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
unsigned char IIC_Read_Byte(int num,unsigned char ack)
{
	unsigned char i;
	unsigned char receive = 0;

	SDA_IN(num);//SDA设置为输入
	for(i = 0; i < 8; i++)
	{
		SetIIC_SCL(num,0); 
		delay_us(num,2);
		SetIIC_SCL(num,1);
		receive <<= 1;
		if(ReadIIC_SDA(num))
		{
			receive++;
		}
		delay_us(num,1); 
	}					 
	if (!ack)
		IIC_NAck(num);//发送nACK
	else
		IIC_Ack(num); //发送ACK   
	return receive;
}

unsigned int IIC_Read(int num,unsigned char device_addr,unsigned int reg_addr,unsigned int uiWantToReadBytes,void *pOut,unsigned int outbuflen)
{
	unsigned int i = 0;
	unsigned int read_bytes = 0;
	unsigned char *ptr = (unsigned char *)pOut;

	if ((pOut == 0) || (outbuflen == 0) || (uiWantToReadBytes == 0)) return 0;

	read_bytes = (uiWantToReadBytes > outbuflen) ? outbuflen : uiWantToReadBytes;

	IIC_Start(num);
	IIC_Send_Byte(num,device_addr | 0x00);
	IIC_Wait_Ack(num);



	//发送寄存器地址
	if (reg_addr <= 0xFF)
	{
		IIC_Send_Byte(num,reg_addr);
		IIC_Wait_Ack(num);
	}
	else if (reg_addr <= 0xFFFF)
	{
		IIC_Send_Byte(num,reg_addr);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 8);
		IIC_Wait_Ack(num);
	}
	else if (reg_addr <= 0xFFFFFF)
	{
		IIC_Send_Byte(num,reg_addr);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 8);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 16);
		IIC_Wait_Ack(num);
	}
	else
	{
		IIC_Send_Byte(num,reg_addr);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 8);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 16);
		IIC_Wait_Ack(num);
		IIC_Send_Byte(num,reg_addr >> 24);
		IIC_Wait_Ack(num);
	}

	//发送读指令
	IIC_Start(num);
	IIC_Send_Byte(num,device_addr | 0x01);
	IIC_Wait_Ack(num);


	for (i = 0; i < read_bytes; i++)
	{
		if (i == (read_bytes - 1))  	//最后一个字节 需要发送不应答
		{
			*(ptr + i) = IIC_Read_Byte(num,0);
		}
		else
		{
			*(ptr + i) = IIC_Read_Byte(num,1);
		}
	}

	IIC_Stop(num);
	return read_bytes;
}


unsigned int IIC_Write(int num,unsigned char device_addr,unsigned char reg_addr,void *pdat,unsigned int len)
{
	unsigned int i = 0;
	unsigned char *ptr = (unsigned char *)pdat;

	if ((pdat == 0) || (len == 0)) return 0;

	IIC_Start(num);
	IIC_Send_Byte(num,device_addr | 0x00);
	IIC_Wait_Ack(num);

	IIC_Send_Byte(num,reg_addr);
	IIC_Wait_Ack(num);

	for (i = 0; i < len; i++)
	{
		IIC_Send_Byte(num,ptr[i]);
		IIC_Wait_Ack(num);
	}
	
	IIC_Stop(num);
	return len;
}


