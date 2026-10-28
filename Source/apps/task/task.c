#include "task.h"



#define TASK0_ID  0
#define TASK1_ID  1
#define TASK2_ID  2
#define TASK3_ID  3
#define TASK4_ID  4
#define TASK5_ID  5
#define TASK6_ID  6
#define TASK7_ID  7



OS_STK task0_stk[256 + 64] = {0};
OS_STK task1_stk[256] = {0};

OS_STK task2_stk[256] = {0};


//主电 备用电池 相互转换检测处理
/* 50ms判断一次主电是否掉电（通过主电AD检测），
//是 打开备用电池（IO口EN_3V3_MCU，PE12）
//同时打开EC20供电（IO口EN_EC20_BAT，PE9） 关闭锂电池充电（IO口为EN_BAT，PE7）
*/
void dc_bat_switch_proc(void)
{
	static INT8U s_main_off_cnt = 0;	//连续检测到主电掉电次数
	static INT8U s_main_on_cnt = 0;		//连续检测到主电通电次数
	static INT8U s_dc_bat_status = 0;	//0表示主电供电 1表示电池供电
	unsigned int dc_power = 0;

	dc_power = read_main_power_vol();

	if (s_dc_bat_status == 0)
	{
		//当前主电供电 就监测掉电情况
		if (dc_power < 8500)
		{
			s_main_off_cnt++;
		}
		else
		{
			s_main_off_cnt = 0;
		}
		if (s_main_off_cnt >= 2)
		{
			//掉电切换
			s_main_off_cnt = 0;
			s_dc_bat_status = 1;

			switch_to_bat();
		}
	}
	else
	{
		//当前电池供电 就监测上电情况
		if (dc_power < 8500)
		{
			s_main_on_cnt = 0;
		}
		else
		{
			s_main_on_cnt++;
		}

		if (s_main_on_cnt >= 100)
		{
			//上电切换
			s_main_on_cnt = 0;
			s_dc_bat_status = 0;
			switch_to_dc();
		}

	}
}



void store_tcdata(void *pdat,unsigned int len)
{
	//tc.len = len;
	//memcpy(tc.buf,pdat,len);
	//StoreOneData(3,&tc,sizeof(tc));

	//store_fast_write(3,write_offset,pdat,len);
	//write_offset += len;
}

void send_tcdata(void)
{
	//store_fast_read(3,read_offset,100,void * pdat,unsigned int datlen)
}

unsigned char zm_tempbuf[12 * 1024] = {0};

void task1(void)
{
	char sled = 0;
	char sled1 = 0;
	char sled2 = 0;
	char sled3 = 0;
	unsigned int cnt = 0;
	unsigned int temp = 0;

	unsigned int a = 0;
	unsigned int b = 0;

	CanRxMsg rxmsg;
	unsigned char *ptr = 0;
	unsigned int rlen = 0;

	//check_usart_update();

	DBG_Print(0,"task1 start...\r\n");

	while (1)
	{
		if (rlen = get_zmode_rx_cnt())
		{
			//ptr = lfos_mem_malloc(0);

			//rlen = read_zmode_uart(zm_tempbuf,sizeof(zm_tempbuf));
			
			ptr = get_zmode_usart_buf_ptr();
			memcpy(zm_tempbuf,ptr,rlen);
			if (rlen && is_mdm_dbg_mode())
			{
				//DBG_Print(0,"rlen:%u\r\n",rlen);
				//先存起来
				//store_tcdata(ptr,rlen);
				send_to_mdm_dbg(zm_tempbuf,rlen);
			}
			//lfos_mem_free(0,ptr);
		}
		
		if (get_usart1_recv_cnt())
		{
			ptr = lfos_mem_malloc(0);
			temp = usart1_read(ptr,lfos_mem_get_block_size(0),1000);
			if (temp)
			{
				DBG_Print(LEVEL_GPRS,"%s\r\n",ptr);
			}
			lfos_mem_free(0,ptr);
		}

		if (get_mdm_dbg_uart_recv_cnt())
		{
			ptr = lfos_mem_malloc(0);
			temp = read_mdm_dbg_uart(ptr,lfos_mem_get_block_size(0));
			if (temp)
			{
				//DBG_Print(0,"%s\r\n",ptr);
				DBG_SendData(ptr,temp);
			}
			lfos_mem_free(0,ptr);
		}

		if (get_gps_uart_recv_cnt())
		{
			ptr = lfos_mem_malloc(0);
			temp = read_gps_uart(ptr,lfos_mem_get_block_size(0));
			if (temp)
			{
				DBG_Print(LEVEL_GPS,"%s\r\n",ptr);			
			}
			lfos_mem_free(0,ptr);

		}

		cnt++;
		if (cnt >= 1000)
		{
			cnt = 0;
			set_data_led(sled3);
			sled3 = !sled3;

		}

		lfos_sleep(1);

	}
}


unsigned char cuu_buf[2048+128] = {0};

void task0(void)
{
	unsigned int i = 0;
	unsigned int rlen = 0;
	
	unsigned int cnt = 0;
	char tx_mdm_dbg_flag = 0;		//透传MDM DBG串口模式

	init();
	init_later();

	set_mdm_dbg_mode(1);

	while (1)
	{
		for (i = 0; i < 2; i++)
		{
			rlen = ReadDBGUsart(i,cuu_buf,sizeof(cuu_buf),10);
			if (rlen)
			{
				DBG_Print(LEVEL2,"recv(%d):\r\n%s\r\n",rlen,cuu_buf);
				//DBG_PrintBuf(LEVEL4,"recv usart:\r\n",cuu_buf,rlen);
				analyze_usercmd(cuu_buf,rlen,0,0);
			}

		}

		cnt++;
		if (cnt >= 50)
		{
			unsigned int a = 0;
			unsigned int b = 0;
			unsigned int bat_power = 0;

			//usart1_send_data("AT\r\n",4);
			//DBG_Print(0,"send at\r\n");

			cnt = 0;
			a = cpu_clock();
			bat_power = read_bat_vol();
			b = cpu_clock();
			DBG_Print(LEVEL3,"read bat(%umv) take times:%u %uus\r\n",bat_power,b - a,(b - a) / 111);

			bat_power = read_rtc_vol();
			DBG_Print(LEVEL3,"rtc vol:%umv gps ant:%umv\r\n",bat_power,read_gps_ant_vol());


			if (bat_power < 3900)
			{
				//open_bat_charge();
			}


		pcf8563_read_rtc();
		DBG_Print(LEVEL4,"<RTC:%04d-%02d-%02d %02d:%02d:%02d>\r\n",pcf8563_get_year()+2000,
		pcf8563_get_month(),pcf8563_get_day(),pcf8563_get_hour(),pcf8563_get_min(),
		pcf8563_get_sec());
		DBG_Print(LEVEL4,"can1msgcnt:%d can2msgcnt:%d can3msgcnt:%d\r\n"
		"[total can msg]:can1:%u can2:%u can3:%u\r\n",
		can0_get_rx_msg_cnt(),can1_get_rx_msg_cnt(),can2_get_rx_msg_cnt(),
		
		can0_get_rx_total_msg_cnt(),can1_get_rx_total_msg_cnt(),can2_get_rx_total_msg_cnt()
		);


		if (1)
		{
			OS_STK *pstk = lfos_get_sys_thread_stk_ptr();
			DBG_PrintBuf(LEVEL5,"sys stk:\r\n",pstk,SYS_THREAD_STK_SIZE * 4);
		}


		}


	}
}


void task2(void)
{
	char sled = 0;
	char sled1 = 0;
	char sled2 = 0;
	char sled3 = 0;
	unsigned int rlen = 0;
	unsigned char *ptr = 0;

	CanRxMsg rxmsg;

	DBG_Print(0,"task2 start...\r\n");
	while (1)
	{

		//write_can_msg_to_flash();
		while (can1_get_rx_msg_cnt())
		{
			can1_get_rx_msg(&rxmsg);
			//DBG_Print(0,"[CAN1]recv:STDID:%08X EXTID:%08X IDE:%d ",rxmsg.StdId,rxmsg.ExtId,rxmsg.IDE);
			//DBG_PrintBuf(0,"",rxmsg.Data,rxmsg.DLC);
			set_net_led(sled1);
			sled1 = !sled1;

		}

		while (can2_get_rx_msg_cnt())
		{
			can2_get_rx_msg(&rxmsg);
			//DBG_Print(0,"[CAN2]recv:STDID:%08X EXTID:%08X IDE:%d ",rxmsg.StdId,rxmsg.ExtId,rxmsg.IDE);
			//DBG_PrintBuf(0,"",rxmsg.Data,rxmsg.DLC);
			set_can_led(sled2);
			
			sled2 = !sled2;
		}

		lfos_sleep(10);
	}
}



#define BIG_MEM_BLOCK_SIZE  	2048
#define SMALL_MEM_BLOCK_SIZE  	512
#define MICRO_MEM_BLOCK_SIZE  	128

#define BIG_MEM_CNT    		1
#define SMALL_MEM_CNT    	1
#define MICRO_MEM_CNT    	1

unsigned char big_mem_buf[BIG_MEM_CNT][BIG_MEM_BLOCK_SIZE] = {0};
unsigned char small_mem_buf[SMALL_MEM_CNT][SMALL_MEM_BLOCK_SIZE] = {0};
unsigned char micro_mem_buf[MICRO_MEM_CNT][MICRO_MEM_BLOCK_SIZE] = {0};


void start_os(void)
{
	lfos_init();

	lfos_create_mem(0,big_mem_buf,BIG_MEM_BLOCK_SIZE,BIG_MEM_CNT);
	lfos_create_mem(1,small_mem_buf,SMALL_MEM_BLOCK_SIZE,SMALL_MEM_CNT);
	lfos_create_mem(2,micro_mem_buf,MICRO_MEM_BLOCK_SIZE,MICRO_MEM_CNT);

	lfos_create_thread(TASK0_ID,task0,&task0_stk[256 + 63],&task0_stk[0]);
	lfos_create_thread(TASK1_ID,task1,&task1_stk[255],&task1_stk[0]);
	lfos_create_thread(TASK2_ID,task2,&task2_stk[255],&task2_stk[0]);
	lfos_start();
}


