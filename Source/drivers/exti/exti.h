#ifndef __EXTI_H__
#define __EXTI_H__
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_EXTI_CNT			8



extern void exti_init(unsigned int rcc,GPIO_Type *gpio,
				PORT_Type *port,unsigned char pin_idx,void (*exti_handler)(void));
				











#ifdef __cplusplus
}
#endif

#endif


