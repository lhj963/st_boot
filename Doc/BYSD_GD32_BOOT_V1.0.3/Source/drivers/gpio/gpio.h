#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif



extern void _gpio_init(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode);

extern void _gpio_init_pull_down(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode);

extern void _gpio_init_pull_up(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,char is_input_mode);


extern void pin_high(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx);

extern void pin_low(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx);



extern char pin_read_in(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx);


extern void _gpio_af(unsigned int rcc,GPIO_Type *gpio,PORT_Type *port,unsigned char pin_idx,unsigned char func_id);







#ifdef __cplusplus
}
#endif

#endif


