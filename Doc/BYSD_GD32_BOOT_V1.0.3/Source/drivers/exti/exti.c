#include "exti.h"

typedef struct tagPIN_HANDLER
{
	unsigned char pin_idx;
	void (*handler)(void);
	struct tagPIN_HANDLER *pNext;
}PIN_HANDLER;


typedef struct tagEXTI_PORT_NUM
{
	PORT_Type *port;
	unsigned int irq_num;

	unsigned char handler_cnt;	//在该PORT上安装了多少个外部中断
	PIN_HANDLER *ph;

}EXTI_PORT_NUM;

EXTI_PORT_NUM s_stEXTI_PORT_NUM[] = 
{
	{PORTA,PORTA_IRQn,0,0},
	{PORTB,PORTB_IRQn,0,0},
	{PORTC,PORTC_IRQn,0,0},
	{PORTD,PORTD_IRQn,0,0},
	{PORTE,PORTE_IRQn,0,0}
};


PIN_HANDLER s_astPIN_HANDLER[MAX_EXTI_CNT] = {0};


static unsigned int get_irq_num(PORT_Type *port)
{
	unsigned char i = 0;
	unsigned char cnt = sizeof(s_stEXTI_PORT_NUM) / sizeof(s_stEXTI_PORT_NUM[0]);

	for (i = 0; i < cnt; i++)
	{
		if (port == s_stEXTI_PORT_NUM[i].port)
		{
			return s_stEXTI_PORT_NUM[i].irq_num;
		}
	}
	return 0;
}

PIN_HANDLER *get_free_ph(void)
{
	unsigned int i = 0;

	for (i = 0; i < MAX_EXTI_CNT; i++)
	{
		if (s_astPIN_HANDLER[i].handler == 0)
		{
			return (s_astPIN_HANDLER + i);
		}
	}
	return 0;
}

void set_exti_handler(PORT_Type *port,unsigned char pin_idx,void (*handler)(void))
{
	unsigned char i = 0;
	unsigned char cnt = sizeof(s_stEXTI_PORT_NUM) / sizeof(s_stEXTI_PORT_NUM[0]);

	for (i = 0; i < cnt; i++)
	{
		if (port == s_stEXTI_PORT_NUM[i].port)
		{
			PIN_HANDLER *ptemp = 0;
			PIN_HANDLER *pptemp = 0;
			PIN_HANDLER *plast = 0;

			//查找该引脚是否已经注册过中断handler
			pptemp = s_stEXTI_PORT_NUM[i].ph;
			while (pptemp)
			{			
				//相同的引脚 则更新handler
				if (pptemp->pin_idx == pin_idx)
				{
					pptemp->handler = handler;
					return ;
				}
				pptemp = pptemp->pNext;
			}

			ptemp = get_free_ph();
			if (ptemp == 0)
			{
				break;
			}
			s_stEXTI_PORT_NUM[i].handler_cnt++;

			ptemp->pNext = 0;
			ptemp->handler = handler;
			ptemp->pin_idx = pin_idx;

			if (s_stEXTI_PORT_NUM[i].ph == 0)
			{
				s_stEXTI_PORT_NUM[i].ph = ptemp;
			}
			else
			{
				pptemp = s_stEXTI_PORT_NUM[i].ph;

				//找链表尾
				while (pptemp)
				{
					plast = pptemp;
					pptemp = pptemp->pNext;
				}
				plast->pNext = ptemp;
			}
		}
	}
}

void exti_init(unsigned int rcc,GPIO_Type *gpio,
				PORT_Type *port,unsigned char pin_idx,void (*exti_handler)(void)) 
{
	unsigned int irq_num = get_irq_num(port);

	set_exti_handler(port,pin_idx,exti_handler);

	//端口配置
	PCC->PCCn[rcc] |= PCC_PCCn_CGC_MASK;	//使能PTx端口时钟
	gpio->PDDR &= ~(1 << pin_idx);			//配置pin_idx为输入端口
	port->PCR[pin_idx] = 0x000B0100;		//配置port pin为GPIO，边沿触发中断

    //外部中断配置
	S32_NVIC->ICPR[1] = 1 << (irq_num % 32);
	S32_NVIC->ISER[(uint32_t)(irq_num) >> 5U] = (uint32_t)(1UL << ((uint32_t)(irq_num) & (uint32_t)0x1FU));
	S32_NVIC->IP[irq_num] = 9;      //中断优先级配置为9（0-15）
}

void port_irq_handler(PORT_Type *port,unsigned char channel)
{
	if (s_stEXTI_PORT_NUM[channel].handler_cnt)
	{
		PIN_HANDLER *ptemp = 0;

		ptemp = s_stEXTI_PORT_NUM[channel].ph;

		while (ptemp)
		{
			if (port->ISFR & (1 << (ptemp->pin_idx)))
			{
				ptemp->handler();
				port->ISFR |= (1 << (ptemp->pin_idx));		//清除中断标志
			}
			ptemp = ptemp->pNext;
		}
	}

}


/*端口PTA外部中断服务函数*/
void PORTA_IRQHandler(void)
{
	port_irq_handler(PORTA,0);
}

/*端口PTB外部中断服务函数*/
void PORTB_IRQHandler(void)
{
	port_irq_handler(PORTB,1);
}

/*端口PTC外部中断服务函数*/
void PORTC_IRQHandler(void)
{
	port_irq_handler(PORTC,2);
}

/*端口PTD外部中断服务函数*/
void PORTD_IRQHandler(void)
{
	port_irq_handler(PORTD,3);
}

/*端口PTE外部中断服务函数*/
void PORTE_IRQHandler(void)
{
	port_irq_handler(PORTE,4);
}







