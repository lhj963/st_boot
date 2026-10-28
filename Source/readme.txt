BYSD_GD32_BOOT_V1.0.3
Map matches the driver (512KB, 2KB pages):
	boot:0x08000000-0x08004000 (linked image is 12KB)
	driver:0x08004000-0x08010000
	app:0x08010000-0x08030000
	OTA image:0x08030000-0x0805F000
	update info:0x0805F000
	param store:0x0805F800
	MPU timeout log:0x08060000
APP_END is the OTA slot start. Update info is not in the boot window.
Boot applies an upgrade only from a packed UPD1 record at 0x0805F000
(magic 0x31445055, layout size 140, header CRC-32). A valid driver or
app vector still boots when that page is empty or the status is not FILE_OK.
An in-flight upgrade left at 0x08003000 is not completed. Re-trigger it
after this bootloader and the driver are flashed together.
GPRS_RST and GPRS_ON_OFF stay low across the jump (field idle). The
driver pulses ON_OFF itself to start the 4G module.

BYSD_GD32_BOOT_V1.0.2
1.4g power pin high

BYSD_GD32_BOOT_V1.0.1
1.check the version

BYSD_NXP_BOOT_V1.0.0
1.S32K144
2.	BOOT:0-12K 
	update param:12K-16K
	driver:16K-64K
	app:64K-256K

	update file:256K-512K

