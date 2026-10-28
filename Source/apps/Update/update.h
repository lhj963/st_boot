#ifndef __UPDATE_H__
#define __UPDATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ONE_SECTOR_SIZE				2048

/* Update info, OTA slot, param store, and MPU log addresses are the
 * driver's map in HardwareCfg.h. UpdateInfo layout is in boot_check.h. */


extern void monitor_xmodem(void *buf,unsigned int len);

extern void check_usart_update(void);

extern void check_remote_update(void);

extern void enter_update_mode(void);

extern char is_update_mode(void);

extern void delayms(unsigned long t);

extern unsigned char is_driver_file_by_usart(void);


#ifdef __cplusplus
}
#endif

#endif


