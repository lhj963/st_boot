#include "lfos_cfg.h"
#include "lfos.h"




void lfos_thread_stack_init(OS_STK **sp,void *thread_proc)
{
	*(--(*sp)) = 0x01000000u;								//xPSR
	*(--(*sp)) = (OS_STK)thread_proc;						//entry point
	*(--(*sp)) = 0xEEEEEEEE;								//LR
	*(--(*sp)) = 0xCCCCCCCC;								//R12
	*(--(*sp)) = 0x33333333;								//R3
	*(--(*sp)) = 0x22222222;								//R2
	*(--(*sp)) = 0x11111111;								//R1
	*(--(*sp)) = 0x00000000;								//R0

	*(--(*sp)) = 0xBBBBBBBB;								//R11
	*(--(*sp)) = 0xAAAAAAAA;								//R10
	*(--(*sp)) = 0x99999999;								//R9
	*(--(*sp)) = 0x88888888;								//R8
	*(--(*sp)) = 0x77777777;								//R7
	*(--(*sp)) = 0x66666666;								//R6
	*(--(*sp)) = 0x55555555;								//R5
	*(--(*sp)) = 0x44444444;								//R4

}



















