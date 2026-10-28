#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif


extern void adc_init(ADC_Type *adc,unsigned int rcc,PORT_Type *port,unsigned char pin_idx);
extern unsigned int adc_read_val(ADC_Type *adc,unsigned char channel);


extern void adc0_init(unsigned int rcc,PORT_Type * port,unsigned char pin_idx);
extern void adc1_init(unsigned int rcc,PORT_Type * port,unsigned char pin_idx);
extern unsigned int adc0_read_val(unsigned char channel);
extern unsigned int adc1_read_val(unsigned char channel);




extern unsigned char is_adc_error(void);
extern void clr_adc_error_flag(void);
extern unsigned char get_adc_error_ad_no(void);
extern unsigned char get_adc_error_channel(void);




#ifdef __cplusplus
}
#endif


#endif


