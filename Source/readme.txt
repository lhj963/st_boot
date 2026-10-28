BYSD_GD32_BOOT_V1.0.3
Map (same numbers as KeilMDK/output/st_boot.sct and HardwareCfg.h):
	boot image:0-12K
	update param:12K-16K
	driver:16K-64K
	app:64K-256K
	update file:256K-512K
BOOT_SIZE stays 16K so an already-linked driver still starts at 16K.
APP_END is 256K and does not include the staging file.

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

