#ifndef __HARDWARECFG_H__
#define __HARDWARECFG_H__
#ifdef __cplusplus
extern "C" {
#endif


#define BOOT_VERSION 	"BYSD_GD32_BOOT_V1.0.3"

/*
 * Same internal map as the driver (512KB, 2KB pages):
 *   0x08000000 boot    16KB   (scatter image is 12KB and stays inside this)
 *   0x08004000 driver  48KB
 *   0x08010000 app     until the OTA slot
 *   0x08030000 OTA image 188KB
 *   0x0805F000 update info
 *   0x0805F800 param store
 *   0x08060000 MPU-timeout log
 * Update info is not in the boot window (the old slot was 0x08003000).
 * APP_END_ADDR is the OTA slot start so erase-while-copy stops there.
 */
#define BOOT_START_ADDR 						0x08000000
#define BOOT_IMAGE_SIZE							(12 * 1024)
#define BOOT_SIZE								(16 * 1024)
#define BOOT_END_ADDR 							(BOOT_START_ADDR + BOOT_SIZE)

#define DRIVER_START_ADDR 						BOOT_END_ADDR
#define DRIVER_SIZE								(48 * 1024)
#define DRIVER_END_ADDR 						(DRIVER_START_ADDR + DRIVER_SIZE)

#define MCU_FLASH_SIZE							(512 * 1024)
#define MCU_FLASH_PAGE_SIZE						(2 * 1024)
#define MCU_FLASH_END_ADDR						(BOOT_START_ADDR + MCU_FLASH_SIZE)

#define APP_START_ADDR 							DRIVER_END_ADDR
#define APP_END_ADDR 							(BOOT_START_ADDR + (192 * 1024))

#define UPDATE_FILE_START_ADDR					APP_END_ADDR
#define UPDATE_FILE_MAX_SIZE					(188 * 1024)
#define UPDATE_FILE_END_ADDR					(UPDATE_FILE_START_ADDR + UPDATE_FILE_MAX_SIZE)

#define UPDATE_INFO_START_ADDR					UPDATE_FILE_END_ADDR
#define PARAM_STORE_ADDR						(UPDATE_INFO_START_ADDR + MCU_FLASH_PAGE_SIZE)
#define MPU_TIMEOUT_LOG_ADDR					(PARAM_STORE_ADDR + MCU_FLASH_PAGE_SIZE)

/* GD32F305 SRAM is 0x20000000-0x20018000 (96KB; the 64KB RB part is inside this). */
#define RAM_START_ADDR							0x20000000u
#define RAM_END_ADDR							(0x20000000u + (96u * 1024u))



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

extern unsigned int get_cpu_flash_size(void);

/* Deassert GPRS_RST and GPRS_ON_OFF (1 = not reset) before leaving the bootloader. */
extern void gprs_release_before_jump(void);

extern void bsp_init(void);


#ifdef __cplusplus
}
#endif


#endif

