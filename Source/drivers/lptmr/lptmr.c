#include "lptmr.h"

//将x的第start_bit到第end_bit位设置成val值
//例如 将x的第3到5位设置成7
#if 1
void set_bits(unsigned int *x,unsigned char start_bit,
					unsigned char end_bit,unsigned int val) 
{
	unsigned char cnt = end_bit - start_bit + 1;
	unsigned int mask = 0;
	unsigned char i = 0;
	unsigned int dat = *x;

	for (i = start_bit; i <= end_bit; i++)
	{
		mask |= (1 << i);
	}
	if (val > (mask >> start_bit))
	{
		val = mask >> start_bit;
	}

	DBG_Print(0,"start_bit:%d end_bit:%d mask:%08X val:%08X\r\n",
	start_bit,end_bit,mask,val);

	dat &= ~mask;					//先清除第start_bit到第end_bit之间的数
	dat |= (val << start_bit);	//再赋值
	*x = dat;
}
#endif


lptmr_handler_func plptmr_handler = 0;

void LPTMR0_IRQHandler(void)
{
	if (plptmr_handler) plptmr_handler();
	LPTMR0->CSR |= (1 << 7);		//清除标志位
}



void lptmr_init(unsigned int us,lptmr_handler_func pfunc)
{
	unsigned int irqNumber = 0;

	plptmr_handler = pfunc;
	PCC->PCCn[PCC_LPTMR0_INDEX] &= ~PCC_PCCn_CGC_MASK;

	PCC->PCCn[PCC_LPTMR0_INDEX] |= PCC_PCCn_PCS(3);		//时钟源选择OSC 12M
	//开启时钟
	PCC->PCCn[PCC_LPTMR0_INDEX] |= PCC_PCCn_CGC_MASK;
	
	/* Enable interrupt */
	irqNumber = (unsigned int)LPTMR0_IRQn;
	S32_NVIC->ISER[(uint32_t)(irqNumber) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irqNumber) & (uint32_t)0x1FU));


	{
		LPTMR_Type *base = LPTMR0;
		/* First, disable the module so we can write the registers */
		uint32_t tmp = base->CSR;
		tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
		tmp |= LPTMR_CSR_TEN(0u);
		base->CSR = tmp;
	
		base->CSR = LPTMR_CSR_TEN(0u) | \
					LPTMR_CSR_TMS(0u) | \
					LPTMR_CSR_TFC(0u) | \
					LPTMR_CSR_TPP(0u) | \
					LPTMR_CSR_TPS(0u) | \
					LPTMR_CSR_TIE(0u) | \
					LPTMR_CSR_TCF(0u) | \
					LPTMR_CSR_TDRE(0u);
	
		base->PSR = LPTMR_PSR_PCS(0u) | \
					LPTMR_PSR_PBYP(0u) | \
					LPTMR_PSR_PRESCALE(0u);
	
		base->CMR = LPTMR_CMR_COMPARE(0u);
	}


	//开中断
	/**
	Timer Interrupt Enable
	When TIE is set, the LPTMR Interrupt is generated whenever TCF is also set.
	0b - Timer interrupt disabled.
	1b - Timer interrupt enabled.
	*/
	set_bits(&(LPTMR0->CSR),6,7,3);


	/*
	Timer Mode Select
	Configures the mode of the LPTMR. 
	TMS must be altered only when the LPTMR is disabled.
	0b - Time Counter mode.
	1b - Pulse Counter mode.
	*/
	set_bits(&(LPTMR0->CSR),1,1,0);

	/**
	Prescale Value
	Configures the size of the Prescaler in Time Counter mode or width of the glitch filter in Pulse Counter
	mode. The width of the glitch filter can vary by 1 cycle due to synchronization of the pulse counter input.
	PRESCALE must be altered only when the LPTMR is disabled.
	0000b - Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
	0001b - Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after
	2 rising clock edges.
	0010b - Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after
	4 rising clock edges.
	0011b - Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin
	after 8 rising clock edges.
	0100b - Prescaler divides the prescaler clock by 32; glitch filter recognizes change on input pin
	after 16 rising clock edges.
	0101b - Prescaler divides the prescaler clock by 64; glitch filter recognizes change on input pin
	after 32 rising clock edges.
	0110b - Prescaler divides the prescaler clock by 128; glitch filter recognizes change on input pin
	after 64 rising clock edges.
	0111b - Prescaler divides the prescaler clock by 256; glitch filter recognizes change on input pin
	after 128 rising clock edges.
	1000b - Prescaler divides the prescaler clock by 512; glitch filter recognizes change on input pin
	after 256 rising clock edges.
	1001b - Prescaler divides the prescaler clock by 1024; glitch filter recognizes change on input pin
	after 512 rising clock edges.
	1010b - Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin
	after 1024 rising clock edges.
	1011b - Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input pin
	after 2048 rising clock edges.
	1100b - Prescaler divides the prescaler clock by 8192; glitch filter recognizes change on input pin
	after 4096 rising clock edges.
	1101b - Prescaler divides the prescaler clock by 16,384; glitch filter recognizes change on input pin
	after 8192 rising clock edges.
	1110b - Prescaler divides the prescaler clock by 32,768; glitch filter recognizes change on input pin
	after 16,384 rising clock edges.
	1111b - Prescaler divides the prescaler clock by 65,536; glitch filter recognizes change on input pin
	after 32,768 rising clock edges.
	*/
	set_bits(&(LPTMR0->PSR),3,6,0);


	set_bits(&(LPTMR0->CMR),0,15,6000);


	//启动定时器
	/**
	Timer Enable
	When TEN is clear, it resets the LPTMR internal logic, including the CNR and TCF. 
	When TEN is set, the LPTMR is enabled. 
	While writing 1 to this field, CSR[5:1] must not be altered.
	0b - LPTMR is disabled and internal logic is reset.
	1b - LPTMR is enabled.
	*/
	//set_bits(&(LPTMR0->CSR),0,0,1);


{	
		uint32_t tmp = LPTMR0->CSR;
		DBG_Print(0,"CSR:%08X\r\n",tmp);

		/* Clear the affected bit-field and write '0' to the w1c bits to avoid side-effects */
		tmp &= ~(LPTMR_CSR_TEN_MASK | LPTMR_CSR_TCF_MASK);
		tmp |= LPTMR_CSR_TEN(1u);
		LPTMR0->CSR = tmp;

}
    

	DBG_Print(0,"LPTMR0->CSR:%08X LPTMR0->PSR:%08X LPTMR0->CMR:%08X\r\n",
	LPTMR0->CSR,LPTMR0->PSR,LPTMR0->CMR);
}







