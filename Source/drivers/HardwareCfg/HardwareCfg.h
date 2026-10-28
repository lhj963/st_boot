#ifndef __HARDWARECFG_H__
#define __HARDWARECFG_H__
#ifdef __cplusplus
extern "C" {
#endif


#define BOOT_VERSION 	"BYSD_GD32_BOOT_V1.0.3"

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


//GPRS_DTR
#define GPRS_DTR_RCC								RCC_APB2Periph_GPIOD
#define GPRS_DTR_PORT								GPIOD
#define GPRS_DTR_PIN								GPIO_Pin_13
#define GPRS_DTR_PIN_MODE							GPIO_Mode_Out_PP


//GPRS_PWR   4G模块供电控制引脚  1打开 0关闭
#define GPRS_PWR_RCC								RCC_APB2Periph_GPIOE
#define GPRS_PWR_PORT								GPIOE
#define GPRS_PWR_PIN								GPIO_Pin_15
#define GPRS_PWR_PIN_MODE							GPIO_Mode_Out_PP

//GPRS_RST   4G RST引脚  1NOT RST 0 RST
#define GPRS_RST_RCC								RCC_APB2Periph_GPIOD
#define GPRS_RST_PORT								GPIOD
#define GPRS_RST_PIN								GPIO_Pin_12
#define GPRS_RST_PIN_MODE							GPIO_Mode_Out_PP


//GPRS_ON_OFF  GPRS_ON_OFF引脚  1NOT RST 0 RST
#define GPRS_ON_OFF_RCC								RCC_APB2Periph_GPIOD
#define GPRS_ON_OFF_PORT							GPIOD
#define GPRS_ON_OFF_PIN								GPIO_Pin_11
#define GPRS_ON_OFF_PIN_MODE						GPIO_Mode_Out_PP


//MCU_WAKE_UP_4G  MCU_WAKE_UP_4G引脚  1WAKE UP 0NOT WAKE UP
#define MCU_WAKE_UP_4G_RCC							RCC_APB2Periph_GPIOB
#define MCU_WAKE_UP_4G_PORT							GPIOB
#define MCU_WAKE_UP_4G_PIN							GPIO_Pin_15
#define MCU_WAKE_UP_4G_PIN_MODE						GPIO_Mode_Out_PP



extern void gpio_init(void);

extern void delayms_by_timer(unsigned int ms);


extern void bsp_init(void);


#ifdef __cplusplus
}
#endif


#endif

