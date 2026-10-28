#ifndef __LPTMR_H__
#define __LPTMR_H__

#ifdef __cplusplus

#endif



typedef void (*lptmr_handler_func)(void);

extern void lptmr_init(unsigned int us,lptmr_handler_func pfunc);


#ifdef __cplusplus

#endif

#endif

