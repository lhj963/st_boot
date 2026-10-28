#line 1 "..\\Source\\os\\cpu_c.c"
#line 1 "..\\Source\\os\\lfos_cfg.h"















typedef unsigned char INT8U;
typedef unsigned short INT16U;
typedef unsigned int INT32U;

typedef char INT8S;
typedef short INT16S;
typedef int INT32S;



typedef unsigned int OS_STK;














#line 2 "..\\Source\\os\\cpu_c.c"
#line 1 "..\\Source\\os\\lfos.h"







#line 9 "..\\Source\\os\\lfos.h"



typedef struct tagLFOS_SEM
{
	void *pName;	
	INT8U sem_cnt;	
	INT32U timeout;
}LFOS_SEM;

typedef struct tagLFOSThread
{
	OS_STK *sp;				
	OS_STK *bottom;			
	OS_STK *sp_init_ptr;	
	INT32U stack_freed;		

	INT8U status;			
	INT32U dly_tick;		
	INT32U use_cpu_tick;	
	LFOS_SEM *pSem;			

}LFOSThread;


extern void cpu_int_en(void);
extern void cpu_int_dis(void);
extern void start_thread(void);
extern void context_sw(void);
extern void context_sw_int(void);
extern void lfos_thread_stack_init(OS_STK **sp,void *thread_proc);

extern LFOSThread *pCurThread;
extern LFOSThread *pHighThread;




extern LFOSThread *lfos_get_thread_ptr(INT8U thread_id);
extern OS_STK *lfos_get_sys_thread_stk_ptr(void);



extern void lfos_tick(void);
extern void lfos_enter_int(void);
extern void lfos_exit_int(void);



extern void lfos_init(void);
extern int lfos_create_thread(INT8U thread_id,void (*thread_proc)(void),
								OS_STK *sp,OS_STK *bottom);
extern void lfos_start(void);
extern void lfos_sleep(unsigned int t);
extern INT32U lfos_stack_used(unsigned char thread_id);
extern INT32U lfos_stack_freed(unsigned char thread_id);
extern INT16U lfos_get_version(void);



extern int lfos_create_sem(LFOS_SEM *pSem,void *pName,INT8U cnt);
extern int lfos_sem_pend(LFOS_SEM *pSem,INT32U timeout);
extern int lfos_sem_post(LFOS_SEM *pSem);



extern int lfos_create_mem(INT8U mem_lib_id,void *ptr,INT32U block_size,INT32U block_cnt);
extern void *lfos_mem_malloc(INT8U mem_lib_id);
extern int lfos_mem_free(INT8U mem_lib_id,void *ptr);
extern unsigned int lfos_mem_get_block_size(INT8U mem_lib_id);







#line 3 "..\\Source\\os\\cpu_c.c"




void lfos_thread_stack_init(OS_STK **sp,void *thread_proc)
{
	*(--(*sp)) = 0x01000000u;								
	*(--(*sp)) = (OS_STK)thread_proc;						
	*(--(*sp)) = 0xEEEEEEEE;								
	*(--(*sp)) = 0xCCCCCCCC;								
	*(--(*sp)) = 0x33333333;								
	*(--(*sp)) = 0x22222222;								
	*(--(*sp)) = 0x11111111;								
	*(--(*sp)) = 0x00000000;								

	*(--(*sp)) = 0xBBBBBBBB;								
	*(--(*sp)) = 0xAAAAAAAA;								
	*(--(*sp)) = 0x99999999;								
	*(--(*sp)) = 0x88888888;								
	*(--(*sp)) = 0x77777777;								
	*(--(*sp)) = 0x66666666;								
	*(--(*sp)) = 0x55555555;								
	*(--(*sp)) = 0x44444444;								

}



















