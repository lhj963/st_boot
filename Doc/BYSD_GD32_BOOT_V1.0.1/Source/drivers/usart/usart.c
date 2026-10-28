#include "usart.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void usart0_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)((uint32_t)1 << (LPUART0_RxTx_IRQn % 32));  /* UART0: clr any pending IRQ*/
	S32_NVIC->ISER[(uint32_t)(LPUART0_RxTx_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(LPUART0_RxTx_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[LPUART0_RxTx_IRQn] = 0x7;              /* UART0: priority 7 of 0-15*/
}

void usart1_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)((uint32_t)1 << (LPUART1_RxTx_IRQn % 32));  /* UART0: clr any pending IRQ*/
	S32_NVIC->ISER[(uint32_t)(LPUART1_RxTx_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(LPUART1_RxTx_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[LPUART1_RxTx_IRQn] = 0x7;              /* UART0: priority 7 of 0-15*/
}

void usart2_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)((uint32_t)1 << (LPUART2_RxTx_IRQn % 32));  /* UART2: clr any pending IRQ*/
	S32_NVIC->ISER[(uint32_t)(LPUART2_RxTx_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(LPUART2_RxTx_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[LPUART2_RxTx_IRQn] = 0x7;              /* UART2: priority 7 of 0-15*/
}

void usart0_port_init(void)
{
	PCC->PCCn[PCC_PORTB_INDEX ] |= PCC_PCCn_CGC_MASK; //使能PTB端口时钟
	PORTB->PCR[0] |= PORT_PCR_MUX(2) | (1 << 6); // Port B0: MUX = ALT2,UART0 RX PTB0复用为RX 增强驱动
	PORTB->PCR[1] |= PORT_PCR_MUX(2) | (1 << 6); // Port B1: MUX = ALT2,UART0 TX PTB1复用为TX 增强驱动
#if 0
#if 1
	PCC->PCCn[PCC_PORTC_INDEX ] |= PCC_PCCn_CGC_MASK; //使能PTC端口时钟
	PORTC->PCR[2] |= PORT_PCR_MUX(4) | (1 << 6); // Port C2: MUX = ALT4,UART0 RX PTC2复用为RX 增强驱动
	PORTC->PCR[3] |= PORT_PCR_MUX(4) | (1 << 6); // Port C3: MUX = ALT4,UART0 TX PTC3复用为TX 增强驱动
#else
	PCC->PCCn[PCC_PORTA_INDEX ] |= PCC_PCCn_CGC_MASK; //使能PTA端口时钟
	PORTA->PCR[2] |= PORT_PCR_MUX(6) | (1 << 6); // Port C2: MUX = ALT4,UART0 RX PTA2复用为RX 增强驱动
	PORTA->PCR[3] |= PORT_PCR_MUX(6) | (1 << 6); // Port C3: MUX = ALT4,UART0 TX PTA3复用为TX 增强驱动
#endif
#endif
}

void usart1_port_init(void)
{
#if 0
	PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK; //使能PTC端口时钟
	PORTC->PCR[8] |= PORT_PCR_MUX(2) | (1 << 6); // Port C8: MUX = ALT2,UART1 RX PTC2复用为RX 增强驱动
	PORTC->PCR[9] |= PORT_PCR_MUX(2) | (1 << 6); // Port C9: MUX = ALT2,UART1 TX PTC3复用为TX 增强驱动
#else
	PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK; //使能PTD端口时钟
	PORTD->PCR[13] |= PORT_PCR_MUX(3) | (1 << 6); // Port D13: MUX = ALT3,UART1 RX PTD13复用为RX 增强驱动
	PORTD->PCR[14] |= PORT_PCR_MUX(3) | (1 << 6); // Port D14: MUX = ALT3,UART1 TX PTD14复用为TX 增强驱动
#endif
}

void usart2_port_init(void)
{
	PCC->PCCn[PCC_PORTD_INDEX ] |= PCC_PCCn_CGC_MASK; //使能PTD端口时钟
	PCC->PCCn[PCC_PORTE_INDEX ] |= PCC_PCCn_CGC_MASK; //使能PTE端口时钟

	PORTD->PCR[17] |= PORT_PCR_MUX(3) | (1 << 6); // Port D17: MUX = ALT3,UART2 RX PTD17复用为RX 	增强驱动
	PORTE->PCR[12] |= PORT_PCR_MUX(3) | (1 << 6); // Port E12: MUX = ALT3,UART2 TX PTE12复用为TX  增强驱动
}

void _lpuart_init(LPUART_Type *lpuart,unsigned long bps,char iParity)
{
	if (bps == 9600)
	{
		//lpuart->BAUD = 0x0B000068;	//12M

		lpuart->BAUD = 0x0F000034;  //配置波特率为9600，1停止位
									 // SBR=52 (0x34): 波特率模数除数 = 8M/9600/16 = ~52
									 // OSR=15: 采样率 = 15+1=16
									 // SBNS=0: 1个停止位
									 // BOTHEDGE=0: 接收端使用波特率时钟上升沿采样输入数据
									 // M10=0: 接收机和发射机使用7位到9位的数据字符
									 // RESYNCDIS=0: 支持在接收数据字期间重新同步
									 // LBKDIE, RXEDGIE=0: 禁用LIN中断，RX收入边缘中断
	}
	else
	{
		//lpuart->BAUD = (3 << 24) | (1 << 17) | 0x1A;	//12M
		lpuart->BAUD = 0x0600000A;  //配置波特率为115200，1停止位
									 // SBR=11 (0x0B): 波特率模数除数 = 8M/115200/7 = ~10
									 // OSR=6: 采样率 = 6+1=7
									 // SBNS=0: 1个停止位
									 // BOTHEDGE=0: 接收端使用波特率时钟上升沿采样输入数据
									 // M10=0: 接收机和发射机使用7位到9位的数据字符
									 // RESYNCDIS=0: 支持在接收数据字期间重新同步
									 // LBKDIE, RXEDGIE=0: 禁用LIN中断，RX收入边缘中断
	}

	lpuart->STAT |= (1 << 23);	//清发送标志  0表示tx buff full  1表示tx buff empty
	lpuart->FIFO |= (1 << 23);

	lpuart->CTRL=0x000C0000 | (1<<21); 
								 // RE=1，TE=1: 使能接收及发送
                          	     // PE=0: 无奇偶校验
                           		 // M7,M,R8T9,R9T8=0: 8个数据位
                           		 // DOZEEN=0: 睡眠模式下LPUART正常启用
                           		 // ORIE,NEIE,FEIE,PEIE,TIE,TCIE,ILIE,MA1IE,MA2IE=0，RIE=1: 接收中断
                           	     // TXINV=0: 传输数据不是反向的
                           		 // IDLCFG=0: 1个空闲字符
                           		 // ILT=0: 空闲字符位计数在开始位之后开始
}

#if __USE_LFOS__
static LFOS_SEM usart_sem_tx[USART_CNT] = {0};
static LFOS_SEM usart_sem_rx[USART_CNT] = {0};
static char usart_sem_init_flag[USART_CNT] = {0};

void _usart_sem_init(unsigned char usart_idx)
{
	if (usart_sem_init_flag[usart_idx] == 0)
	{
		usart_sem_init_flag[usart_idx] = 1;

		lfos_create_sem(&usart_sem_tx[usart_idx],"tx",1);
		lfos_create_sem(&usart_sem_rx[usart_idx],"rx",0);
	}
}

void _usart_tx_sem_pend(unsigned char usart_idx,unsigned int timeout)
{
	lfos_sem_pend(&usart_sem_tx[usart_idx],timeout);
}

void _usart_rx_sem_pend(unsigned char usart_idx,unsigned int timeout)
{
	lfos_sem_pend(&usart_sem_rx[usart_idx],timeout);
}

void _usart_tx_sem_post(unsigned char usart_idx)
{
	lfos_sem_post(&usart_sem_tx[usart_idx]);
}

void _usart_rx_sem_post(unsigned char usart_idx)
{
	lfos_sem_post(&usart_sem_rx[usart_idx]);
}


#endif

//波特率: bps , 1停止位, 8个数据位, 无奇偶校验
void usart0_init(unsigned long bps,char iParity)
{
	usart0_nvic_init_irqs();
	usart0_port_init();
#if __USE_LFOS__
	_usart_sem_init(0);
#endif
	PCC->PCCn[PCC_LPUART0_INDEX] &= ~PCC_PCCn_CGC_MASK;    //禁LPUART0时钟
	PCC->PCCn[PCC_LPUART0_INDEX] |= PCC_PCCn_PCS(1)    //选择时钟 Clock Src= 1 (SOSCDIV2_CLK)
                               	 | PCC_PCCn_CGC_MASK;   //使能LPUART0时钟
	_lpuart_init(LPUART0,bps,iParity);
}

//波特率: bps , 1停止位, 8个数据位, 无奇偶校验
void usart1_init(unsigned long bps,char iParity)
{
	usart1_nvic_init_irqs();
	usart1_port_init();
#if __USE_LFOS__
	_usart_sem_init(1);
#endif

	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;    //禁LPUART1时钟
	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(1)    //选择时钟 Clock Src= 1 (SOSCDIV2_CLK)
                               		| PCC_PCCn_CGC_MASK;   //使能LPUART1时钟
	_lpuart_init(LPUART1,bps,iParity);
}


//波特率: bps , 1停止位, 8个数据位, 无奇偶校验
void usart2_init(unsigned long bps,char iParity)
{
	usart2_nvic_init_irqs();
	usart2_port_init();
#if __USE_LFOS__
	_usart_sem_init(2);
#endif

	PCC->PCCn[PCC_LPUART2_INDEX] &= ~PCC_PCCn_CGC_MASK;    //禁LPUART2时钟
	PCC->PCCn[PCC_LPUART2_INDEX] |= PCC_PCCn_PCS(1)    //选择时钟 Clock Src= 1 (SOSCDIV2_CLK)
                               		| PCC_PCCn_CGC_MASK;   //使能LPUART2时钟
	_lpuart_init(LPUART2,bps,iParity);
}


void _usart_send_char(LPUART_Type *lpuart,unsigned char ch)
{
	lpuart->DATA = ch;              /* Send data */
	/* Function to Transmit single Char */
  	while((lpuart->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT==0);
                                   /* Wait for transmit buffer to be empty */
}


/*********************************************************************
 * 函数原型：void usart0_send_char(unsigned char ch)
 * 功        能：UART0发送一个BYTE的数据
 * 输入参数：ch--需要发送的字符数据
 * 返回参数：无
 *
 * 其他说明：
*********************************************************************/
void _usart0_send_char(unsigned char ch)
{
	_usart_send_char(LPUART0,ch);
}

void _usart1_send_char(unsigned char ch)
{
	_usart_send_char(LPUART1,ch);
}

void _usart2_send_char(unsigned char ch)
{
	_usart_send_char(LPUART2,ch);
}


void usart0_send_char(unsigned char ch)
{
#if __USE_LFOS__
	_usart_tx_sem_pend(0,0);
#endif
	_usart_send_char(LPUART0,ch);
#if __USE_LFOS__
	_usart_tx_sem_post(0);
#endif
}

void usart1_send_char(unsigned char ch)
{
#if __USE_LFOS__
		_usart_tx_sem_pend(1,0);
#endif

	_usart_send_char(LPUART1,ch);
#if __USE_LFOS__
	_usart_tx_sem_post(1);
#endif
}

void usart2_send_char(unsigned char ch)
{
#if __USE_LFOS__
	_usart_tx_sem_pend(2,0);
#endif
	_usart_send_char(LPUART2,ch);
#if __USE_LFOS__
	_usart_tx_sem_post(2);
#endif
}


//串口接收状态
typedef enum tagUsartRecvStatus
{
	UsartRecvStatus_Nodata = 0,
	UsartRecvStatus_Recving,
	UsartRecvStatus_RecvFinish
}UsartRecvStatus;

typedef struct tagUsartRx
{
	unsigned char buf[USART_RECV_BUF_SIZE];			//缓冲区大小
	unsigned int write_idx;							//写索引
	unsigned int read_idx;							//读索引  数据处理过程就是 读索引去追写索引
	unsigned int total_len;								//标识接收的总数据量
	UsartRecvStatus stUsartRecvStatus;				//状态
	unsigned int timeout;							//超时计数
}UsartRx;


static UsartRx s_astUsartRx[USART_CNT] = {0};

//每1ms执行一次
void usart_rx_timing(unsigned char usart_channel)
{
	s_astUsartRx[usart_channel].timeout++;
	if ((s_astUsartRx[usart_channel].stUsartRecvStatus == UsartRecvStatus_Recving)
	&& (s_astUsartRx[usart_channel].timeout >= USART_MAX_TWO_BYTE_INTERVAL))
	{
		s_astUsartRx[usart_channel].stUsartRecvStatus = UsartRecvStatus_RecvFinish;
		#if __USE_LFOS__
		_usart_rx_sem_post(usart_channel);
		#endif
	}
}

unsigned int _get_usart_recv_cnt(unsigned char usart_ch)
{
	if (s_astUsartRx[usart_ch].stUsartRecvStatus != UsartRecvStatus_RecvFinish)
	{
		return 0;
	}

	if (s_astUsartRx[usart_ch].write_idx >= s_astUsartRx[usart_ch].read_idx)
	{
		return (s_astUsartRx[usart_ch].write_idx - s_astUsartRx[usart_ch].read_idx);
	}
	else
	{
		return (s_astUsartRx[usart_ch].write_idx + USART_RECV_BUF_SIZE - s_astUsartRx[usart_ch].read_idx);
	}
}

unsigned int get_usart0_recv_cnt(void)
{
	return _get_usart_recv_cnt(0);
}

unsigned int get_usart1_recv_cnt(void)
{
	return _get_usart_recv_cnt(1);
}

unsigned int get_usart2_recv_cnt(void)
{
	return _get_usart_recv_cnt(2);
}

unsigned int _read_usart(unsigned char usart_ch,void *buf,unsigned int ulBufSize)
{
	unsigned int temp = 0;
	unsigned int rlen = 0;
	unsigned int read_idx = s_astUsartRx[usart_ch].read_idx;
	unsigned int write_idx = s_astUsartRx[usart_ch].write_idx;

	if ((buf == 0) || (ulBufSize == 0))
	{
		return 0;
	}

	if (read_idx == write_idx) return 0;
	if (s_astUsartRx[usart_ch].stUsartRecvStatus != UsartRecvStatus_RecvFinish) return 0;
	
	if (write_idx >= read_idx)
	{
		rlen = write_idx - read_idx;

		if (rlen > ulBufSize)
		{
			temp = ulBufSize;
			//标识还没读取完成
			s_astUsartRx[usart_ch].stUsartRecvStatus = UsartRecvStatus_RecvFinish;
		}
		else
		{
			temp = rlen;
		}
		memset(buf,0,ulBufSize);
		memcpy(buf,s_astUsartRx[usart_ch].buf + s_astUsartRx[usart_ch].read_idx,temp);
	}
	else
	{
		rlen = write_idx + USART_RECV_BUF_SIZE - read_idx;	
		if (rlen > ulBufSize)
		{
			temp = ulBufSize;
			//标识还没读取完成
			s_astUsartRx[usart_ch].stUsartRecvStatus = UsartRecvStatus_RecvFinish;
		}
		else
		{
			temp = rlen;
		}
		
		memset(buf,0,ulBufSize);
		if ((temp + s_astUsartRx[usart_ch].read_idx) <= USART_RECV_BUF_SIZE)
		{
			memcpy(buf,s_astUsartRx[usart_ch].buf + s_astUsartRx[usart_ch].read_idx,temp);
		}
		else
		{
			unsigned int seg_cnt1 = USART_RECV_BUF_SIZE - s_astUsartRx[usart_ch].read_idx;
			unsigned int seg_cnt2 = temp - seg_cnt1;

			memcpy(buf,s_astUsartRx[usart_ch].buf + s_astUsartRx[usart_ch].read_idx,seg_cnt1);
			memcpy((unsigned char *)buf + seg_cnt1,s_astUsartRx[usart_ch].buf,seg_cnt2);
		}


	}
	s_astUsartRx[usart_ch].read_idx += temp;
	if (s_astUsartRx[usart_ch].read_idx >= USART_RECV_BUF_SIZE)
	{
		s_astUsartRx[usart_ch].read_idx -= USART_RECV_BUF_SIZE;
	}

	return temp;
}


unsigned int _usart0_read(void *buf,unsigned int ulBufSize)
{
	return _read_usart(0,buf,ulBufSize);
}

unsigned int _usart1_read(void *buf,unsigned int ulBufSize)
{
	return _read_usart(1,buf,ulBufSize);
}

unsigned int _usart2_read(void *buf,unsigned int ulBufSize)
{
	return _read_usart(2,buf,ulBufSize);
}

unsigned int usart0_read(void *buf,unsigned int ulBufSize,unsigned int timeout)
{
	//return SEGGER_RTT_Read(0,buf,ulBufSize);
#if __USE_LFOS__
	_usart_rx_sem_pend(0,timeout);
	return _read_usart(0,buf,ulBufSize);
#else
	return _read_usart(0,buf,ulBufSize);
#endif
}

unsigned int usart1_read(void *buf,unsigned int ulBufSize,unsigned int timeout)
{
#if __USE_LFOS__
	_usart_rx_sem_pend(1,timeout);
	return _read_usart(1,buf,ulBufSize);
#else
	return _read_usart(1,buf,ulBufSize);
#endif
}

unsigned int usart2_read(void *buf,unsigned int ulBufSize,unsigned int timeout)
{
#if __USE_LFOS__
	_usart_rx_sem_pend(2,timeout);
	return _read_usart(2,buf,ulBufSize);
#else
	return _read_usart(2,buf,ulBufSize);
#endif
}


void usart_recv_handler(unsigned char usart_channel,unsigned char ch)
{
	//状态:接收中
	s_astUsartRx[usart_channel].stUsartRecvStatus = UsartRecvStatus_Recving;
	s_astUsartRx[usart_channel].timeout = 0;

	s_astUsartRx[usart_channel].buf[s_astUsartRx[usart_channel].write_idx] = ch;
	s_astUsartRx[usart_channel].write_idx++;
	if (s_astUsartRx[usart_channel].write_idx >= USART_RECV_BUF_SIZE)
	{
		s_astUsartRx[usart_channel].write_idx = 0;
	}
	s_astUsartRx[usart_channel].total_len++;
}

usart_data_arrive_call_back_func p_usart0_dat_arrive = 0;
usart_data_arrive_call_back_func p_usart1_dat_arrive = 0;
usart_data_arrive_call_back_func p_usart2_dat_arrive = 0;


void reg_callback_usart0_data_arrive(usart_data_arrive_call_back_func pfunc)
{
	p_usart0_dat_arrive = pfunc;
}

void reg_callback_usart1_data_arrive(usart_data_arrive_call_back_func pfunc)
{
	p_usart1_dat_arrive = pfunc;
}

void reg_callback_usart2_data_arrive(usart_data_arrive_call_back_func pfunc)
{
	p_usart2_dat_arrive = pfunc;
}

void LPUART0_RxTx_IRQHandler(void)
{
	unsigned char rev = 0;

	if (LPUART0->STAT & 0x00200000)
	{
		rev = LPUART0->DATA;

		//usart0_send_char(rev);
		usart_recv_handler(0,rev);
		if (p_usart0_dat_arrive) p_usart0_dat_arrive(rev);
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	unsigned char rev = 0;

	if (LPUART1->STAT & 0x00200000)
	{
		rev = LPUART1->DATA;
		usart_recv_handler(1,rev);
		if (p_usart1_dat_arrive) p_usart1_dat_arrive(rev);

	}
}

void LPUART2_RxTx_IRQHandler(void)
{
	unsigned char rev = 0;

	if (LPUART2->STAT & 0x00200000)
	{
		rev = LPUART2->DATA;
		usart_recv_handler(2,rev);
		
		if (p_usart2_dat_arrive) p_usart2_dat_arrive(rev);
	}
}


unsigned int _usart_send_data(LPUART_Type *lpuart,void *pdat,unsigned int len)
{
	unsigned int i = 0;
	unsigned char *ptr = (unsigned char *)pdat;

	if ((pdat == 0) || (len == 0)) return 0;

	for (i = 0; i < len; i++)
	{
		_usart_send_char(lpuart,*(ptr + i));
	}
	return len;
}


unsigned int _usart0_send_data(void *pdat,unsigned int len)
{
	return _usart_send_data(LPUART0,pdat,len);
}

unsigned int _usart1_send_data(void *pdat,unsigned int len)
{
	return _usart_send_data(LPUART1,pdat,len);
}

unsigned int _usart2_send_data(void *pdat,unsigned int len)
{
	return _usart_send_data(LPUART2,pdat,len);
}


unsigned int usart0_send_data(void *pdat,unsigned int len)
{
	unsigned int rlen = 0;

#if __USE_LFOS__
	_usart_tx_sem_pend(0,0);
#endif
	rlen = _usart_send_data(LPUART0,pdat,len);
#if __USE_LFOS__
	_usart_tx_sem_post(0);
#endif
	return rlen;
}

unsigned int usart1_send_data(void *pdat,unsigned int len)
{
	unsigned int rlen = 0;

#if __USE_LFOS__
	_usart_tx_sem_pend(1,0);
#endif
	rlen = _usart_send_data(LPUART1,pdat,len);
#if __USE_LFOS__
	_usart_tx_sem_post(1);
#endif
	return rlen;
}

unsigned int usart2_send_data(void *pdat,unsigned int len)
{
	unsigned int rlen = 0;

#if __USE_LFOS__
	_usart_tx_sem_pend(2,0);
#endif
	rlen = _usart_send_data(LPUART2,pdat,len);
#if __USE_LFOS__
	_usart_tx_sem_post(2);
#endif
	return rlen;
}

#if 0
/*
 * FLEXIO UART DEMO USE CASE
 * Rev1.0
 * Demo will show the UART communication using the FlexIO module with following parameters:
 * 8-bit communication
 * One stop bit
 * No parity
 * No hardware flow control
 * Baud rate: 115200
 * Hardware used: S32K144 EVB
 * PTA0: FlexIO_D2 as TX
 * PTA1: FlexIO_D3 as RX
 */

char string[] = "\rHello World!!!\n\r";



void Flexio_Uart_Tx_Init(void)
{

	PORTA->PCR[1] |= PORT_PCR_MUX(0x04);  /* Select PTA1 MUX as FXIOD3 */

	/* Shifter Configuration*/
	FLEXIO->SHIFTCFG[0]|= FLEXIO_SHIFTCFG_SSTOP(0x03)   /* Stop bit enable on logic 1*/
					   |  FLEXIO_SHIFTCFG_SSTART(0x02); /* Start bit 0 before loading the data on first shift*/

	FLEXIO->SHIFTCTL[0]|= FLEXIO_SHIFTCTL_TIMSEL(0X00)  /* Select Timer 0*/
					   |  FLEXIO_SHIFTCTL_TIMPOL(0x00)  /* Shift on pos edge*/
					   |  FLEXIO_SHIFTCTL_PINCFG(0x03)  /* Shift as output*/
					   |  FLEXIO_SHIFTCTL_PINSEL(0x03)  /* FXIO D3 as Tx*/
					   |  FLEXIO_SHIFTCTL_PINPOL(0x00)  /* Pin active high*/
					   |  FLEXIO_SHIFTCTL_SMOD(0x02);    /* Shifter in Tx mode*/


	/* Timer Configuration*/
	FLEXIO->TIMCFG[0]|= FLEXIO_TIMCFG_TIMDEC(0x0) /* Counter Decrement of FlexIO clock*/
					 | FLEXIO_TIMCFG_TIMDIS(0x02) /* Timer disable on Timer compare*/
					 | FLEXIO_TIMCFG_TIMENA(0x02) /* Timer enable on trigger high*/
					 | FLEXIO_TIMCFG_TSTOP(0x02) /* Shifter to generate stop bit on timer compare*/
					 | FLEXIO_TIMCFG_TSTART(0x01); /* Enable start bit*/


	FLEXIO->TIMCTL[0]|= FLEXIO_TIMCTL_TRGSEL(0x01)     /* Trigger on shifter flag*/
					 |  FLEXIO_TIMCTL_TRGPOL(0x01)    /* Trigger active LOW*/
					 |  FLEXIO_TIMCTL_TRGSRC(0x01)    /* Internal Trigger*/
					 |  FLEXIO_TIMCTL_PINSEL(0x03)    /* Select FXIO D3*/
					 |  FLEXIO_TIMCTL_PINCFG(0x00)    /* FXDIO disabled*/
					 |  FLEXIO_TIMCTL_TIMOD(0x01);     /* Baud rate mode*/


	/* Time Compare*/
	FLEXIO->TIMCMP[0]=0x0F21;  /* Baud rate at 115200*/

}


void Flexio_Uart_Rx_Init(void)
{

	PORTA->PCR[0]|=PORT_PCR_MUX(0x04);  /* Select PTA0 MUX as FXIOD2 */

	/* Shifter Configuratio*/
	FLEXIO->SHIFTCFG[1]|= FLEXIO_SHIFTCFG_INSRC(0x00)	/* Pin Source*/
						|	FLEXIO_SHIFTCFG_SSTOP(0x03) /* Stop bit enable on logic 1*/
						|	FLEXIO_SHIFTCFG_SSTART(0x02); /* Start bit 0*/

	FLEXIO->SHIFTCTL[1]|= FLEXIO_SHIFTCTL_TIMSEL(0x01)  /* Select Timer 1*/
						|  FLEXIO_SHIFTCTL_TIMPOL(0x01)  /* Shift on neg edge*/
						|  FLEXIO_SHIFTCTL_PINCFG(0x00)  /* Pin disabled*/
						|  FLEXIO_SHIFTCTL_PINSEL(0x02)  /* FXIO D3*/
						|  FLEXIO_SHIFTCTL_PINPOL(0x00)  /* Pin active high*/
						|  FLEXIO_SHIFTCTL_SMOD(0x01);    /* Shifter in Rx mode*/

	/*Timer Configuration*/
	FLEXIO->TIMCFG[1]|= FLEXIO_TIMCFG_TIMDEC(0x0) /* Counter Decrement of FlexIO clock*/
						 | FLEXIO_TIMCFG_TIMDIS(0x02) /* Timer disable on Timer compare*/
						 | FLEXIO_TIMCFG_TIMENA(0x04) /* Timer enable on pin rising edge*/
						 | FLEXIO_TIMCFG_TSTOP(0x02) /* Shifter to generate stop bit on timer compare*/
						 | FLEXIO_TIMCFG_TSTART(0x01); /* Enable start bit*/

	FLEXIO->TIMCTL[1]|= FLEXIO_TIMCTL_TRGSEL(0x04)     /* Trigger on input pin 2 */
							|FLEXIO_TIMCTL_TRGPOL(0x00)    /* Trigger active LOW*/
							|FLEXIO_TIMCTL_TRGSRC(0x01)    /* Internal Trigger*/
							|FLEXIO_TIMCTL_PINSEL(0x02)    /* Select FXIO D2*/
							|FLEXIO_TIMCTL_PINPOL(0x01)    /* PIN pol low*/
							|FLEXIO_TIMCTL_PINCFG(0x00)    /* FXDIO disabled*/
							|FLEXIO_TIMCTL_TIMOD(0x01);     /* Baud rate mode*/
    /*Timer Compare*/
	FLEXIO->TIMCMP[1]=0x0F21;  /* Baud rate at 115200*/



}


int flexio_uart_init(void)
{
	char i=0;

	PCC->PCCn[PCC_FlexIO_INDEX] |= PCC_PCCn_PCS(1); /*OSC clock for FlexIO */
	PCC->PCCn[PCC_FlexIO_INDEX] |= PCC_PCCn_CGC_MASK; /* Enable clock for FlexIO */
	PCC->PCCn[PCC_PORTA_INDEX ] |= PCC_PCCn_CGC_MASK; /* Enable clock for PORTA */

	Flexio_Uart_Tx_Init();
	Flexio_Uart_Rx_Init();

	/* Enable FlexIO*/
	FLEXIO->CTRL|=FLEXIO_CTRL_FLEXEN_MASK;

    /* Send hello string*/
	for (i=0;i<sizeof(string);i++)
	{
		/* Send each character*/
		FLEXIO->SHIFTBUF[0]=string[i];
		while((FLEXIO->SHIFTSTAT & 0x01) ==0 );
	}

	return 0;
}


void FLEXIO_IRQHandler(void)
{
	static char s_sled = 0;

	set_sys_led(s_sled);
	set_net_led(s_sled);
	set_data_led(s_sled);
	set_can_led(s_sled);
	s_sled = !s_sled;
}
#endif






