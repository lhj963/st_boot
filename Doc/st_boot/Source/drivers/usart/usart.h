#ifndef __USART_H__
#define __USART_H__
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __USE_LFOS__
#define __USE_LFOS__  0
#endif


#define USART_RECV_BUF_SIZE   			(1536+128)		//串口接收缓冲区大小
#define USART_CNT  			   			3				//串口数量
#define USART_MAX_TWO_BYTE_INTERVAL 	30			//两个字节接收的最大时间间隔



extern void usart0_init(unsigned long bps,char iParity);
extern void usart1_init(unsigned long bps,char iParity);
extern void usart2_init(unsigned long bps,char iParity);

extern void usart0_send_char(unsigned char ch);
extern void usart1_send_char(unsigned char ch);
extern void usart2_send_char(unsigned char ch);

extern unsigned int usart0_send_data(void *pdat,unsigned int len);
extern unsigned int usart1_send_data(void *pdat,unsigned int len);
extern unsigned int usart2_send_data(void *pdat,unsigned int len);


extern unsigned int get_usart0_recv_cnt(void);
extern unsigned int get_usart1_recv_cnt(void);
extern unsigned int get_usart2_recv_cnt(void);

extern unsigned int usart0_read(void *buf,unsigned int ulBufSize,unsigned int timeout);
extern unsigned int usart1_read(void *buf,unsigned int ulBufSize,unsigned int timeout);
extern unsigned int usart2_read(void *buf,unsigned int ulBufSize,unsigned int timeout);


typedef void (*usart_data_arrive_call_back_func)(unsigned char dat);
extern void reg_callback_usart0_data_arrive(usart_data_arrive_call_back_func pfunc);
extern void reg_callback_usart1_data_arrive(usart_data_arrive_call_back_func pfunc);
extern void reg_callback_usart2_data_arrive(usart_data_arrive_call_back_func pfunc);

extern void usart_rx_timing(unsigned char usart_channel);




#ifdef __cplusplus
}
#endif
#endif


