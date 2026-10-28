#ifndef __CAN_H__
#define __CAN_H__
#ifdef __cplusplus
extern "C" {
#endif

#define CAN0_RX_BUFF_CNT  32
#define CAN1_RX_BUFF_CNT  32
#define CAN2_RX_BUFF_CNT  32

typedef struct tagCanTxMsg
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be transmitted. This parameter can be a value 
                        of @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the message that will 
                        be transmitted. This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be 
                        transmitted. This parameter can be a value between 
                        0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0 
                        to 0xFF. */
} CanTxMsg;



typedef struct tagCanRxMsg
{
  uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

  uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

  uint8_t IDE;     /*!< Specifies the type of identifier for the message that 
                        will be received. This parameter can be a value of 
                        @ref CAN_identifier_type */

  uint8_t RTR;     /*!< Specifies the type of frame for the received message.
                        This parameter can be a value of 
                        @ref CAN_remote_transmission_request */

  uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

  uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to 
                        0xFF. */

  uint8_t FMI;     /*!< Specifies the index of the filter the message stored in 
                        the mailbox passes through. This parameter can be a 
                        value between 0 to 0xFF */
} CanRxMsg;

#define CAN_Id_Extended  	1
#define CAN_RTR_DATA     	0
#define CAN_RTR_REMOTE     	1

typedef void (*CanMsgArriveCallBack)(CanRxMsg *);




extern void view_can_reg(void);


extern void can0_init(unsigned int can_bps);
extern void can1_init(unsigned int can_bps);
extern void can2_init(unsigned int can_bps);


/****************CAN消息发送相关接口********************/
extern unsigned char can0_tx_msg(unsigned char IDE,unsigned char RTR,
									unsigned char prio,unsigned int can_id,
									void *pdat,unsigned char len);
	
extern unsigned char can1_tx_msg(unsigned char IDE,unsigned char RTR,
									unsigned char prio,unsigned int can_id,
									void *pdat,unsigned char len);

extern unsigned char can2_tx_msg(unsigned char IDE,unsigned char RTR,
									unsigned char prio,unsigned int can_id,
									void *pdat,unsigned char len);



/****************CAN消息读取相关接口********************/
extern unsigned long can0_get_rx_total_msg_cnt(void);
extern unsigned long can1_get_rx_total_msg_cnt(void);
extern unsigned long can2_get_rx_total_msg_cnt(void);

extern unsigned int can0_get_rx_msg_cnt(void);
extern unsigned int can1_get_rx_msg_cnt(void);
extern unsigned int can2_get_rx_msg_cnt(void);
extern unsigned int can0_get_rx_msg(CanRxMsg *pOutMsg);
extern unsigned int can1_get_rx_msg(CanRxMsg *pOutMsg);
extern unsigned int can2_get_rx_msg(CanRxMsg *pOutMsg);


extern void can_init(unsigned char channel,unsigned int bps);
extern void install_can_msg_arrive_hook(unsigned char channel,void (*pf)(CanRxMsg *));
extern unsigned long can_recv_total_msg_cnt(unsigned char channel);
extern int can_send_data(unsigned char channel,CanTxMsg* CanData);




#ifdef __cplusplus
}
#endif

#endif
