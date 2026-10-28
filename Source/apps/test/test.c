#include "test.h"

#define TEST_TASK0_ID  0
#define TEST_TASK1_ID  1
#define TEST_TASK2_ID  2
#define TEST_TASK3_ID  3
#define TEST_TASK4_ID  4
#define TEST_TASK5_ID  5
#define TEST_TASK6_ID  6
#define TEST_TASK7_ID  7



OS_STK test_task0_stk[256] = {0};
OS_STK test_task1_stk[256] = {0};

OS_STK test_task2_stk[256] = {0};
OS_STK test_task3_stk[256] = {0};


unsigned char test_buf0[256] = {0};
unsigned char test_buf1[512] = {0};
unsigned char test_buf2[2048] = {0};
unsigned char rtempbuf[2048] = {0};

unsigned int test_write_cnt[3] = {0};

void test_task0(void)
{
	unsigned int i = 0;
	char cuu_buf[128] = {0};
	unsigned int rlen = 0;

	init();

	DBG_Print(0,"test task0 start...\r\n");
	while (1)
	{
		for (i = 0; i < 2; i++)
		{
			memset(cuu_buf,0,sizeof(cuu_buf));
			rlen = ReadDBGUsart(i,cuu_buf,sizeof(cuu_buf),100);
			if (rlen)
			{
				DBG_Print(LEVEL0,"recv:\r\n%s\r\n",cuu_buf);
				DBG_PrintBuf(LEVEL0,"recv usart:\r\n",cuu_buf,rlen);
			
				analyze_usercmd(cuu_buf,rlen,0,0);

				if (strstr(cuu_buf,"txcan"))
				{
					unsigned int i = 0;
					DBG_Print(0,"send tx test.\r\n");
					for (i = 0; i < get_test_val(); i++)
					{
						can0_tx_msg(1,0,0,0x18FF0032,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
						//delayms(500);
						//can1_tx_msg(1,0,0,0x18FF0032,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
						//can2_tx_msg(1,0,0,0x18FF0032,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
						
						//can0_tx_msg(0,0,0,0x7DF,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
						//can1_tx_msg(0,0,0,0x7DF,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
						//can2_tx_msg(0,0,0,0x7DF,"\x11\x22\x33\x44\x55\x66\x77\x88",8);
					}
				}
			
			
			}

		}


		for (i = 0; i < 256; i++)
		{
			test_buf0[i] = i;
		}
		StoreOneData(0,test_buf0,sizeof(test_buf0));
		test_write_cnt[0]++;
		lfos_sleep(200);
	}
}

void test_task1(void)
{
	unsigned int i = 0;
	unsigned int cnt = 0;

	DBG_Print(0,"test task1 start...\r\n");
	while (1)
	{
		cnt++;
		for (i = 0; i < 128; i++)
		{
			test_buf1[i * 4 + 0] = cnt >> 24;
			test_buf1[i * 4 + 1] = cnt >> 16;
			test_buf1[i * 4 + 2] = cnt >> 8;
			test_buf1[i * 4 + 3] = cnt;
		}
		StoreOneData(1,test_buf1,sizeof(test_buf1));
		test_write_cnt[1]++;
		lfos_sleep(300);
	}
}
void test_task2(void)
{
	unsigned char cnt = 0;

	DBG_Print(0,"test task2 start...\r\n");

	while (1)
	{
		cnt++;
		memset(test_buf2,cnt,sizeof(test_buf2));
		StoreOneData(2,test_buf2,sizeof(test_buf2));
		test_write_cnt[2]++;
		lfos_sleep(300);
	}
}

void test_task3(void)
{
	unsigned int i = 0;
	unsigned int temp = 0;
	unsigned int dat = 0;
	unsigned int read_cnt = 0;
	unsigned int rdat[3] = {0};

	DBG_Print(0,"test task3 start...\r\n");
	while (1)
	{
		//读出数据库2里面的数据 判断是否有错误
		if (ReadOneData(2,rtempbuf,sizeof(rtempbuf)) == 0)
		{
			ReadOneDataOk(2);
			rdat[2] = rtempbuf[0];
			for (i = 1; i < 2048; i++)
			{
				if (rtempbuf[i] != rtempbuf[0])
				{
					DBG_PrintBuf(0,"Block 2 err:\r\n",rtempbuf,2048);
					break;
				}
			}
		}
		
		//读出数据库1里面的数据 判断是否有错误
		if (ReadOneData(1,rtempbuf,sizeof(rtempbuf)) == 0)
		{
			ReadOneDataOk(1);
			dat = (rtempbuf[0] << 24) + (rtempbuf[1] << 16) + 
			(rtempbuf[2] << 8) + rtempbuf[3];
			rdat[1] = dat;
			for (i = 0; i < 128; i++)
			{
				temp = (rtempbuf[i * 4 + 0] << 24) + (rtempbuf[i * 4 + 1] << 16) + 
				(rtempbuf[i * 4 + 2] << 8) + rtempbuf[i * 4 + 3];
				if (temp != dat)
				{
					DBG_PrintBuf(0,"Block 1 err:\r\n",rtempbuf,512);
					break;
				}
			}
		}

		//读出数据库0里面的数据 判断是否有错误
		rdat[0] = 0;
		if (ReadOneData(0,rtempbuf,sizeof(rtempbuf)) == 0)
		{
			ReadOneDataOk(0);
			for (i = 0; i < 256; i++)
			{
				rdat[0] += rtempbuf[i];
				if (rtempbuf[i] != i)
				{
					DBG_PrintBuf(0,"Block 0 err:\r\n",rtempbuf,256);
					break;
				}
			}
		}
		read_cnt++;

		DBG_Print(0,"data:%u(the sum of 0-255) %u(increase) %u(loop from 0 to 255)\r\n"
		"write flash cnt:%u %u %u read flash cnt:%u\r\n"
		"total can msgs:%u %u %u\r\n",
		rdat[0],rdat[1],rdat[2],
		test_write_cnt[0],test_write_cnt[1],test_write_cnt[2],read_cnt,
		can0_get_rx_total_msg_cnt(),can1_get_rx_total_msg_cnt(),can2_get_rx_total_msg_cnt());

		lfos_sleep(1000);
	}
}


void test_task4(void)
{
	DBG_Print(0,"test task4 start...\r\n");
	while (1)
	{
		lfos_sleep(1000);
	}
}


void test_start_os(void)
{
	lfos_init();
	lfos_create_thread(TEST_TASK0_ID,test_task0,&test_task0_stk[255],&test_task0_stk[0]);
	lfos_create_thread(TEST_TASK1_ID,test_task1,&test_task1_stk[255],&test_task1_stk[0]);

	lfos_create_thread(TEST_TASK2_ID,test_task2,&test_task2_stk[255],&test_task2_stk[0]);
	lfos_create_thread(TEST_TASK3_ID,test_task3,&test_task3_stk[255],&test_task3_stk[0]);

	lfos_start();
}
