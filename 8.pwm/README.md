# Summary
- Refer to the SDK pwm development documentation, you need to configure the corresponding device tree, and you need to enable the kernel pwm configuration option.

- SSD20X configuration quick reference
```shell
     #kernel
     make infinity2m_spinand_ssc011a_s01a_minigui_defconfig
     # Open pwm configuration (arm 4.9.84 Kernel Configuration → Device Drivers → SStar SoC platform drivers → <*> SSTAR_PWM)
     make menuconfig
     # Modify device tree
     vim arch/arm/boot/dts/infinity2m-ssc011a-s01a-display.dtsi
     #~~~~~
         pwm {
             compatible = "sstar,infinity-pwm";
             reg = <0x1F003400 0x600>;
             clocks = <&CLK_xtali_12m>;
             npwm = <2>;
             pad-ctrl = <PAD_GPIO4 PAD_GPIO5>;
             status = "ok"; // no available pads
         };
     #~~~~~
     # Modify the device tree (need to shield the associated pins)
     vim arch/arm/boot/dts/infinity2m-ssc011a-s01a-padmux-display.dtsi
     #~~~~~
         <PAD_GPIO4 PINMUX_FOR_PWM0_MODE_3 MDRV_PUSE_PWM0 >,
         <PAD_GPIO5 PINMUX_FOR_PWM1_MODE_4 MDRV_PUSE_PWM1 >,
         //<PAD_GPIO6 PINMUX_FOR_EJ_MODE_3 MDRV_PUSE_EJ_TDO >,
         //<PAD_GPIO7 PINMUX_FOR_EJ_MODE_3 MDRV_PUSE_EJ_TDI >,
     #~~~~~
```
### common
- Universal pwm interface

### pwm_test1
- Simply call the system interface to control pwm
- The original default screen backlight enablement of SSD202 is GPIO5. (active high level). The backlight adjustment pwm is PWM4.

### pwm_test2
- The encapsulated pwm interface is called to achieve the same function as test1
