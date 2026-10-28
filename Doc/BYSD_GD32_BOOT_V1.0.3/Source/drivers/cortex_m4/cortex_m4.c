#include "cortex_m4.h"


#define  DWT_CR      *(volatile unsigned int *)0xE0001000
#define  DWT_CYCCNT  *(volatile unsigned int *)0xE0001004
#define  DEM_CR      *(volatile unsigned int *)0xE000EDFC
#define  DBGMCU_CR   *(volatile unsigned int *)0xE0042004

#define  DEM_CR_TRCENA                   (1 << 24)

#define  DWT_CR_CYCCNTENA                (1 <<  0)



void cpu_ts_init(void)
{
    DEM_CR         |= (unsigned int)DEM_CR_TRCENA;                /* Enable Cortex-M4's DWT CYCCNT reg.                   */
    DWT_CYCCNT      = (unsigned int)0u;
    DWT_CR         |= (unsigned int)DWT_CR_CYCCNTENA;
}


unsigned int cpu_clock(void)
{
    return ((unsigned int)DWT_CYCCNT);
}












