# SSD20X startup process
## 1. Partition
### 1.1. Startup method
- SSD20x has only two boot methods
    1. nand flash startup
    2. nor flash startup
### 1.2. Basic introduction to NOR partitions
Partition Name | Summary
---------|---------
  IPL | The main function is to do some basic hardware initialization, such as setting the current DDR parameters, GPIO/IIC related, etc.
  IPL_CUST | IPL_CUST will initialize the executable binary file of the customized board hardware according to the actual situation of the current board, such as customized GPIO management, IIC configuration
  MXPT | Binary files related to partition configuration.
  UBOOT | UBOOT binary file storage partition.
  UBOOT_ENV | UBOOT environment variable storage partition
  LOGO | Used on NVR devices, it stores the configuration related to the startup logo.
  KERNEL | Stores kernel binary files
  ROOTFS | file system
  miservice | Corresponds to the configs partition on the board. This is a partition defined by the public board. It is used to store mi libraries and some configuration documents. The file system defaults to jiffs2.
  customer | User-customized partition
### 1.3. Basic introduction to NAND partitions
Partition Name | Summary
---------|---------
  CIS | SPI-NAND unique partition, saved at the flash 0 address. It contains two parts. One part is spinand info, which saves some basic information of spinand, and the other part is partinifo, which saves partition information and is used by ROM CODE. of
  IPL0 | The main function is to do some basic hardware initialization, such as setting the current DDR parameters, GPIO/IIC related, etc.
  IPL1 | Backup partition of IPL0
  IPL_CUST0 | IPL_CUST will initialize the executable binary file of the customized board hardware according to the actual situation of the current board, such as customized GPIO management, IIC configuration
  IPL_CUST1 | Backup partition of IPL_CUST0
  UBOOT0 | UBOOT binary file storage partition.
  UBOOT0 | Backup partition of UBOOT1
  ENV0 | UBOOT environment variable storage partition
  ENV1 | Backup partition of ENV0
  KEY_CUST | Store third-party user keys
  LOGO | Used on NVR devices, it stores the configuration related to the startup logo.
  KERNEL | Stores kernel binary files
  RECOVERY | KERNEL's backup partition.
  ROOTFS | file system
  UBI | The content of UBI will not be displayed in the partition table above. Multiple sub-partitions in ubifs format will be created in UBI, and customers can create them as needed. Spinand's miservice partition is placed in UBI
### 1.4 Startup method selection process
- The Security boot process will perform security verification on IPL and other partitions, which is not involved here (only customers with special applications will open this information).
![doc/ssd20x_start_process/res/Start mode selection process.jpg](./res/Start mode selection process.jpg)

### 1.5. NOR flash startup process
![./res/NOR_flash_startup process.jpg](./res/NOR_flash_startup process.jpg)

### 1.6. NAND flash startup process
![./res/NAND_flash_startup process.jpg](./res/NAND_flash_startup process.jpg)

## 2. System
### 2.1 uboot startup process
- The standard uboot startup process can be seen online as follows:
    - Analysis of the overall process of starting Linux with uboot for embedded Linux development - ZhangyiStudio - Blog Park https://www.cnblogs.com/zhangyi-studio/p/8179795.html
- This section only explains the commonly used startup processes on SSD20x and those that require special attention.
- other instructions:
    - The uboot main function program is as follows `common/main.c`
    - If you need to add your own cli command, please refer to [Add your own cli command under uboot](../uboot_add_cmd/README.md);
- start up
    1. When uboot starts, press Enter to enter the uboot cli command line. You can then use the uboot command to perform corresponding operations.
    2. When exiting the cli command, the variable value of env will be read to determine whether an upgrade is required (the config of uboot needs to enable the corresponding configuration).
       - USB: setenv usbautoupgrade 1;saveenv
       - SD: setenv sdautoupgrade 1;saveenv
       - EMMC: setenv emmcautoupgrade 1;saveenv
    3. Then the `bootcmd` command in the env variable will be executed, such as the public version` bootlogo 0 0 0 0 0; mw 1f001cc0 11; gpio out 8 0; nand read.e 0x22000000 KERNEL 0x500000; gpio out 8 1; bootm 0x22000000; nand read.e 0x22000000 RECOVERY 0x500000; bootm 0x22000000`
       - The command will be executed in sequence. The display including the bootlogo is also displayed after executing this command until the kernel is finally run.

### 2.2 app startup process
- Take zk DEMO as an example.
- start up:
     1. After the kernel starts up, /etc/profile will be run. Execute the following parts in order (this file can be modified according to the script under the project to add your own content)
```shell
   1 #!/bin/sh
   2 export PATH=/bin:/sbin:/usr/bin:/usr/sbin
   3 export LD_LIBRARY_PATH=/lib
   4 mkdir -p /dev/pts
   5 ulimit -c unlimited
   6 export PATH=$PATH:/config
   7 export TERMINFO=/config/terminfo
   8 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/config/lib
   9 mkdir -p /dev/pts
  10 mount -t sysfs none /sys
  11 mount -t tmpfs mdev /dev
  12 mount -t debugfs none /sys/kernel/debug/
  13 mdev-s
  14 mkdir -p /var/lock
  15 mount -t ubifs ubi0:miservice /config
  16 mount -t ubifs ubi0:customer /customer
  17 mount -t ubifs ubi0:appconfigs /appconfigs
  18 mount -t ubifs ubi0:test1 /test1
  19
  20 mkdir -p /dev/pts
  21 mount -t devpts devpts /dev/pts
  22 busybox telnetd&
  23 if [ -e /etc/core.sh ]; then
  24 echo "|/etc/core.sh %p" > /proc/sys/kernel/core_pattern
  25 chmod 777 /etc/core.sh
  26fi;
  27 if [ -e /customer/demo.sh ]; then
  28/customer/demo.sh
  29fi;

```
    2. At the end, it will be judged whether the `/customer/demo.sh` file exists. If it exists, execute the modified script.
    - This script will be automatically generated when the project is packaged.
    - Will load the relevant ko, configure the corresponding environment and finally start zk DEMO
