#ifndef CLOCKS_AND_MODES_H_
#define CLOCKS_AND_MODES_H_

typedef enum CLOCK_CFG_ERR
{
	CLOCK_ERR_NONE = 0,			//无错误	
	CLOCK_ERR_WAIT_EXTERN_OSI,		//外部晶振错误
	CLOCK_ERR_WAIT_SPLL,				//SPLL错误
	CLOCK_ERR_WAIT_SYS_SRC,	//等待系统时钟挂接到时钟源上
		

}CLOCK_CFG_ERR;


extern void SOSC_init_interl(void);


void SOSC_init_8MHz (void);
void SPLL_init_160MHz (void);
void NormalRUNmode_80MHz (void);
void NormalRUNmode_48MHz (void);
void NormalRUNmode_40MHz(void);


void deinit_SPLL(void);
void deinit_SOSC(void);


extern void normal_run_mode_80mhz_for_8mhz(void);

extern void normal_run_mode_80mhz_for_12mhz(void);


extern void normal_run_mode_48mhz_for_firc(void);

extern void clock_out_pin(void);

extern void clock_hsrun_mode_for_8mhz(void);

extern CLOCK_CFG_ERR clock_hsrun_mode_for_12mhz(void);
extern CLOCK_CFG_ERR clock_run_mode_for_12mhz(void);


extern void view_clock_reg(void);


#endif /* CLOCKS_AND_MODES_H_ */

