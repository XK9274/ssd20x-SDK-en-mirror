# SSD2x2 public board uses SSW101B wifi
### 1. Background
- The document does not describe how to use SSW101B's wifi, but the SDK contains the SSW101B driver.
- Version V014
### 2. Usage steps
- Take nor as an example.
- Operate in the project folder
##### 1. Select configuration
```shell
# Select the configuration without sdio wifi according to the environment construction document
make dispcam_p3_nor.glibc-9.1.0-squashfs.s01a.64.qfn128.demo_defconfig
# Open the configuration and choose to use ssw101b (sigma_wifi -> (X) ssw101b_wifi_usb)
make menuconfig
```
##### 2. Add a script to write the bootcmd command
- After making menuconfig, you can see the log **IMAGE_CONFIG = nor.squashfs.partition.dualenv.dispcam.config**
- Add it directly to the file `vim image/configs/p3/nor.squashfs.partition.dualenv.dispcam.config`
- Modify as follows
```sh
wifi23mclkcmd = mw 1f00lcc0 11
wifirstoffcmd = gpio out 60 1
wifirstoncmd = gpio out 60 0

bootlogocmd = $(wifi23mclkcmd)\;$(wifirstoffcmd)\; bootlogo 0 0 0 0\;$(wifirstoncmd)\;

```
- The purpose is just to write wifi23mclkcmd, wifirstoffcmd, wifirstoncmd into the parameters of bootcmd in env. You can also write it in other places and adjust it yourself.
- gpio 60 corresponds to the WiFi power pin of the public board. If you draw your own board, you need to adjust it yourself.

##### 3. Compile
- Directly make image, then burn it and it can be used normally.
- For test methods, please refer to **SSD20x WIFI usage test**
