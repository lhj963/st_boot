# BYSD_GD32_BOOT

GD32 Bootloader。上电后完成板级初始化，检查远程升级与串口升级，无需升级时跳转到应用程序。版本记录见 `Source/readme.txt`（当前 `BYSD_GD32_BOOT_V1.0.3`）。

## Flash 分区

以下范围摘自 `Source/readme.txt`（相对片内 Flash 起始地址）：

| 区域 | 范围 |
| --- | --- |
| BOOT | 0–12K |
| update param（升级参数） | 12–16K |
| driver | 16–64K |
| app | 64–256K |
| update file（升级文件） | 256–512K |

## 编译

用 Keil MDK 打开 `KeilMDK/st_boot.uvproj`。`KeilMDK/lst/`、`KeilMDK/output/` 以及 Source Insight 目录 `SI/` 为本地生成物，不纳入版本库。

## 发布

不要把 `BYSD_GD32_BOOT_*.zip` 等发布压缩包提交进仓库。对外发布请使用 GitHub Releases。

## 迁移历史

`Source/drivers` 里的 NXP / S32K 时钟与 FlexCAN 等驱动是从早期 NXP 工程迁到 GD32 时留下的，只作历史对照，请勿删除。
