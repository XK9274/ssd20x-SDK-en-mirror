# Public board touch screen is not allowed to be set

- The configuration of the touch driver needs to correspond to the resolution of `/config/fbdev.ini` on the board

## Setting method

- Documentation in `doc/other/tp_config`
- The setting command is as follows

   ```shell
     echo 1024x600.bin > /sys/bus/i2c/devices/0-005d/gtcfg
     echo 800x480.bin > /sys/bus/i2c/devices/0-005d/gtcfg
     #or
     echo 1024x600.bin > /sys/bus/i2c/devices/1-005d/gtcfg
     echo 800x480.bin > /sys/bus/i2c/devices/1-005d/gtcfg
   ```
