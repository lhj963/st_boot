#ifndef __UPDATE_H__
#define __UPDATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ONE_SECTOR_SIZE				2048

/* 12KB..16KB, after the 12KB scatter image and before the driver at 16KB.
 * Record layout (magic, packed fields, header CRC) is UpdateInfo in boot_check.h. */
#define	UPDATE_INFO_START_SECTOR	0
#define UPDATE_INFO_SECTOR_CNT      1
#define UPDATE_INFO_START_ADDR		(0x08000000 + (12 * 1024))


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


