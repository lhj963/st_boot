#include "adc.h"


unsigned int get_adc_rcc(ADC_Type *adc)
{
	if (adc == ADC0)
	{
		return PCC_ADC0_INDEX;
	}
	else if (adc == ADC1)
	{
		return PCC_ADC1_INDEX;
	}
	return PCC_ADC0_INDEX;
}

void _adc_init(ADC_Type *adc,unsigned int rcc,PORT_Type *port,unsigned char pin_idx)
{
	unsigned int adc_rcc = get_adc_rcc(adc);

	//ADC硬件上开关接口配置
	PCC->PCCn[rcc] |= PCC_PCCn_CGC_MASK; //使能PTA端口时钟
	port->PCR[pin_idx] = PORT_PCR_MUX(0) | (1 << 6); //MUX = ALT0,PTx端口复用 ADC 增强驱动

	PCC->PCCn[adc_rcc] &=~ PCC_PCCn_CGC_MASK;  //禁掉ADC时钟
	PCC->PCCn[adc_rcc] |= PCC_PCCn_PCS(1);     //PCS=1: 时钟源SOSCDIV2 = 8MHZ
	PCC->PCCn[adc_rcc] |= PCC_PCCn_CGC_MASK;   //使能ADC时钟

	adc->SC1[0] =0x00001F;    // ADCH=1F: 输入通道选择为保留
                               // AIEN=0: 禁用转换完成中断
	adc->CFG1 = 0x000000004;  //ADICLK=0: 输入时钟选择ALTCLK1=SOSCDIV2
                               // ADIV=0: Prescaler=1  分频/1 时钟速率为输入时钟
                               // MODE=1: 转换模式选择为12-bit
	adc->CFG2 = 0x00000000C;  //SMPLTS=12(default):采样时间12 ADC时钟周期 
	adc->SC2 = 0x00000000;    //ADTRG=0: 转换触发选择为软件触发
                               //ACFE,ACFGT,ACREN=0: 比较函数禁用
                               // DMAEN=0: DMA禁用
                               // REFSEL=0: 电压参考引脚选择为 VREFH, VREEFL
	adc->SC3 = 0x00000000 | (1 << 7);    //CAL=0: 不启动校准程序 当CAL=1时，会启动校准程序
                               //ADCO=0: 不连续转换，选择一次转换
                               //AVGE,AVGS=0: 禁用硬件平均功能
}

void adc_init(ADC_Type *adc,unsigned int rcc,PORT_Type *port,unsigned char pin_idx)
{
	_adc_init(adc,rcc,port,pin_idx);
}

typedef struct tagADCError
{
	//AD转换出错标记
	unsigned char read_ad_err_flag;
	unsigned char ad_no;		//AD号
	unsigned char channel;		//AD通道
}ADCError;

ADCError stADCError = {0};

unsigned char is_adc_error(void)
{
	return stADCError.read_ad_err_flag;
}

void clr_adc_error_flag(void)
{
	stADCError.read_ad_err_flag = 0;
}

unsigned char get_adc_error_ad_no(void)
{
	return stADCError.ad_no;
}

unsigned char get_adc_error_channel(void)
{
	return stADCError.channel;
}


unsigned int _adc_read_val(ADC_Type *adc,unsigned char channel)
{
	unsigned int adc_val = 0;
	unsigned int cnt = 0;

	if (channel >= ADC_SC1_COUNT) return 0;

	/* For SW trigger mode, SC1[channel] is used */
	adc->SC1[0] &= ~ADC_SC1_ADCH_MASK; 	 //清除之前的ADCH位
	adc->SC1[0] = ADC_SC1_ADCH(channel);	 //开始转换

	while (((adc->SC1[0] & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT) == 0)
	{
		cnt++;
		if (cnt >= 1000)
		{
			stADCError.read_ad_err_flag = 1;
			if (adc == ADC0)
			{
				stADCError.ad_no = 0;
			}
			else if (adc == ADC1)
			{
				stADCError.ad_no = 1;
			}
			stADCError.channel = channel;
			return 0;
		}
	}

	adc_val = adc->R[0];
	return adc_val;
}

unsigned int adc_read_val(ADC_Type *adc,unsigned char channel)
{
	return _adc_read_val(adc,channel);
}

void adc0_init(unsigned int rcc,PORT_Type * port,unsigned char pin_idx)
{
	_adc_init(ADC0, rcc, port, pin_idx);
}

void adc1_init(unsigned int rcc,PORT_Type * port,unsigned char pin_idx)
{
	_adc_init(ADC1, rcc, port, pin_idx);
}


unsigned int adc0_read_val(unsigned char channel)
{
	return _adc_read_val(ADC0,channel);
}

unsigned int adc1_read_val(unsigned char channel)
{
	return _adc_read_val(ADC1,channel);
}












