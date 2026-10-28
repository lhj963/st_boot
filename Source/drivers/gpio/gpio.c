#include "gpio.h"


void __gpio_init(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,
					unsigned char pin_idx,char is_input_mode,
					char is_en_pull_up_down,char is_pullup)
{
	char is_en_pull = is_en_pull_up_down ? 1 : 0;
	char is_pull_up = is_pullup ? 1 : 0;

	if ((rcc == 0) || (gpio == 0) || (port == 0)) return ;

	/* Enable clock to PORT */
    PCC->PCCn[rcc] |= PCC_PCCn_CGC_MASK;
	
	if (is_input_mode)
	{
		/* Set pin as an input pin */
		gpio->PDDR &= (~(1 << pin_idx));
	}
	else
	{
		/* Set pin as an output pin */
		gpio->PDDR |= (1 << pin_idx);
	}

	/* Configure port pin as a GPIO function */
	if (is_en_pull)
	{
		port->PCR[pin_idx]	= 0x100u | (is_en_pull << 1) | is_pull_up;
	}
	else
	{
		port->PCR[pin_idx]	= 0x100u;
	}
}


void _gpio_af(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,unsigned char func_id)
{
	PCC->PCCn[rcc] |= PCC_PCCn_CGC_MASK; 					//使能PTn端口时钟
	port->PCR[pin_idx] |= PORT_PCR_MUX(func_id) | (1 << 6); // Port C8: MUX = ALT2,UART1 RX PTC2复用为RX 增强驱动
}

void _gpio_init(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode)
{
	__gpio_init(rcc,gpio,port,pin_idx,is_input_mode,0,0);
}

void _gpio_init_pull_down(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode)
{
	__gpio_init(rcc,gpio,port,pin_idx,is_input_mode,1,0);
}

void _gpio_init_pull_up(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode)
{
	__gpio_init(rcc,gpio,port,pin_idx,is_input_mode,1,1);
}


void pin_high(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx)
{
	if ((rcc == 0) || (gpio == 0) || (port == 0)) return ;

	gpio->PDOR |= (1 << pin_idx);
}

void pin_low(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx)
{
	if ((rcc == 0) || (gpio == 0) || (port == 0)) return ;

	gpio->PDOR &= (~(1 << pin_idx));
}


char pin_read_in(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx)
{
	if ((rcc == 0) || (gpio == 0) || (port == 0)) return 0;

	if (gpio->PDIR & (1 << pin_idx))
	{
		return 1;
	}
	return 0;
}

