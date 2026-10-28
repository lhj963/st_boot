/* Host-side checks for the boot decision logic. Not part of the Keil image. */
#include "boot_check.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

extern unsigned int calc_crc32(unsigned int PartialCrc, void *pbuf, unsigned int Length);

/* Readme map used by the bootloader. */
#define MAP_RAM_LO        0x20000000u
#define MAP_RAM_HI        0x20018000u
#define MAP_DRIVER        0x08004000u
#define MAP_APP           0x08010000u
#define MAP_APP_END       0x08040000u
#define MAP_STAGING_END   0x08080000u

static void seal(UpdateInfo *info)
{
	info->magic = UPDATE_INFO_MAGIC;
	info->usLayoutBytes = (uint16_t)sizeof(UpdateInfo);
	info->ucLayoutVersion = (uint8_t)UPDATE_INFO_LAYOUT_VER;
	info->ulHeaderCrc = 0;
	info->ulHeaderCrc = calc_crc32(0, info, (unsigned int)(sizeof(*info) - 4u));
}

static unsigned int header_crc(const UpdateInfo *info)
{
	UpdateInfo tmp = *info;
	tmp.ulHeaderCrc = 0;
	return calc_crc32(0, &tmp, (unsigned int)(sizeof(tmp) - 4u));
}

static void test_layout(void)
{
	assert(sizeof(UpdateInfo) == 140u);
	assert(sizeof(((UpdateInfo *)0)->eUpdateStatus) == 1u);
	assert(offsetof(UpdateInfo, eUpdateStatus) == 7u);
	assert(offsetof(UpdateInfo, ulStartAddr) == 12u);
	assert(offsetof(UpdateInfo, ulHeaderCrc) == 136u);
}

static void test_vector(void)
{
	/* Realistic driver image: SP at top of 64KB SRAM, Thumb reset in the driver. */
	assert(boot_vector_is_valid(0x20010000u, 0x08004135u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 1);
	/* Top of 96KB SRAM is a legal initial MSP. */
	assert(boot_vector_is_valid(0x20018000u, 0x08010001u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 1);
	/* Blank slot. Reset is odd, so the explicit 0xFFFFFFFF check matters. */
	assert(boot_vector_is_valid(0xFFFFFFFFu, 0xFFFFFFFFu,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20010000u, 0xFFFFFFFFu,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0xFFFFFFFFu, 0x08004135u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	/* Outside RAM, misaligned, missing Thumb bit, bootloader, staging. */
	assert(boot_vector_is_valid(0x08004000u, 0x08004135u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20010004u, 0x08004135u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20010000u, 0x08004134u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20010000u, 0x08000101u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20010000u, 0x08040001u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
	assert(boot_vector_is_valid(0x20018008u, 0x08004135u,
		MAP_RAM_LO, MAP_RAM_HI, MAP_DRIVER, MAP_APP_END) == 0);
}

static void test_update_info(void)
{
	UpdateInfo info;
	unsigned char raw[sizeof(UpdateInfo)];
	unsigned int crc;

	memset(&info, 0, sizeof(info));
	info.eUpdateStatus = (uint8_t)UPDATE_STATUS_FILE_OK;
	info.ulStartAddr = MAP_APP_END;
	info.ulEndAddr = MAP_APP_END + 4096u - 1u;
	info.ulTotalBytes = 4096u;
	seal(&info);
	crc = header_crc(&info);
	assert(boot_update_header_ok(&info, crc) == 1);
	assert(boot_update_bounds_ok(info.ulStartAddr, info.ulTotalBytes,
		MAP_APP_END, MAP_STAGING_END) == 1);

	assert(boot_update_header_ok(&info, crc ^ 1u) == 0);

	memset(raw, 0xFF, sizeof(raw));
	assert(boot_update_header_ok((const UpdateInfo *)raw, 0) == 0);

	info.usLayoutBytes = (uint16_t)(sizeof(UpdateInfo) + 4u);
	info.ulHeaderCrc = 0;
	info.ulHeaderCrc = calc_crc32(0, &info, (unsigned int)(sizeof(info) - 4u));
	assert(boot_update_header_ok(&info, info.ulHeaderCrc) == 0);

	seal(&info);
	info.eUpdateStatus = 0xABu;
	crc = header_crc(&info);
	info.ulHeaderCrc = crc;
	assert(boot_update_header_ok(&info, crc) == 0);

	/* Address inside the app partition is not staging. */
	assert(boot_update_bounds_ok(MAP_APP, 4096u, MAP_APP_END, MAP_STAGING_END) == 0);
	/* Length that runs out of the staging window. */
	assert(boot_update_bounds_ok(MAP_STAGING_END - 100u, 200u,
		MAP_APP_END, MAP_STAGING_END) == 0);
	/* Unaligned source. */
	assert(boot_update_bounds_ok(MAP_APP_END + 1u, 4096u,
		MAP_APP_END, MAP_STAGING_END) == 0);
	/* No staging on a 256KB part. */
	assert(boot_update_bounds_ok(MAP_APP_END, 4096u, MAP_APP_END, MAP_APP_END) == 0);

	assert(boot_image_fits_partition(100u * 1024u, MAP_APP, MAP_APP_END) == 1);
	assert(boot_image_fits_partition(0x50000u, MAP_APP, MAP_APP_END) == 0);
	assert(boot_image_fits_partition(200u * 1024u, MAP_DRIVER, MAP_APP_END) == 1);
	assert(boot_image_fits_partition(250u * 1024u, MAP_DRIVER, MAP_APP_END) == 0);
}

static void test_classify_and_slot(void)
{
	int is_driver = 1;
	unsigned char text[64];

	assert(boot_classify_image("BYSD_DRIVER_GD32_V1.0.3", "BYSD_DRIVER",
		0x11223344u, 0x11223344u, &is_driver) == 1);
	assert(is_driver == 1);

	is_driver = 1;
	assert(boot_classify_image("BYSD_DRIVER_GD32_V1.0.3", "BYSD_DRIVER",
		0x11223345u, 0x11223344u, &is_driver) == 0);
	assert(is_driver == 0);

	is_driver = 1;
	assert(boot_classify_image("BYSD_APP_V1.2.0", "BYSD_DRIVER",
		0u, 0x11223344u, &is_driver) == 1);
	assert(is_driver == 0);

	memset(text, 0xFF, sizeof(text));
	assert(boot_slot_header_state(text, sizeof(text), "BYSD") == BOOT_SLOT_EMPTY);
	assert(boot_slot_allows_install(BOOT_SLOT_EMPTY) == 1);

	memset(text, 0, sizeof(text));
	memcpy(text, "<BYSD><BYSD_DRIVER_GD32_V1.0.3>", 30);
	assert(boot_slot_header_state(text, sizeof(text), "BYSD") == BOOT_SLOT_OK);
	assert(boot_slot_allows_install(BOOT_SLOT_OK) == 1);

	memset(text, 0, sizeof(text));
	memcpy(text, "<OTHER><img>", 12);
	assert(boot_slot_header_state(text, sizeof(text), "BYSD") == BOOT_SLOT_MISMATCH);
	assert(boot_slot_allows_install(BOOT_SLOT_MISMATCH) == 0);

	memset(text, 0, sizeof(text));
	memcpy(text, "no-header", 9);
	assert(boot_slot_header_state(text, sizeof(text), "BYSD") == BOOT_SLOT_UNPARSED);
	assert(boot_slot_allows_install(BOOT_SLOT_UNPARSED) == 1);
}

static void test_program_result(void)
{
	unsigned char page[32];
	unsigned char src[6];
	unsigned int i;

	assert(boot_commit_status(1, 1) == (int)UPDATE_STATUS_UPDATE_OK);
	assert(boot_commit_status(0, 1) == (int)UPDATE_STATUS_UPDATE_FALSE);
	assert(boot_commit_status(1, 0) == (int)UPDATE_STATUS_UPDATE_FALSE);
	assert(boot_commit_status(0, 0) == (int)UPDATE_STATUS_UPDATE_FALSE);

	for (i = 0; i < sizeof(page); i++)
	{
		page[i] = 0xABu;
	}
	src[0] = 1;
	src[1] = 2;
	src[2] = 3;
	src[3] = 4;
	src[4] = 5;
	src[5] = 6;
	boot_pad_page(page, sizeof(page), src, sizeof(src));
	assert(page[0] == 1 && page[5] == 6);
	for (i = 6; i < sizeof(page); i++)
	{
		assert(page[i] == 0xFFu);
	}

	memset(src, 0x11, sizeof(src));
	memset(page, 0xAB, sizeof(page));
	boot_pad_page(page, sizeof(src), src, sizeof(src));
	assert(page[0] == 0x11);
	assert(page[5] == 0x11);
}

int main(void)
{
	test_layout();
	test_vector();
	test_update_info();
	test_classify_and_slot();
	test_program_result();
	printf("boot_check_test: ok\n");
	return 0;
}
