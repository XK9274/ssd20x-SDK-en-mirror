# Summary
- Please refer to the documentation for SSD2x2 screen click. There is a special configuration file. The panel can be automatically initialized after the system starts. After the system starts, the fb can be directly operated.

## ssd20x-ttl-panel-base
- SDK verification for v030 version
- The display is SAT070CP50_1024x600. **Contents other point screen parameters**
- The kernel configuration is `make infinity2m_ssc011a_s01a_minigui_defconfig`.
- You can click on the default screen of sigmastar public board
- ARGB8888
-  use
```shell
# Run in the background, and then run the ui application and only initialize the panel.
     ./ssd20x-ttl-panel-base &
# Simple fb fill background color, ARGB8888. If filled with red
     ./ssd20x-ttl-panel-base 0xffff0000
```

##ssd20x-st7789-240x240-sw
- SDK verification for v030 version
- TTL-RGB565 small screen
- It also needs to be initialized through SPI, **spi software simulation** to send 9bit data
- There are some references to other files such as device trees in the other folder

##ssd20x-st7789-240x240-hw
- SDK verification for v030 version
- TTL-RGB565 small screen
- It also needs to be initialized through SPI, and the **spi hardware peripheral** sends 9bit data (remember to open the spi configuration for the kernel)
- There are some references to other files such as device trees in the other folder

## ssd20x-mipi-1024x600
- SDK verification for v030 version
-TTL-RGB888
- The kernel configuration is `make infinity2m_ssc011a_s01a_minigui_defconfig`.
- The customized screen does not send any MIPI CMD commands
-  use
```shell
# Run in the background, and then run the ui application and only initialize the panel.
     ./ssd20x-mipi-1024x600 &
# Simple fb fill background color, ARGB8888. If filled with red
     ./ssd20x-mipi-1024x600 0xffff0000
```

## ssd2x2_ttl_panel_init
- According to the structure of the SDK, the panel has been initialized by default after the system is started, and disp is enabled.
- But if other applications have disp enabled and then exit, the disp disp will be lost, so re-initialization is required, otherwise fb cannot be used.
