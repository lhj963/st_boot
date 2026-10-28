#include "can.h"

CanMsgArriveCallBack pcan0_msg_arrive_func = 0;
CanMsgArriveCallBack pcan1_msg_arrive_func = 0;
CanMsgArriveCallBack pcan2_msg_arrive_func = 0;
CanRxMsg can0_msg_temp;
CanRxMsg can1_msg_temp;
CanRxMsg can2_msg_temp;


void view_can_reg(void)
{
	unsigned int mcr = 0;
	unsigned int ctrl1 = 0;
	unsigned int timer = 0;

	PCC->PCCn[PCC_FlexCAN0_INDEX] = PCC_PCCn_CGC_MASK;

	mcr = CAN0->MCR;
	ctrl1 = CAN0->CTRL1;
	timer = CAN0->TIMER;

	DBG_Print(0,"MCR:%08X CTRL1:%08X TIMER:%08X\r\n",mcr,ctrl1,timer);
}

void can0_port_init(void)
{
	PCC->PCCn[PCC_PORTE_INDEX] |= PCC_PCCn_CGC_MASK; //使能PTE端口时钟

	PORTE->PCR[4] |= PORT_PCR_MUX(5) | (1 << 6); // Port E4: MUX = ALT5, CAN0_RX 复用
	PORTE->PCR[5] |= PORT_PCR_MUX(5) | (1 << 6); // Port E5: MUX = ALT5, CAN0_TX 复用
}

void can1_port_init(void)
{
	PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK; //使能PTA端口时钟

	PORTA->PCR[12] |= PORT_PCR_MUX(3) | (1 << 6); // Port A12: MUX = ALT3, CAN1_RX 复用
	PORTA->PCR[13] |= PORT_PCR_MUX(3) | (1 << 6); // Port A13: MUX = ALT3, CAN1_TX 复用
}

void can2_port_init(void)
{
	PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK; //使能PTB端口时钟

	PORTB->PCR[12] |= PORT_PCR_MUX(4) | (1 << 6); // Port B12: MUX = ALT4, CAN2_RX 复用
	PORTB->PCR[13] |= PORT_PCR_MUX(4) | (1 << 6); // Port B13: MUX = ALT4, CAN2_TX 复用
}


void can0_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)(1ul << (CAN0_ORed_0_15_MB_IRQn % 32));  /* IRQ81-CHA0 0-15: clr any pending IRQ*/
	S32_NVIC->ISER[(uint32_t)(CAN0_ORed_0_15_MB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(CAN0_ORed_0_15_MB_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[CAN0_ORed_0_15_MB_IRQn] = 0x0b;              /* IRQ81-CAN0 0-15: priority 10 of 0-15*/
}

void can1_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)(1ul << (CAN1_ORed_0_15_MB_IRQn % 32));  /* IRQ81-CHA0 0-15: clr any pending IRQ*/
	S32_NVIC->ISER[(uint32_t)(CAN1_ORed_0_15_MB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(CAN1_ORed_0_15_MB_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[CAN1_ORed_0_15_MB_IRQn] = 0x0b;              /* IRQ81-CAN0 0-15: priority 10 of 0-15*/
}

void can2_nvic_init_irqs(void)
{
	S32_NVIC->ICPR[1] = (uint32_t)(1ul << (CAN2_ORed_0_15_MB_IRQn % 32));
	S32_NVIC->ISER[(uint32_t)(CAN2_ORed_0_15_MB_IRQn) >> 5U] = (uint32_t)(1UL << ((uint32_t)(CAN2_ORed_0_15_MB_IRQn) & (uint32_t)0x1FU));
	S32_NVIC->IP[CAN2_ORed_0_15_MB_IRQn] = 0x0b;              /* IRQ81-CAN0 0-15: priority 10 of 0-15*/
}


#define MSG_BUF_SIZE  4    /* Msg Buffer Size. (CAN 2.0AB: 2 hdr +	2 data= 4 words) */
#define CAN_RX_FIFO_CHANNEL 	4
#define CAN_RX_FIFO_CHANNEL1 	3


void _can_init(CAN_Type *can,unsigned int can_bps)
{
	unsigned int i = 0;
	unsigned int cnt = 0;

	//先复位寄存器的值  0x0D890000F
	can->MCR = 0x0D890000F;
	can->CTRL1 = 0;

	can->MCR |= CAN_MCR_MDIS_MASK; 		/* MDIS=1: Disable module before selecting clock */

	can->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;	/* CLKSRC=0: Clock Source = oscillator (8 MHz) */

	can->MCR &= ~CAN_MCR_MDIS_MASK;		/* MDIS=0; Enable module config. (Sets FRZ, HALT) */

	while (!((can->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))
	{

	} /* Good practice: wait for FRZACK=1 on freeze mode entry/exit */

	//This register can only be written in Freeze mode as it is blocked by hardware in other modes
	can->RXMGMASK = 0; /* Global acceptance mask: not check ID bits */
	can->RXFGMASK = 0;

	if (can_bps == 500)
	{
		can->CTRL1 = 0x00DB0006; /* Configure for 500 KHz bit time */
								  /* Time quanta freq = 16 time quanta x 500 KHz bit time= 8MHz */
								  /* PRESDIV+1 = Fclksrc/Ftq = 8 MHz/8 MHz = 1 */
								  /*	so PRESDIV = 0 */
								  /* PSEG2 = Phase_Seg2 - 1 = 4 - 1 = 3 */
								  /* PSEG1 = PSEG2 = 3 */
								  /* PROPSEG= Prop_Seg - 1 = 7 - 1 = 6 */
								  /* RJW: since Phase_Seg2 >=4, RJW+1=4 so RJW=3. */
								  /* SMP = 1: use 3 bits per CAN sample */
								  /* CLKSRC=0 (unchanged): Fcanclk= Fosc= 8 MHz */
	}
	else if (can_bps == 250)
	{
		can->CTRL1 |= CAN_CTRL1_PRESDIV(1);
		can->CTRL1 |= CAN_CTRL1_RJW(3);
		can->CTRL1 |= CAN_CTRL1_PSEG1(3);
		can->CTRL1 |= CAN_CTRL1_PSEG2(3);
		can->CTRL1 |= 0x06;
	}
	else if (can_bps == 125)
	{
		can->CTRL1 |= CAN_CTRL1_PRESDIV(3);
		can->CTRL1 |= CAN_CTRL1_RJW(3);
		can->CTRL1 |= CAN_CTRL1_PSEG1(3);
		can->CTRL1 |= CAN_CTRL1_PSEG2(3);
		can->CTRL1 |= 0x06;
	}
	else if (can_bps == 1000)
	{
		can->CTRL1 |= CAN_CTRL1_PRESDIV(0);
		can->CTRL1 |= CAN_CTRL1_RJW(0);
		can->CTRL1 |= CAN_CTRL1_PSEG1(2);
		can->CTRL1 |= CAN_CTRL1_PSEG2(1);
		can->CTRL1 |= 0x01;
	}

	if (can == CAN0)
	{
		cnt = 128;
	}
	else
	{
		cnt = 64;
	}
	for (i = 0; i < cnt; i++)
	{						  /* CANx: clear 32 msg bufs x 4 words/msg buf = 128 words*/
		can->RAMn[i] = 0;	  /* Clear msg buf word */
	}

	for (i = 0; i < 16; i++)
	{								  /* In FRZ mode, init CAN0 16 msg buf filters */
		can->RXIMR[i] = 0;  /* Not Check ID bits for incoming messages */
	}

	can->RAMn[CAN_RX_FIFO_CHANNEL*MSG_BUF_SIZE + 0] = 0x04000000 | (1 << CAN_WMBn_CS_IDE_SHIFT);
												/* Msg Buf 4, word 0: Enable for reception */
												  /* EDL,BRS,ESI=0: CANFD not used */
												  /* CODE=4: MB set to RX inactive */
												  /* IDE=0: Standard ID or Extended */
												  /* SRR, RTR, TIME STAMP = 0: not applicable */

										

	can->RAMn[CAN_RX_FIFO_CHANNEL*MSG_BUF_SIZE + 1] = 0; /* Msg Buf 4, word 1: Standard ID = 0*/

	can->RAMn[CAN_RX_FIFO_CHANNEL1*MSG_BUF_SIZE + 0] = 0x04000000;
												/* Msg Buf 4, word 0: Enable for reception */
												  /* EDL,BRS,ESI=0: CANFD not used */
												  /* CODE=4: MB set to RX inactive */
												  /* IDE=0: Standard ID or Extended */
												  /* SRR, RTR, TIME STAMP = 0: not applicable */

	can->RAMn[CAN_RX_FIFO_CHANNEL1*MSG_BUF_SIZE + 1] = 0; /* Msg Buf 4, word 1: Standard ID = 0*/

	/* Open FIFO receives interrupt */
	can->IMASK1 |= (1 << CAN_RX_FIFO_CHANNEL) | (1 << CAN_RX_FIFO_CHANNEL1);


	// Self-reception disabled.
	can->MCR = (0x0000001F | (1 << CAN_MCR_SRXDIS_SHIFT));
	//can->MCR = 0x0000001F;


	while ((can->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT)
	{

	}

	/* Good practice: wait for FRZACK to clear (not in freeze mode) */
	while ((can->MCR & CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)
	{

	}
	/* Good practice: wait for NOTRDY to clear (module ready)  */
}

void can0_init(unsigned int can_bps)
{
	can0_port_init();
	can0_nvic_init_irqs();

	PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK; /* CGC=1: enable clock to FlexCAN0 */

	_can_init(CAN0,can_bps);
}

void can1_init(unsigned int can_bps)
{
	can1_port_init();
	can1_nvic_init_irqs();

	PCC->PCCn[PCC_FlexCAN1_INDEX] |= PCC_PCCn_CGC_MASK; /* CGC=1: enable clock to FlexCAN0 */

	_can_init(CAN1,can_bps);
}


void can2_init(unsigned int can_bps)
{
	can2_port_init();
	can2_nvic_init_irqs();

	PCC->PCCn[PCC_FlexCAN2_INDEX] |= PCC_PCCn_CGC_MASK; /* CGC=1: enable clock to FlexCAN2 */

	_can_init(CAN2,can_bps);
}


//0表示发送成功 非0表示发送失败
unsigned char _can_tx_msg(CAN_Type *can,unsigned char IDE,unsigned char RTR,unsigned char prio,unsigned int can_id,void *pdat,unsigned char len)
{
	unsigned char i = 0;
	unsigned char DLC = 0;
	unsigned char *ptr = (unsigned char *)pdat;
	unsigned int dat1 = 0;
	unsigned int dat2 = 0;
	unsigned int send_cnt = 0;

	if (pdat == 0) return 0;

	IDE = IDE ? 1 : 0;
	RTR = RTR ? 1 : 0;
	DLC = (len > 8) ? 8 : len;
	prio &= 0x07;				//优先级 3位

	for (i = 0; i < DLC; i++)
	{
		if (i <= 3)
		{
			dat1 <<= 8;
			dat1 |= ptr[i];
		}
		else
		{
			dat2 <<= 8;
			dat2 |= ptr[i];
		}
	}

	/* Assumption:  Message buffer CODE is INACTIVE */
	can->IFLAG1 = 0x00000001;       /* Clear CAN 0 MB 0 flag without clearing others */


	can->RAMn[0*MSG_BUF_SIZE + 2] = dat1; 	/* MB0 word 2: data word 0 */
	can->RAMn[0*MSG_BUF_SIZE + 3] = dat2;	/*MB0 word 3: data word 1 */
 
	if (IDE)			//扩展帧
	{
		can->RAMn[ 0*MSG_BUF_SIZE + 1] = can_id | (prio << 29);
	}
	else				//标准帧
	{
		can->RAMn[0*MSG_BUF_SIZE + 1] = (can_id << 18) | (prio << 29);
	}

	can->RAMn[0*MSG_BUF_SIZE + 0] = 0x0C400000
								| (DLC << CAN_WMBn_CS_DLC_SHIFT)
								| (IDE << CAN_WMBn_CS_IDE_SHIFT)
								| (RTR << CAN_WMBn_CS_RTR_SHIFT); 
								/* MB0 word 0: */
                                /* EDL,BRS,ESI=0: CANFD not used */
                                /* CODE=0xC: Activate msg buf to transmit */
                                /* IDE=0: Standard ID */
                                /* SRR=1 Tx frame (not req'd for std ID) */
                                /* RTR = 0: data, not remote tx request frame*/
                                /* DLC = 8 bytes */
    while(0 == (can->IFLAG1 & 1))
    {
		send_cnt++; //wait send finish
		if (send_cnt >= 5000)
		{
			return 1;
		}
    }

	return 0;
}


unsigned char can0_tx_msg(unsigned char IDE,unsigned char RTR,unsigned char prio,unsigned int can_id,void *pdat,unsigned char len)
{
	return _can_tx_msg(CAN0,IDE,RTR,prio,can_id,pdat,len);
}

unsigned char can1_tx_msg(unsigned char IDE,unsigned char RTR,unsigned char prio,unsigned int can_id,void *pdat,unsigned char len)
{
	return _can_tx_msg(CAN1,IDE,RTR,prio,can_id,pdat,len);
}

unsigned char can2_tx_msg(unsigned char IDE,unsigned char RTR,unsigned char prio,unsigned int can_id,void *pdat,unsigned char len)
{
	return _can_tx_msg(CAN2,IDE,RTR,prio,can_id,pdat,len);
}


unsigned int CAN0_RX_MSG_BUF[CAN0_RX_BUFF_CNT][4] = {0};
unsigned int CAN1_RX_MSG_BUF[CAN1_RX_BUFF_CNT][4] = {0};
unsigned int CAN2_RX_MSG_BUF[CAN2_RX_BUFF_CNT][4] = {0};


//unsigned int can_rx_msg_cnt[3] = {0};	//已接收未处理的 CAN消息条数
unsigned int can_rx_write_idx[3] = {0};	//CAN消息写指针
unsigned int can_rx_read_idx[3] = {0};	//CAN消息读指针

unsigned long can_rx_total_msg_cnt[3] = {0};

unsigned long can0_get_rx_total_msg_cnt(void)
{
	return can_rx_total_msg_cnt[0];
}
unsigned long can1_get_rx_total_msg_cnt(void)
{
	return can_rx_total_msg_cnt[1];
}
unsigned long can2_get_rx_total_msg_cnt(void)
{
	return can_rx_total_msg_cnt[2];
}


static unsigned int _can_get_rx_msg(unsigned char channel,CanRxMsg *pOutMsg,unsigned int max_buf_cnt)
{
	unsigned int read_idx = can_rx_read_idx[channel];
	unsigned int *ptr = 0;

	if (channel == 0)
	{
		ptr = CAN0_RX_MSG_BUF[read_idx];
	}
	else if (channel == 1)
	{
		ptr = CAN1_RX_MSG_BUF[read_idx];
	}
	else
	{
		ptr = CAN2_RX_MSG_BUF[read_idx];
	}

	if (pOutMsg == 0)
	{
		return 1;
	}

	if (can_rx_read_idx[channel] == can_rx_write_idx[channel])
	{
		return 2;
	}

	pOutMsg->IDE = (ptr[0] >> 21) & 0x01;
	pOutMsg->RTR = (ptr[0] >> 20) & 0x01;
	pOutMsg->DLC = (ptr[0] >> 16) & 0x0F;

	if (pOutMsg->IDE)
	{
		pOutMsg->StdId = 0;
		pOutMsg->ExtId = ptr[1] & 0x1FFFFFFF;
	}
	else
	{
		pOutMsg->StdId = (ptr[1] >> 18) & 0x07FF;
		pOutMsg->ExtId = 0;
	}

	pOutMsg->Data[0] = (unsigned char)(ptr[2] >> 24);
	pOutMsg->Data[1] = (unsigned char)(ptr[2] >> 16);
	pOutMsg->Data[2] = (unsigned char)(ptr[2] >> 8);
	pOutMsg->Data[3] = (unsigned char)(ptr[2]);
	pOutMsg->Data[4] = (unsigned char)(ptr[3] >> 24);
	pOutMsg->Data[5] = (unsigned char)(ptr[3] >> 16);
	pOutMsg->Data[6] = (unsigned char)(ptr[3] >> 8);
	pOutMsg->Data[7] = (unsigned char)(ptr[3]);

	read_idx++;
	//读指针不能超过接收消息最大缓冲区
	if (read_idx >= max_buf_cnt)
	{
		read_idx = 0;
	}
	can_rx_read_idx[channel] = read_idx;

	return 0;
}


unsigned int _can_get_rx_msg_cnt(unsigned char channel,unsigned int max_buf_size)
{
	unsigned int ridx = can_rx_read_idx[channel];
	unsigned int widx = can_rx_write_idx[channel];

	if (widx >= ridx)
	{
		return (widx - ridx);
	}
	else
	{
		return (widx + max_buf_size - ridx);
	}
}


unsigned int can0_get_rx_msg_cnt(void)
{
	return _can_get_rx_msg_cnt(0,CAN0_RX_BUFF_CNT);
}

unsigned int can1_get_rx_msg_cnt(void)
{
	return _can_get_rx_msg_cnt(1,CAN1_RX_BUFF_CNT);
}

unsigned int can2_get_rx_msg_cnt(void)
{
	return _can_get_rx_msg_cnt(2,CAN2_RX_BUFF_CNT);
}

unsigned int can0_get_rx_msg(CanRxMsg *pOutMsg)
{

	return _can_get_rx_msg(0,pOutMsg, CAN0_RX_BUFF_CNT);
}

unsigned int can1_get_rx_msg(CanRxMsg *pOutMsg)
{
	return _can_get_rx_msg(1,pOutMsg,CAN1_RX_BUFF_CNT);
}

unsigned int can2_get_rx_msg(CanRxMsg *pOutMsg)
{
	return _can_get_rx_msg(2,pOutMsg,CAN2_RX_BUFF_CNT);
}

static void analyze_rx_msg(unsigned int msgbuf[],CanRxMsg *pOutMsg)
{
	unsigned int *ptr = msgbuf;

	pOutMsg->IDE = (ptr[0] >> 21) & 0x01;
	pOutMsg->RTR = (ptr[0] >> 20) & 0x01;
	pOutMsg->DLC = (ptr[0] >> 16) & 0x0F;

	if (pOutMsg->IDE)
	{
		pOutMsg->StdId = 0;
		pOutMsg->ExtId = ptr[1] & 0x1FFFFFFF;
	}
	else
	{
		pOutMsg->StdId = (ptr[1] >> 18) & 0x07FF;
		pOutMsg->ExtId = 0;
	}

	pOutMsg->Data[0] = (unsigned char)(ptr[2] >> 24);
	pOutMsg->Data[1] = (unsigned char)(ptr[2] >> 16);
	pOutMsg->Data[2] = (unsigned char)(ptr[2] >> 8);
	pOutMsg->Data[3] = (unsigned char)(ptr[2]);
	pOutMsg->Data[4] = (unsigned char)(ptr[3] >> 24);
	pOutMsg->Data[5] = (unsigned char)(ptr[3] >> 16);
	pOutMsg->Data[6] = (unsigned char)(ptr[3] >> 8);
	pOutMsg->Data[7] = (unsigned char)(ptr[3]);
}



void __CAN_ORed_0_15_MB_IRQHandler(CAN_Type *can,unsigned char channel)
{
	unsigned int temp = 0;
	unsigned short idx = channel * MSG_BUF_SIZE;

	if (can == CAN0)
	{
		can_rx_total_msg_cnt[0]++;

		CAN0_RX_MSG_BUF[can_rx_write_idx[0]][0] = can->RAMn[idx + 0];
		CAN0_RX_MSG_BUF[can_rx_write_idx[0]][1] = can->RAMn[idx + 1];
		CAN0_RX_MSG_BUF[can_rx_write_idx[0]][2] = can->RAMn[idx + 2];
		CAN0_RX_MSG_BUF[can_rx_write_idx[0]][3] = can->RAMn[idx + 3];
		temp = CAN0->RAMn[0*MSG_BUF_SIZE + 0];

		analyze_rx_msg(CAN0_RX_MSG_BUF[can_rx_write_idx[0]],&can0_msg_temp);
		if (pcan0_msg_arrive_func)
		{
			pcan0_msg_arrive_func(&can0_msg_temp);
		}

		can_rx_write_idx[0]++;
		if (can_rx_write_idx[0] >= CAN0_RX_BUFF_CNT)
		{
			can_rx_write_idx[0] = 0;
		}



		//消息缓冲区警告
		//if (can_rx_msg_cnt[0] >= (CAN0_RX_BUFF_CNT - 5))
		{
			//DBG_Print(0,"[warning]CAN0 rx buf(%u/%u).\r\n",can_rx_msg_cnt[0],CAN0_RX_BUFF_CNT);
		}
	
	}
	else if (can == CAN1)
	{
		can_rx_total_msg_cnt[1]++;
		
		CAN1_RX_MSG_BUF[can_rx_write_idx[1]][0] = can->RAMn[idx + 0];		
		CAN1_RX_MSG_BUF[can_rx_write_idx[1]][1] = can->RAMn[idx + 1];
		CAN1_RX_MSG_BUF[can_rx_write_idx[1]][2] = can->RAMn[idx + 2];
		CAN1_RX_MSG_BUF[can_rx_write_idx[1]][3] = can->RAMn[idx + 3];
		temp = CAN1->RAMn[0*MSG_BUF_SIZE + 0];

		analyze_rx_msg(CAN1_RX_MSG_BUF[can_rx_write_idx[1]],&can1_msg_temp);
		if (pcan1_msg_arrive_func)
		{
			pcan1_msg_arrive_func(&can1_msg_temp);
		}
		
		can_rx_write_idx[1]++;
		if (can_rx_write_idx[1] >= CAN1_RX_BUFF_CNT)
		{
			can_rx_write_idx[1] = 0;
		}
		
		//消息缓冲区警告
		//if (can_rx_msg_cnt[1] >= (CAN1_RX_BUFF_CNT - 5))
		{
			//DBG_Print(0,"[warning]CAN1 rx buf(%u/%u).\r\n",can_rx_msg_cnt[1],CAN1_RX_BUFF_CNT);
		}
	
	}
	else if (can == CAN2)
	{
		can_rx_total_msg_cnt[2]++;

		CAN2_RX_MSG_BUF[can_rx_write_idx[2]][0] = can->RAMn[idx + 0];		
		CAN2_RX_MSG_BUF[can_rx_write_idx[2]][1] = can->RAMn[idx + 1];
		CAN2_RX_MSG_BUF[can_rx_write_idx[2]][2] = can->RAMn[idx + 2];
		CAN2_RX_MSG_BUF[can_rx_write_idx[2]][3] = can->RAMn[idx + 3];
		temp = CAN2->RAMn[0*MSG_BUF_SIZE + 0];

		analyze_rx_msg(CAN2_RX_MSG_BUF[can_rx_write_idx[2]],&can2_msg_temp);
		if (pcan2_msg_arrive_func)
		{
			pcan2_msg_arrive_func(&can2_msg_temp);
		}

		can_rx_write_idx[2]++;
		if (can_rx_write_idx[2] >= CAN2_RX_BUFF_CNT)
		{
			can_rx_write_idx[2] = 0;
		}
		
		//消息缓冲区警告
		//if (can_rx_msg_cnt[2] >= (CAN2_RX_BUFF_CNT - 5))
		{
			//DBG_Print(0,"[warning]CAN2 rx buf(%u/%u).\r\n",can_rx_msg_cnt[2],CAN2_RX_BUFF_CNT);
		}
	}
}

void _CAN_ORed_0_15_MB_IRQHandler(CAN_Type *can)
{
	if ((can->IFLAG1 >> CAN_RX_FIFO_CHANNEL) & 0x01)
	{
		__CAN_ORed_0_15_MB_IRQHandler(can,CAN_RX_FIFO_CHANNEL);
		can->IFLAG1 = (1 << CAN_RX_FIFO_CHANNEL);       /* Clear CAN 0 MB CAN_RX_FIFO_CHANNEL flag without clearing others*/
	}

	if ((can->IFLAG1 >> CAN_RX_FIFO_CHANNEL1) & 0x01)
	{
		__CAN_ORed_0_15_MB_IRQHandler(can,CAN_RX_FIFO_CHANNEL1);
		can->IFLAG1 = (1 << CAN_RX_FIFO_CHANNEL1);		/* Clear CAN 0 MB CAN_RX_FIFO_CHANNEL flag without clearing others*/
	}
}

/*********************************************************************
 * 函数原型：void CAN0_ORed_0_15_MB_IRQHandler(void)
 * 功        能：CAN0中断服务器
 * 输入参数：无
 * 返回参数：无
 *
 * 其他说明：
*********************************************************************/
void CAN0_ORed_0_15_MB_IRQHandler(void)
{
	_CAN_ORed_0_15_MB_IRQHandler(CAN0);
}

/*********************************************************************
 * 函数原型：void CAN1_ORed_0_15_MB_IRQHandler(void)
 * 功        能：CAN0中断服务器
 * 输入参数：无
 * 返回参数：无
 *
 * 其他说明：
*********************************************************************/
void CAN1_ORed_0_15_MB_IRQHandler(void)
{
	_CAN_ORed_0_15_MB_IRQHandler(CAN1);
}

/*********************************************************************
 * 函数原型：void CAN2_ORed_0_15_MB_IRQHandler(void)
 * 功        能：CAN0中断服务器
 * 输入参数：无
 * 返回参数：无
 *
 * 其他说明：
*********************************************************************/
void CAN2_ORed_0_15_MB_IRQHandler(void)
{
	_CAN_ORed_0_15_MB_IRQHandler(CAN2);
}


void can_init(unsigned char channel,unsigned int bps)
{
	if (channel == 0)
	{
		can0_init(bps);
	}
	else if (channel == 1)
	{
		can1_init(bps);
	}
	else
	{
		can2_init(bps);
	}
}






void install_can_msg_arrive_hook(unsigned char channel,void (*pf)(CanRxMsg *))
{
	if (channel == 0)
	{
		pcan0_msg_arrive_func = pf;
	}
	else if (channel == 1)
	{
		pcan1_msg_arrive_func = pf;
	}
	else
	{
		pcan2_msg_arrive_func = pf;
	}
}

unsigned long can_recv_total_msg_cnt(unsigned char channel)
{
	if (channel == 0)
	{
		return can0_get_rx_total_msg_cnt();
	}
	else if (channel == 1)
	{
		return can1_get_rx_total_msg_cnt();
	}
	else
	{
		return can2_get_rx_total_msg_cnt();
	}
}


int can_send_data(unsigned char channel,CanTxMsg* CanData)
{
	if (channel == 0)
	{
		return can0_tx_msg(CanData->IDE,CanData->RTR,0,
		CanData->IDE ? CanData->ExtId : CanData->StdId,CanData->Data,CanData->DLC);
	}
	else if (channel == 1)
	{
		return can1_tx_msg(CanData->IDE,CanData->RTR,0,
		CanData->IDE ? CanData->ExtId : CanData->StdId,CanData->Data,CanData->DLC);
	}
	else
	{
		return can2_tx_msg(CanData->IDE,CanData->RTR,0,
		CanData->IDE ? CanData->ExtId : CanData->StdId,CanData->Data,CanData->DLC);
	}
}







