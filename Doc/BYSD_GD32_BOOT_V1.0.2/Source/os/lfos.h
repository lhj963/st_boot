#ifndef __LFOS_H__
#define __LFOS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lfos_cfg.h"

#define SYS_THREAD_STK_SIZE 	64

typedef struct tagLFOS_SEM
{
	void *pName;	//信号量名称
	INT8U sem_cnt;	//信号量数量
	INT32U timeout;
}LFOS_SEM;

typedef struct tagLFOSThread
{
	OS_STK *sp;				//栈顶指针
	OS_STK *bottom;			//栈底指针
	OS_STK *sp_init_ptr;	//堆顶初始指针
	INT32U stack_freed;		//空闲堆栈

	INT8U status;			//线程状态
	INT32U dly_tick;		//延时节拍
	INT32U use_cpu_tick;	//占用CPU的时间
	LFOS_SEM *pSem;			//信号量

}LFOSThread;

//需要移植的函数
extern void cpu_int_en(void);
extern void cpu_int_dis(void);
extern void start_thread(void);
extern void context_sw(void);
extern void context_sw_int(void);
extern void lfos_thread_stack_init(OS_STK **sp,void *thread_proc);

extern LFOSThread *pCurThread;
extern LFOSThread *pHighThread;



//调试相关的函数
extern LFOSThread *lfos_get_thread_ptr(INT8U thread_id);
extern OS_STK *lfos_get_sys_thread_stk_ptr(void);


//需要在中断里面调用的函数
extern void lfos_tick(void);
extern void lfos_enter_int(void);
extern void lfos_exit_int(void);


//API接口
extern void lfos_init(void);
extern int lfos_create_thread(INT8U thread_id,void (*thread_proc)(void),
								OS_STK *sp,OS_STK *bottom);
extern void lfos_start(void);
extern void lfos_sleep(unsigned int t);
extern INT32U lfos_stack_used(unsigned char thread_id);
extern INT32U lfos_stack_freed(unsigned char thread_id);
extern INT16U lfos_get_version(void);


//信号量
extern int lfos_create_sem(LFOS_SEM *pSem,void *pName,INT8U cnt);
extern int lfos_sem_pend(LFOS_SEM *pSem,INT32U timeout);
extern int lfos_sem_post(LFOS_SEM *pSem);


//mem_lib_id:内存库ID
extern int lfos_create_mem(INT8U mem_lib_id,void *ptr,INT32U block_size,INT32U block_cnt);
extern void *lfos_mem_malloc(INT8U mem_lib_id);
extern int lfos_mem_free(INT8U mem_lib_id,void *ptr);
extern unsigned int lfos_mem_get_block_size(INT8U mem_lib_id);

#ifdef __cplusplus
}
#endif

#endif

