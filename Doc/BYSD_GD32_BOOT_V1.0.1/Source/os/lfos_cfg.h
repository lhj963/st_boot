#ifndef __LFOS_CFG_H__
#define __LFOS_CFG_H__
#ifdef __cplusplus
extern "C" {
#endif



#define MAX_THREAD_CNT 16

//线程最大占用TICK数 占用CPU超过MAX_THREAD_USE_TICK_CNT 将会被系统杀死
#define MAX_THREAD_USE_TICK_CNT  20000



typedef unsigned char INT8U;
typedef unsigned short INT16U;
typedef unsigned int INT32U;

typedef char INT8S;
typedef short INT16S;
typedef int INT32S;



typedef unsigned int OS_STK;







#ifdef __cplusplus
}
#endif


#endif

