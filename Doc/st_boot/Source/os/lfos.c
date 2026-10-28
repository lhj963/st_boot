#include "lfos.h"

#define LFOS_VERSION	102

#define _set_bit(x,y)   x |= (1 << y)
#define _clr_bit(x,y)   x &= (~(1 << y))
#define _get_bit(x,y)	(x & (1 << y))


typedef enum tagThreadStatus
{
	ThreadStatus_NO_CREATE = 0,		//未创建状态

	ThreadStatus_RDY,			//就绪态
	ThreadStatus_RUN,			//运行态
	ThreadStatus_DLY,			//延时态

	ThreadStatus_PENDING,			//等待信号

	ThreadStatus_BLOCK,			//阻塞态
	ThreadStatus_SUPEND, 		//挂起状态

}ThreadStatus;


typedef struct tagLFOS
{
	INT32U idle_ctr;			//空闲线程计数

	INT32U flag;				//标志
}LFOS;


LFOS g_os = {0};
LFOSThread osthread[MAX_THREAD_CNT + 1] = {0};
LFOSThread *pCurThread = 0;
LFOSThread *pHighThread = 0;



INT8U cur_thread_id = 0;		//当前运行的线程ID
INT8U rdy_high_id = 0;			//就绪的高优先级线程ID

INT32U rdy_tbl = 0;				//每个位代表每个线程状态是否就绪
INT8U int_nest_ctr;				//中断嵌套计数


OS_STK sys_thread_stk[SYS_THREAD_STK_SIZE] = {0};

OS_STK *lfos_get_sys_thread_stk_ptr(void)
{
	return sys_thread_stk;
}

LFOSThread *lfos_get_thread_ptr(INT8U thread_id)
{
	if (thread_id > MAX_THREAD_CNT) return 0;

	return osthread + thread_id;
}

unsigned char find_ready_thread_id(void)
{
	INT8U i = 0;

	for (i = 0; i < MAX_THREAD_CNT; i++)
	{
		if (rdy_tbl & (1 << i))
		{
			return i;
		}
	}

	return MAX_THREAD_CNT;
}

INT16U lfos_get_version(void)
{
	return LFOS_VERSION;
}

extern void triger_pendsv(void);
//进行一次任务调度
void sched(void)
{
	//关中断
	//cpu_int_dis();

	rdy_high_id = find_ready_thread_id();
	if (rdy_high_id == cur_thread_id)
	{
		cpu_int_en();
		return ;
	}

	//关中断
	//cpu_int_dis();
	pCurThread = osthread + cur_thread_id;
	pHighThread = osthread + rdy_high_id;
	osthread[cur_thread_id].use_cpu_tick = 0;
	osthread[rdy_high_id].status = ThreadStatus_RUN;
	cur_thread_id = rdy_high_id;
	cpu_int_en();
	context_sw();
}

//进行一次任务调度
void sched_int(void)
{
	//关中断
	//cpu_int_dis();
	rdy_high_id = find_ready_thread_id();
	if (rdy_high_id == cur_thread_id)
	{
		cpu_int_en();
		return ;
	}

	//关中断
	//cpu_int_dis();
	pCurThread = osthread + cur_thread_id;
	pHighThread = osthread + rdy_high_id;
	osthread[cur_thread_id].use_cpu_tick = 0;
	osthread[rdy_high_id].status = ThreadStatus_RUN;
	cur_thread_id = rdy_high_id;
	cpu_int_en();
	context_sw_int();
}

void lfos_enter_int(void)
{
	if (int_nest_ctr < 250) int_nest_ctr++;
}

void lfos_exit_int(void)
{
	if (int_nest_ctr) int_nest_ctr--;
}

INT32U lfos_stack_used(unsigned char thread_id)
{
	INT32U all = 0;
	if (thread_id > MAX_THREAD_CNT) return 0;

	if (osthread[thread_id].sp_init_ptr > osthread[thread_id].bottom)
	{
		all = osthread[thread_id].sp_init_ptr - osthread[thread_id].bottom + 1;
	}
	else
	{
		all = osthread[thread_id].bottom - osthread[thread_id].sp_init_ptr + 1;
	}

	return all - osthread[thread_id].stack_freed;
}

INT32U lfos_stack_freed(unsigned char thread_id)
{
	if (thread_id > MAX_THREAD_CNT) return 0;

	return osthread[thread_id].stack_freed;
}

void lfos_sleep(unsigned int t)
{
	cpu_int_dis();
	_clr_bit(rdy_tbl,cur_thread_id);
	osthread[cur_thread_id].status = (INT8U)ThreadStatus_DLY;
	osthread[cur_thread_id].dly_tick = t;

	sched();
}

void lfos_tick(void)
{
	INT8U i = 0;

	for (i = 0; i < MAX_THREAD_CNT; i++)
	{
		if (osthread[i].status == ThreadStatus_DLY)
		{
			if (osthread[i].dly_tick)
			{
				osthread[i].dly_tick--;
			}
			else
			{
				osthread[i].status = ThreadStatus_RDY;			//就绪态
				_set_bit(rdy_tbl,i);
			}
		}
		else if (osthread[i].status == ThreadStatus_PENDING)
		{
			if (osthread[i].pSem)
			{
				if (osthread[i].pSem->sem_cnt)
				{
					osthread[i].status = ThreadStatus_RDY;		//就绪态
					_set_bit(rdy_tbl,i);
					osthread[i].pSem->sem_cnt--;
					osthread[i].pSem = 0;
				}
				else if (osthread[i].pSem->timeout)
				{
					osthread[i].pSem->timeout--;
					if (osthread[i].pSem->timeout == 0)				//等待超时
					{
						osthread[i].status = ThreadStatus_RDY;		//就绪态
						_set_bit(rdy_tbl,i);
						osthread[i].pSem = 0;
					}
				}

			}
		}
		else if (osthread[i].status == ThreadStatus_BLOCK)
		{

		}
		#if 0
		else if (osthread[i].status == ThreadStatus_RUN)
		{
			osthread[i].use_cpu_tick++;
			//该线程占用CPU时间太多 杀死该线程
			if (osthread[i].use_cpu_tick > MAX_THREAD_USE_TICK_CNT)
			{
				osthread[i].status = ThreadStatus_SUPEND;
				_clr_bit(rdy_tbl,i);
				sched_int();
			}
		}
		#endif
		//清除占用CPU时间计时器
		if (osthread[i].status != ThreadStatus_RUN)
		{
			osthread[i].use_cpu_tick = 0;
		}

	}

	//if (sched_flag)
	{
		//sched_int();
	}
}

#define SET_STACK_HI_TO_LOW()	_set_bit(g_os.flag,0)
#define SET_STACK_LOW_TO_HI()   _clr_bit(g_os.flag,0)
#define IS_STACK_HI_TO_LOW()	_get_bit(g_os.flag,0)


int lfos_create_thread(INT8U thread_id,void (*thread_proc)(void),
								OS_STK *sp,OS_STK *bottom)
{
	if (thread_id > MAX_THREAD_CNT) return 1;

	//检查该thread_id是否有线程存在 有线程存在 则不能创建该线程
	if (osthread[thread_id].sp || osthread[thread_id].sp_init_ptr || osthread[thread_id].bottom)
	{
		return 2;
	}

	osthread[thread_id].dly_tick = 0;
	osthread[thread_id].sp_init_ptr = sp;
	osthread[thread_id].sp = sp;
	osthread[thread_id].bottom = bottom;
	osthread[thread_id].status = ThreadStatus_RDY;
	_set_bit(rdy_tbl,thread_id);
	if (sp > bottom)
	{
		SET_STACK_HI_TO_LOW();
	}
	else
	{
		SET_STACK_LOW_TO_HI();
	}

	lfos_thread_stack_init(&osthread[thread_id].sp,thread_proc);
	return 0;
}

void check_stack_used(void)
{
	INT8U i = 0;
	OS_STK *pstk = 0;
	INT32U freed = 0;

	for (i = 0; i <= MAX_THREAD_CNT; i++)
	{
		if (osthread[i].sp_init_ptr)	//osthread[i].sp_init_ptr不等于0表示该线程ID被创建
		{
			pstk = osthread[i].bottom;
			freed = 0;
			if (osthread[i].bottom > osthread[i].sp_init_ptr)	//堆栈由低向高生长
			{
				while (*pstk == 0)
				{
					freed++;
					pstk--;
				}
			}
			else												//堆栈由高向低生长
			{
				while (*pstk == 0)
				{
					freed++;
					pstk++;
				}
			}
			osthread[i].stack_freed = freed;
		}
	}
}

void sys_thread(void)
{
	while (1)
	{
		//check_stack_used();
		g_os.idle_ctr++;
		sched();
	}
}

void lfos_init(void)
{
	g_os.flag = 0;
	g_os.idle_ctr = 0;

	pCurThread = 0;
	pHighThread = 0;
	rdy_tbl = 0;
	rdy_high_id = 0;
	cur_thread_id = 0;
}



void lfos_start(void)
{
	if (IS_STACK_HI_TO_LOW())
	{
		lfos_create_thread(MAX_THREAD_CNT,sys_thread,&sys_thread_stk[SYS_THREAD_STK_SIZE - 1],&sys_thread_stk[0]);
	}
	else
	{
		lfos_create_thread(MAX_THREAD_CNT,sys_thread,&sys_thread_stk[0],&sys_thread_stk[SYS_THREAD_STK_SIZE - 1]);
	}

	rdy_high_id = find_ready_thread_id();
	cur_thread_id = rdy_high_id;
	pCurThread = osthread + rdy_high_id;
	pHighThread = osthread + rdy_high_id;
	start_thread();
}


/*********************************信号量SEM*********************************/

int lfos_create_sem(LFOS_SEM *pSem,void *pName,INT8U cnt)
{
	if (pSem == 0)
	{
		return 1;
	}

	pSem->pName = pName;
	pSem->sem_cnt = cnt;
	return 0;
}

int lfos_sem_pend(LFOS_SEM *pSem,INT32U timeout)
{
	if (pSem == 0) return 1;

	//存在可用的信号量 直接退出 否则就进入等待状态 让出CPU使用权
	if (pSem->sem_cnt)
	{
		pSem->sem_cnt--;
		return 0;
	}

	//timeout为-1 表示不进行阻塞
	if (timeout == (INT32U)-1)
	{
		return 0;
	}
	cpu_int_dis();
	pSem->timeout = timeout;
	osthread[cur_thread_id].pSem = pSem;
	osthread[cur_thread_id].status = ThreadStatus_PENDING;
	_clr_bit(rdy_tbl,cur_thread_id);
	sched();
	return 2;
}

int lfos_sem_post(LFOS_SEM *pSem)
{
	if (pSem == 0) return 1;
	pSem->sem_cnt++;
	return 0;
}



/*********************************动态内存管理MEM*********************************/

typedef struct tagLFOS_MEM
{
	INT8U *ptr;
	INT32U block_size;
	INT32U block_cnt;
	INT32U used_tbl;
}LFOS_MEM;

#define MAX_MEM_LIB_CNT 8

LFOS_MEM s_astLFOS_MEM[MAX_MEM_LIB_CNT] = {0};

//mem_lib_id:内存库ID
int lfos_create_mem(INT8U mem_lib_id,void *ptr,INT32U block_size,INT32U block_cnt)
{
	if (mem_lib_id >= MAX_MEM_LIB_CNT)
	{
		return 1;
	}

	if ((ptr == 0) || (block_cnt == 0) || (block_size == 0)) return 2;

	if (block_cnt > 32) block_cnt = 32;

	s_astLFOS_MEM[mem_lib_id].ptr = (INT8U *)ptr;
	s_astLFOS_MEM[mem_lib_id].block_size = block_size;
	s_astLFOS_MEM[mem_lib_id].block_cnt = block_cnt;
	s_astLFOS_MEM[mem_lib_id].used_tbl = 0;
	return 0;
}


void *lfos_mem_malloc(INT8U mem_lib_id)
{
	INT8U i = 0;
	INT32U cnt = 0;

	if (mem_lib_id >= MAX_MEM_LIB_CNT)
	{
		return 0;
	}

	//查找空闲内存块
	cnt = s_astLFOS_MEM[mem_lib_id].block_cnt;

	for (i = 0; i < cnt; i++)
	{
		if ((s_astLFOS_MEM[mem_lib_id].used_tbl & (1 << i)) == 0)
		{
			break;
		}
	}

	if (i >= cnt)
	{
		return 0;
	}
	else
	{
		_set_bit(s_astLFOS_MEM[mem_lib_id].used_tbl,i);
		return (void *)(s_astLFOS_MEM[mem_lib_id].ptr + i * s_astLFOS_MEM[mem_lib_id].block_size);
	}
}

int lfos_mem_free(INT8U mem_lib_id,void *ptr)
{
	INT32U num = 0;
	INT32U idx = 0;

	if (mem_lib_id >= MAX_MEM_LIB_CNT)
	{
		return 1;
	}
	if (ptr == 0)
	{
		return 2;
	}

	num = (INT8U *)ptr - s_astLFOS_MEM[mem_lib_id].ptr;
	if (num % s_astLFOS_MEM[mem_lib_id].block_size)
	{
		return 3;
	}
	idx = num / s_astLFOS_MEM[mem_lib_id].block_size;
	if (idx >= s_astLFOS_MEM[mem_lib_id].block_cnt)
	{
		return 4;
	}

	//清除使用标志
	_clr_bit(s_astLFOS_MEM[mem_lib_id].used_tbl,idx);

	return 0;
}

unsigned int lfos_mem_get_block_size(INT8U mem_lib_id)
{
	return s_astLFOS_MEM[mem_lib_id].block_size;
}













