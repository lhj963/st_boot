#include "export_api.h"

unsigned int read_mdm_usart(void *buf,unsigned int ulBufSize,unsigned int ulTimeoutMs)
{
	return usart1_read(buf,ulBufSize,ulTimeoutMs);
}

unsigned int read_gps_usart(void *buf,unsigned int ulBufSize,unsigned int ulTimeoutMs)
{
	return 0;
}								

void mdm_usart_init(unsigned long bps,char iParity)
{
	usart1_init(bps,iParity);
}

void gps_usart_init(unsigned long bps,char iParity)
{

}

unsigned int write_mdm_usart(void *pdat,unsigned int len)
{
	return usart1_send_data(pdat,len);
}

unsigned int write_gps_usart(void *pdat,unsigned int len)
{
	return usart2_send_data(pdat,len);
}

void rsv(void)
{
	DBG_Print(0,"%s","功能建设中\r\n");
}

void * const api_func_address[] __attribute__((section(".ARM.__at_0x1000"))) = 
{
	DBG_Print,
	DBG_PrintBuf,
	Set_DBG_Level,
	ReadDBGUsart,

	lfos_create_thread,
	lfos_sleep,

	can0_init,
	can1_init,
	can2_init,

	can0_tx_msg,
	can1_tx_msg,
	can2_tx_msg,

	can0_get_rx_msg_cnt,
	can1_get_rx_msg_cnt,
	can2_get_rx_msg_cnt,

	can0_get_rx_msg,
	can1_get_rx_msg,
	can2_get_rx_msg,

	set_sys_led,
	set_can_led,
	set_net_led,

	mdm_power_on,
	mdm_power_off,

	gps_power_on,
	gps_power_off,

	read_mdm_usart,
	read_gps_usart,

	mdm_usart_init,
	gps_usart_init,

	write_mdm_usart,
	write_gps_usart,

	read_main_power_vol,
	read_bat_vol,

	install_acc_int,
	install_io1_int,
	install_io2_int,

	pcf8563_set_rtc,

	CreateStoreBlock,
	StoreOneData,
	ReadOneData,
	ReadOneData_Reverse,

	ReadOneDataOk,
	GetStoreBlockCap,
	GetStoreBlockUsed,
	GetStoreBlockFree,

	can0_set_filter,
	can1_set_filter,
	can2_set_filter,

	lfos_create_sem,
	lfos_sem_pend,
	lfos_sem_post,	
	lfos_create_mem,
	lfos_mem_malloc,
	lfos_mem_free,

	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv,
	rsv
};





