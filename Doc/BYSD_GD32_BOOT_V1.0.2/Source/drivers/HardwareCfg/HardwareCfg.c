#include "HardwareCfg.h"


unsigned int s_ms = 0;

void delay_dec(void)
{
	if (s_ms) s_ms--;
}

void delayms_by_timer(unsigned int ms)
{
	s_ms = ms;
	while (s_ms);
}

void delayms1(unsigned long t)
{
	volatile unsigned long i = 0;
	volatile unsigned long j = 0;

	for (i = 0; i < 80000; i++)
	{
		for (j = 0; j < 10; j++);
	}
}


void delayus(unsigned int t)
{
	volatile unsigned int i = 0;
	volatile unsigned int j = 0;

	for (j = 0; j < 6; j++)
	{
		for (i = 0; i < t; i++);
	}
}

unsigned int get_cpu_flash_size(void)
{
    unsigned int Stm32_Flash_Size = 0;

    Stm32_Flash_Size = *(u16*)(0x1FFFF7E0);
    return Stm32_Flash_Size;
}

void _gpio_init(uint32_t rcc,GPIO_TypeDef* port,uint16_t pin,GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  gpio_init;

	if ((rcc == 0) || (port == 0) || (pin == 0))
	{
		return ;
	}
	RCC_APB2PeriphClockCmd(rcc, ENABLE);

	gpio_init.GPIO_Pin   = pin;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode  = mode;
	GPIO_Init(port, &gpio_init);
}

void pin_low(uint32_t rcc,GPIO_TypeDef* port,uint16_t pin)
{
	if (rcc && port && pin)
	{
		GPIO_ResetBits(port, pin);
	}
}

void pin_high(uint32_t rcc,GPIO_TypeDef* port,uint16_t pin)
{
	if (rcc && port && pin)
	{
		GPIO_SetBits(port, pin);
	}
}

unsigned int dbg_write(void *buf,unsigned int len)
{
	if ((buf == 0) || (len == 0))
	{
		return 0;
	}

	SEGGER_RTT_Write(0,buf,len);

	delayms1(100);
	return len;
}

unsigned int dbg_read(void *buf,unsigned int ulBufSize,unsigned int ulTimeoutMs)
{
	return 0;
}

void gpio_init(void)
{
	//_gpio_init(LED0_RCC,LED0_PORT,LED0_PIN,LED0_PIN_MODE);
	//pin_high(LED0_RCC,LED0_PORT,LED0_PIN);

	_gpio_init(GPRS_PWR_RCC,GPRS_PWR_PORT,GPRS_PWR_PIN,GPRS_PWR_PIN_MODE);
	pin_high(GPRS_PWR_RCC,GPRS_PWR_PORT,GPRS_PWR_PIN);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);
}

void bsp_init(void)
{
	gpio_init();
	SEGGER_RTT_Init();
	//调试串口
	//usart1_init(115200,0);
	DBG_Init(0,0,0,0,dbg_write,dbg_read);
	//预留备用串口
	//DBG_Init(1,usart2_init,115200,0,usart2_send_data,usart2_read);

	DBG_Print(LEVEL0,"*********************************************************************\r\n"
				"*BOOT Version:%s Compile @ %s %s.\r\n"
				"*CPU:GD32F305 FLASH:%dKB\r\n"
				"*Space Size:0x%08X ~ 0x%08X.\r\n"
				"*2022 mu wei 4 Corporation.\r\n"
				"*********************************************************************\r\n",
				BOOT_VERSION,__TIME__,__DATE__,
				get_cpu_flash_size(),
				BOOT_START_ADDR,BOOT_END_ADDR);

	//定时1ms
	//SysTick_Config(8000);

}

void SysTick_Handler(void)
{

}


