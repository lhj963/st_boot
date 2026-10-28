#ifndef __HARDWARECFG_H__
#define __HARDWARECFG_H__
#ifdef __cplusplus
extern "C" {
#endif


#define BOOT_VERSION 	"BYSD_GD32_BOOT_V1.0.0"

//boot层
#define BOOT_START_ADDR 						0x08000000
#define BOOT_SIZE								(16 * 1024)
#define BOOT_END_ADDR 							(BOOT_START_ADDR + BOOT_SIZE)

//驱动层
#define DRIVER_START_ADDR 						BOOT_END_ADDR
#define DRIVER_SIZE								(48 * 1024)
#define DRIVER_END_ADDR 						(DRIVER_START_ADDR + DRIVER_SIZE)

//app层
#define APP_START_ADDR 							DRIVER_END_ADDR
#define APP_END_ADDR 							(0x08000000 + 0x00060000)



#define SOFTWARE_INFO_OFFSET					0x1000
#define APP_SOFTWARE_INFO_OFFSET				0x1000

#define SOFTWARE_INFO_ADDR 						(BOOT_START_ADDR + SOFTWARE_INFO_OFFSET)

#define MANUFACTURER_FLAG       				"BYSD"				//厂商标识
#define LF_DRIVER_FILE_FLAG						"BYSD_DRIVER"		//驱动文件标识
#define LF_DRIVER_FILE_FLAG1 					0x11223344			//驱动文件标识
#define LF_DRIVER_FILE_FLAG1_OFFSET 			40					//驱动文件标识偏移地址



#define LED0_RCC								RCC_APB2Periph_GPIOB
#define LED0_PORT								GPIOB
#define LED0_PIN								GPIO_Pin_12
#define LED0_PIN_MODE							GPIO_Mode_Out_PP




extern void gpio_init(void);

extern void delayms_by_timer(unsigned int ms);


extern void bsp_init(void);


#ifdef __cplusplus
}
#endif


#endif

