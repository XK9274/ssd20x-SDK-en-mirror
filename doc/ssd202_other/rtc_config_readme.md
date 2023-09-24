# illustrate
- SSD20x has built-in RTC.
- Current 0.001mA (see HDK)
- The normal RTC voltage is 2.0V-3.3V
- Please refer to HDK for hardware circuit.

# Configuration instructions
- You need to open the corresponding configuration RTC in the kernel to use it
- `make menuconfig` in kernel folder
![Configuration instructions](https://gitee.com/mFlying/flying_picgo_img/raw/master/PicGo-updata-img/RTC_config.png)

#RTC usage reference
- RTC adopts the standard LINUX framework and can use a unified interface to operate RTC
- First use the `data` command to view the current Linux time and set the time
- The `hwclock` command can be used to view the RTC time
- The `hwclock -w` command can write the time set by the "data" command into the RTC
- After a power outage and restart, the RTC time can be read through the hwlock command. (Refer to "RTC Usage Reference" for the original manufacturer's documentation)
