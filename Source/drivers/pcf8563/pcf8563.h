#ifndef __PCF8563_H__
#define __PCF8563_H__

#ifdef __cplusplus
extern "C" {
#endif


extern void pcf8563_init(void);

extern void pcf8563_read_rtc(void);


extern unsigned char pcf8563_get_year(void);
extern unsigned char pcf8563_get_month(void);
extern unsigned char pcf8563_get_day(void);
extern unsigned char pcf8563_get_hour(void);
extern unsigned char pcf8563_get_min(void);
extern unsigned char pcf8563_get_sec(void);


extern void pcf8563_set_rtc(unsigned int year,unsigned char month,unsigned char day,
							unsigned char hour,unsigned char min,unsigned char sec);



#ifdef __cplusplus
}
#endif



#endif

