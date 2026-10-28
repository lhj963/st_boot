#ifndef __BOOT_CHECK_H__
#define __BOOT_CHECK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*
 * On-flash UpdateInfo at 0x0805F000 (one page, after the OTA slot).
 *
 * The record is packed and does not use a C enum, so --short-enums and
 * --enum_is_int cannot move ulStartAddr. usLayoutBytes must equal
 * sizeof(UpdateInfo). ulHeaderCrc is CRC-32 (calc_crc32) over every byte
 * before that field. A record without this magic, size, or CRC is ignored.
 *
 * Little-endian magic bytes are 'U','P','D','1'.
 */
#define UPDATE_INFO_MAGIC           0x31445055u
#define UPDATE_INFO_LAYOUT_VER      1u

#define UPDATE_STATUS_NO            0x12u
#define UPDATE_STATUS_START         0x34u
#define UPDATE_STATUS_FILE_OK       0x56u
#define UPDATE_STATUS_UPDATE_OK     0x78u
#define UPDATE_STATUS_UPDATE_FALSE  0x90u

#define BOOT_SLOT_MISMATCH          0
#define BOOT_SLOT_EMPTY             1
#define BOOT_SLOT_OK                2
#define BOOT_SLOT_UNPARSED          3

#if defined(__CC_ARM)
#define BOOT_STRUCT_PACKED __packed
#define BOOT_ATTR_PACKED
#else
#define BOOT_STRUCT_PACKED
#define BOOT_ATTR_PACKED __attribute__((packed))
#endif

typedef BOOT_STRUCT_PACKED struct tagDate
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
} BOOT_ATTR_PACKED Date;

typedef BOOT_STRUCT_PACKED struct tagUpdateInfo
{
	uint32_t magic;
	uint16_t usLayoutBytes;
	uint8_t ucLayoutVersion;
	uint8_t eUpdateStatus;
	uint8_t ucUpdateWay;
	uint8_t ucReserved0;
	uint16_t usReserved1;
	uint32_t ulStartAddr;
	uint32_t ulEndAddr;
	uint32_t ulTotalBytes;
	uint16_t usTotalPackCnt;
	Date stStartTime;
	uint32_t ulStartTime;
	Date stEndTime;
	uint32_t ulEndTime;
	uint32_t ulTakeTimes;
	int8_t szReportPhone[20];
	int8_t szServerAddr[32];
	uint16_t usServerPort;
	int8_t szUpdateFileName[32];
	uint32_t ulHeaderCrc;
} BOOT_ATTR_PACKED UpdateInfo;

/* 1 when SP is in RAM, 8-byte aligned, and the reset vector is a Thumb
 * address inside the installed image. 0xFFFFFFFF slots are refused. */
int boot_vector_is_valid(unsigned int sp, unsigned int reset,
	unsigned int ram_lo, unsigned int ram_hi,
	unsigned int image_lo, unsigned int image_hi);

/* Magic, layout size, version, known status, and header CRC. */
int boot_update_header_ok(const UpdateInfo *info, unsigned int computed_crc);

/* Source range must sit inside the staging partition. */
int boot_update_bounds_ok(unsigned int start, unsigned int total,
	unsigned int staging_lo, unsigned int staging_hi);

/* Image must fit in the destination partition before any erase. */
int boot_image_fits_partition(unsigned int total, unsigned int dest,
	unsigned int dest_end);

/*
 * Returns 1 and sets *is_driver when the payload may be installed.
 * A version string that starts with the driver name but whose flag word
 * is not the driver magic is refused (it must not be installed as an app).
 */
int boot_classify_image(const char *version, const char *driver_name,
	unsigned int flag_word, unsigned int expect_magic, int *is_driver);

/* Installed driver/app version text at SOFTWARE_INFO_OFFSET. */
int boot_slot_header_state(const unsigned char *text, unsigned int len,
	const char *manufacturer);

/* Manufacturer mismatch refuses the install. Empty and unparsed slots stay installable. */
int boot_slot_allows_install(int state);

/* UPDATE_OK only when the program and the programmed-image CRC both succeeded. */
int boot_commit_status(int program_ok, int image_crc_ok);

/* Copy src_len payload bytes and fill the rest of the page with 0xFF. */
void boot_pad_page(unsigned char *page, unsigned int page_size,
	const unsigned char *src, unsigned int src_len);

#ifdef __cplusplus
}
#endif

#endif
