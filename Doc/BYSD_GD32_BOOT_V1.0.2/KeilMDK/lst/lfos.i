#line 1 "..\\Source\\os\\lfos.c"
#line 1 "..\\Source\\os\\lfos.h"







#line 1 "..\\Source\\os\\lfos_cfg.h"















typedef unsigned char INT8U;
typedef unsigned short INT16U;
typedef unsigned int INT32U;

typedef char INT8S;
typedef short INT16S;
typedef int INT32S;



typedef unsigned int OS_STK;














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







#line 2 "..\\Source\\os\\lfos.c"








typedef enum tagThreadStatus
{
	ThreadStatus_NO_CREATE = 0,		

	ThreadStatus_RDY,			
	ThreadStatus_RUN,			
	ThreadStatus_DLY,			

	ThreadStatus_PENDING,			

	ThreadStatus_BLOCK,			
	ThreadStatus_SUPEND, 		

}ThreadStatus;


typedef struct tagLFOS
{
	INT32U idle_ctr;			

	INT32U flag;				
}LFOS;


LFOS g_os = {0};
LFOSThread osthread[16 + 1] = {0};
LFOSThread *pCurThread = 0;
LFOSThread *pHighThread = 0;



INT8U cur_thread_id = 0;		
INT8U rdy_high_id = 0;			

INT32U rdy_tbl = 0;				
INT8U int_nest_ctr;				


OS_STK sys_thread_stk[64] = {0};

OS_STK *lfos_get_sys_thread_stk_ptr(void)
{
	return sys_thread_stk;
}

LFOSThread *lfos_get_thread_ptr(INT8U thread_id)
{
	if (thread_id > 16) return 0;

	return osthread + thread_id;
}

unsigned char find_ready_thread_id(void)
{
	INT8U i = 0;

	for (i = 0; i < 16; i++)
	{
		if (rdy_tbl & (1 << i))
		{
			return i;
		}
	}

	return 16;
}

INT16U lfos_get_version(void)
{
	return 102;
}

extern void triger_pendsv(void);

void sched(void)
{
	
	

	rdy_high_id = find_ready_thread_id();
	if (rdy_high_id == cur_thread_id)
	{
		cpu_int_en();
		return ;
	}

	
	
	pCurThread = osthread + cur_thread_id;
	pHighThread = osthread + rdy_high_id;
	osthread[cur_thread_id].use_cpu_tick = 0;
	osthread[rdy_high_id].status = ThreadStatus_RUN;
	cur_thread_id = rdy_high_id;
	cpu_int_en();
	context_sw();
}


void sched_int(void)
{
	
	
	rdy_high_id = find_ready_thread_id();
	if (rdy_high_id == cur_thread_id)
	{
		cpu_int_en();
		return ;
	}

	
	
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
	if (thread_id > 16) return 0;

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
	if (thread_id > 16) return 0;

	return osthread[thread_id].stack_freed;
}

void lfos_sleep(unsigned int t)
{
	cpu_int_dis();
	rdy_tbl &= (~(1 << cur_thread_id));
	osthread[cur_thread_id].status = (INT8U)ThreadStatus_DLY;
	osthread[cur_thread_id].dly_tick = t;

	sched();
}

void lfos_tick(void)
{
	INT8U i = 0;

	for (i = 0; i < 16; i++)
	{
		if (osthread[i].status == ThreadStatus_DLY)
		{
			if (osthread[i].dly_tick)
			{
				osthread[i].dly_tick--;
			}
			else
			{
				osthread[i].status = ThreadStatus_RDY;			
				rdy_tbl |= (1 << i);
			}
		}
		else if (osthread[i].status == ThreadStatus_PENDING)
		{
			if (osthread[i].pSem)
			{
				if (osthread[i].pSem->sem_cnt)
				{
					osthread[i].status = ThreadStatus_RDY;		
					rdy_tbl |= (1 << i);
					osthread[i].pSem->sem_cnt--;
					osthread[i].pSem = 0;
				}
				else if (osthread[i].pSem->timeout)
				{
					osthread[i].pSem->timeout--;
					if (osthread[i].pSem->timeout == 0)				
					{
						osthread[i].status = ThreadStatus_RDY;		
						rdy_tbl |= (1 << i);
						osthread[i].pSem = 0;
					}
				}

			}
		}
		else if (osthread[i].status == ThreadStatus_BLOCK)
		{

		}
#line 233 "..\\Source\\os\\lfos.c"
		
		if (osthread[i].status != ThreadStatus_RUN)
		{
			osthread[i].use_cpu_tick = 0;
		}

	}

	
	{
		
	}
}






int lfos_create_thread(INT8U thread_id,void (*thread_proc)(void),
								OS_STK *sp,OS_STK *bottom)
{
	if (thread_id > 16) return 1;

	
	if (osthread[thread_id].sp || osthread[thread_id].sp_init_ptr || osthread[thread_id].bottom)
	{
		return 2;
	}

	osthread[thread_id].dly_tick = 0;
	osthread[thread_id].sp_init_ptr = sp;
	osthread[thread_id].sp = sp;
	osthread[thread_id].bottom = bottom;
	osthread[thread_id].status = ThreadStatus_RDY;
	rdy_tbl |= (1 << thread_id);
	if (sp > bottom)
	{
		g_os . flag |= (1 << 0);
	}
	else
	{
		g_os . flag &= (~(1 << 0));
	}

	lfos_thread_stack_init(&osthread[thread_id].sp,thread_proc);
	return 0;
}

void check_stack_used(void)
{
	INT8U i = 0;
	OS_STK *pstk = 0;
	INT32U freed = 0;

	for (i = 0; i <= 16; i++)
	{
		if (osthread[i].sp_init_ptr)	
		{
			pstk = osthread[i].bottom;
			freed = 0;
			if (osthread[i].bottom > osthread[i].sp_init_ptr)	
			{
				while (*pstk == 0)
				{
					freed++;
					pstk--;
				}
			}
			else												
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
	if ((g_os . flag & (1 << 0)))
	{
		lfos_create_thread(16,sys_thread,&sys_thread_stk[64 - 1],&sys_thread_stk[0]);
	}
	else
	{
		lfos_create_thread(16,sys_thread,&sys_thread_stk[0],&sys_thread_stk[64 - 1]);
	}

	rdy_high_id = find_ready_thread_id();
	cur_thread_id = rdy_high_id;
	pCurThread = osthread + rdy_high_id;
	pHighThread = osthread + rdy_high_id;
	start_thread();
}


 

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

	
	if (pSem->sem_cnt)
	{
		pSem->sem_cnt--;
		return 0;
	}

	
	if (timeout == (INT32U)-1)
	{
		return 0;
	}
	cpu_int_dis();
	pSem->timeout = timeout;
	osthread[cur_thread_id].pSem = pSem;
	osthread[cur_thread_id].status = ThreadStatus_PENDING;
	rdy_tbl &= (~(1 << cur_thread_id));
	sched();
	return 2;
}

int lfos_sem_post(LFOS_SEM *pSem)
{
	if (pSem == 0) return 1;
	pSem->sem_cnt++;
	return 0;
}



 

typedef struct tagLFOS_MEM
{
	INT8U *ptr;
	INT32U block_size;
	INT32U block_cnt;
	INT32U used_tbl;
}LFOS_MEM;



LFOS_MEM s_astLFOS_MEM[8] = {0};


int lfos_create_mem(INT8U mem_lib_id,void *ptr,INT32U block_size,INT32U block_cnt)
{
	if (mem_lib_id >= 8)
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

	if (mem_lib_id >= 8)
	{
		return 0;
	}

	
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
		s_astLFOS_MEM[mem_lib_id]. used_tbl |= (1 << i);
		return (void *)(s_astLFOS_MEM[mem_lib_id].ptr + i * s_astLFOS_MEM[mem_lib_id].block_size);
	}
}

int lfos_mem_free(INT8U mem_lib_id,void *ptr)
{
	INT32U num = 0;
	INT32U idx = 0;

	if (mem_lib_id >= 8)
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

	
	s_astLFOS_MEM[mem_lib_id]. used_tbl &= (~(1 << idx));

	return 0;
}

unsigned int lfos_mem_get_block_size(INT8U mem_lib_id)
{
	return s_astLFOS_MEM[mem_lib_id].block_size;
}













