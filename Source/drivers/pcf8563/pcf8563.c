#include "pcf8563.h"


#define PCF8563_IIC_INDEX   0
#define PCF8563_DEVICE_ADDRESS   0x0A2


typedef struct tagPCF8563_RTC
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned char week;
}PCF8563_RTC;

PCF8563_RTC stPCF8563_RTC = {0};


void pcf8563_write_reg(unsigned char reg_addr,unsigned char dat)
{
	IIC_Write(PCF8563_IIC_INDEX,PCF8563_DEVICE_ADDRESS,reg_addr,&dat,1);
}


void pcf8563_init(void)
{
	pcf8563_write_reg(1,0);

	pcf8563_write_reg(0x0E,0);

	//时钟输出 1HZ
	pcf8563_write_reg(0x0D,0x83);

	pcf8563_write_reg(0,0);	//enable source clock
}

unsigned char bcd_to_dec(unsigned char bcd)
{
	unsigned char hi = 0;
	unsigned char low = 0;

	hi = (bcd & 0xF0) >> 4;
	low = bcd & 0x0F;

	return (hi * 10 + low);
}

unsigned char dec_to_bcd(unsigned char dec)
{
	unsigned char hi = 0;
	unsigned char low = 0;

	hi = dec / 10;
	low= dec % 10;

	return ((hi << 4) + low);
}

void pcf8563_read_rtc(void)
{
	unsigned char aucTemp[7] = {0};

	IIC_Read(PCF8563_IIC_INDEX,PCF8563_DEVICE_ADDRESS,0x02,7,aucTemp,7);

	stPCF8563_RTC.year = bcd_to_dec(aucTemp[6]);
	stPCF8563_RTC.month = bcd_to_dec(aucTemp[5] & 0x1F);
	stPCF8563_RTC.day = bcd_to_dec(aucTemp[3] & 0x3F);
	stPCF8563_RTC.hour = bcd_to_dec(aucTemp[2] & 0x3F);
	stPCF8563_RTC.min = bcd_to_dec(aucTemp[1] & 0x7F);
	stPCF8563_RTC.sec = bcd_to_dec(aucTemp[0] & 0x7F);
	stPCF8563_RTC.week = bcd_to_dec(aucTemp[4] & 0x07);
}


void pcf8563_set_rtc(unsigned int year,unsigned char month,unsigned char day,
							unsigned char hour,unsigned char min,unsigned char sec)
{
	pcf8563_write_reg(0,0x20);	//disable source clock
	//秒
	pcf8563_write_reg(0x02,dec_to_bcd(sec));
	//分
	pcf8563_write_reg(0x03,dec_to_bcd(min));
	//时
	pcf8563_write_reg(0x04,dec_to_bcd(hour));
	//天
	pcf8563_write_reg(0x05,dec_to_bcd(day)); 
	//month
	pcf8563_write_reg(0x07,dec_to_bcd(month));
	//year
	pcf8563_write_reg(0x08,dec_to_bcd(year - 2000));
	pcf8563_write_reg(0,0);	//enable source clock
}

unsigned char pcf8563_get_year(void)
{
	return stPCF8563_RTC.year;
}


unsigned char pcf8563_get_month(void)
{
	return stPCF8563_RTC.month;
}

unsigned char pcf8563_get_day(void)
{
	return stPCF8563_RTC.day;
}

unsigned char pcf8563_get_hour(void)
{
	return stPCF8563_RTC.hour;
}
unsigned char pcf8563_get_min(void)
{
	return stPCF8563_RTC.min;
}

unsigned char pcf8563_get_sec(void)
{
	return stPCF8563_RTC.sec;
}

