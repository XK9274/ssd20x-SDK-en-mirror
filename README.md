Original source: https://gitee.com/mFlying/ssd2xx-demo.git

# SSD series application demo<a name="demoDoc"></a>

- [1. Summary](#demoDoc1)
- [2. Contents](#demoDoc2)
- [3. Instructions for use](#demoDoc3)
- [4. Internal DEMO description](#demoDoc4)
- [5. Other external DEMOs of SSD2XX](#demoDoc5)
- [6. Other documentation](#demoDoc7)
- [7. Contact us](#demoDoc6)

## 1. Introduction<a name="demoDoc1"></a>

- It contains commonly used test DEMOs such as SSD20x (SSD201, SSD202, SSD203), SSD21X (SSD212, SSD222), etc. to facilitate everyone to verify problems.
- The folder name numbers have no special meaning, they are just named in the order before and after adding DEMO.

## 2. Directory<a name="demoDoc2"></a>

```shell
/ssd2xx-demo
├── CMakeLists.txt # cmake lists, project configuration, used for cmake compilation
├── toolchain.cmake # cmake cross-compilation configuration
├── README.md # Main entrance to documentation
├── doc # documentation
├── 0.common # Public lib, include, third-party libraries, etc.
│ ├── ssd20x # SSD20x SDK related library (V030 version)
│ ├── ssd2x2 # SSD2x2 SDK related library (V013 version)
│ ├── iniparser # Third-party ini parsing library, iniparser
│ ├── general # Third-party general libraries, such as lists, queues, etc.
│ ├── tests # common test code
│ ├── list # Doubly linked list
│ └── ### # END
├── 1.watchdog # watchdog demo
├── 2.panel # Click screen related demo
├── 3.framebuffer # fb operation demo
├── 4.littlevgl # littleVGL demo
├── 5.wifi # wifi demo
├── 6.audio # Audio related, MI_AI/MI_AO demo
├── 7.gpio # GPIO operation demo
├── 8.pwm # PWM operation demo
├── 9.uart # UART (serial port) operation demo
├── 10.video # Video, YUV display and other related demos
├── 11.mi_gfx # MI GFX demo
├── 12.mi_disp # MI DISP demo
└── ### # END
```

## 3. Instructions for use<a name="demoDoc3"></a>

- Connotation sub-repository, you need to update the sub-repository if necessary after cloning

```shell
     git clone https://gitee.com/mFlying/ssd2xx-demo.git
     cd ssd2xx-demo
     git submodule init
     git submodule update
```

### Full compiled script

```shell
     #ssd202D, ssd201 platform
     ./build_all.sh -j8 -ssd20x

     #ssd212、ssd222、ssd222D platform
     ./build_all.sh -j8 -ssd2x2
    
     #stm32mp157平台
     ./build_all.sh -j8 -mp157
```

### Compile with separate command

#### Compile the DEMO of SSD20x

- Installation of cross-compilation tools, cmake and other tools.
- The compilation process is as follows:

```shell
     mkdir build
     cd build
     cmake -D CMAKE_TOOLCHAIN_FILE=toolchain.cmake -D CHIP=ssd20x ..
     make -j8
```

#### Compile the DEMO of SSD2x2

- If you have used `cmake` with other CHIP before, you need to delete the files that were generated by cmake before.

```shell
     cd build
     rm*-rf
     cmake -D CMAKE_TOOLCHAIN_FILE=toolchain.cmake -D CHIP=ssd2x2 ..
     # Compile all
     make -j8
     # You can check what demos are available, and then you can specify DEMO compilation.
     make help
     make pwm_test1
```

- **The files generated after compilation are in /build/bin & /build/lib**

## 4. DEMO description<a name="demoDoc4"></a>

- [0.common general library, third-party open source library, etc. Document description](./0.common/README.md);
- [1.watchdog watchdog document description](./1.watchdog/README.md);
- [2.panel click screen related document description](./2.panel/README.md);
- [Demo document description related to 3.framebuffer fb operation](./3.framebuffer/README.md);
- [4.littlevgl LVGL GUI demo documentation](./4.littlevgl/README.md);
- [5.wifi WIFI demo document description](./5.wifi/README.md);
- [6.audio AO/AI and other interface DEMO document description](./6.audio/README.md);
- [7.gpio GPIO DEMO document description](./7.gpio/README.md);
- [8.pwm pwm DEMO document description](./8.pwm/README.md);
- [9.uart serial port DEMO document description](./9.uart/README.md);
- [10.video video related DEMO document description](./10.video/README.md);
- [11.mi_gfx GFX DEMO document description](./11.mi_gfx/README.md);
- [12.mi_disp DISP DEMO document description](./12.mi_disp/README.md);
- [13. Read the chip’s unique identifier UUID and set it to the MAC of eth0](./13.uuid/README.md);

## 5. Other documentation<a name="demoDoc7"></a>

- [SSD20x startup instructions](./doc/ssd20x_start_process/README.md)
- [uboot adds its own cli command](./doc/uboot_add_cmd/README.md);
- [ssd2x2 modify kernel configuration (make menuconfig) method](./doc/ssd2x2_kernel_config_set/README.md);
- [Application memory detection tool valgrind summary](./doc/valgrind/README.md);
- [List of methods for downloading applications to the public board](./doc/file_download/README.md);
- [SSD20x RTC configuration instructions](./doc/ssd202_other/rtc_config_readme.md);
- [Network testing tool iperf3 description](./doc/iperf3/README.md)
- [NAT/iptables summary description, ap, eth bridge description](./doc/NAT/README.md)
- [Use of SSD202x wifi test command wpa_cli](./doc/ssd202_other/wifi_test.md)
- [SSD2X2, SDK compilation supports SSW101B (USBwifi) instructions](./doc/other/ssd21x_sup_ssw101.md)
- [SSD20X screen clicking restrictions, determine whether the panel can be clicked](./doc/ssd202_other/panel_clk.md)
- [Public board touch screen is not allowed to be set](./doc/other/tp_set.md)
- [SSD20X public board NOR project customer, config (partition) cannot be written problem](./doc/other/sdk_nor_jffs2.md)
- [Overview of SQLite basic concepts and usage](./doc/other/sqlite_introduce.md)
  
## 6. Other DEMOs of SSD2XX<a name="demoDoc5"></a>

### 1. SSD20x

#### 1. There will be some DEMOs in the `sdk` folder of the V030 version of the SDK. as follows

```shell
└── verify
     ├── application
     │ ├── bootanimation
     │ ├── jpeg2disp
     │ ├── logo
     ├──feature
     │ ├── disp
     │ ├── fb
     │ │ ├── fb_tc001
     │ │ ├── fb_tc002
     │ │ ├── fb_tc003
     │ │ ├── fb_tc004
     │ │ ├── fb_tc005
     │ │ ├── fb_tc006
     │ │ └── fb_tc007
     │ └── gfx
     │ ├── common
     │ ├── tc_bitblit
     │ ├── tc_blend
     │ ├── tc_fillrect
     │ └── tc_rotate
     └── mi_demo
         ├── 3rdparty
         │ ├── jpeg
         │ ├── libnl
         │ ├── openssl
         │ ├── png
         │ ├── wpa_supplicant
         │ └── z
         ├── amigos
         │ ├── hdmi_convertor
         │ ├── internal
         │ └── preview
         ├── common
         │ ├── dla_fw
         │ ├── iniparser
         │ ├── live555
         │ ├── lwfs
         │ ├── onvif
         │ ├── opencv
         │ ├── res
         │ └── tem
         ├── geonosis
         │ ├── audio_all_test_case
         │ ├── cardv_test
         │ ├── codec
         │ ├── fb
         │ ├── hdmi_test
         │ ├── internal
         │ ├── lib
         │ ├── obj
         │ ├── vdec
         │ └── venc
         └── out
             └── demo

```

#### 2. The DEMO that is outside the SDK can be obtained from FAE.

- No updates released with SDK
- The following are only available in the V08 version. Some demos cannot be compiled normally in the new version and need to be modified by yourself.

```shell
# Demo_Release.tar.gz
├─Airplay
├─browser
├─BurnKey
├─CloudPlay+Wifi
├─directfb
├─DisplayDemo
├─enable_cipher
├─eventtest
├─fb&gfx
│ └─feature
│ ├─disp
│ ├─fb
│ │ ├─fb_tc001
│ │ ├─fb_tc002
│ │ ├─fb_tc003
│ │ ├─fb_tc004
│ │ └─fb_tc005
│ └─gfx
├─H264Player
│ └─h264Player
├─IR
├─JpegPlayer
├─jpg_rotate
├─mini_player
├─MM
├─QT
├─RequestIDR
├─rw_reg
├─simplayer
├─smarttalk_outside
├─UI_DEMO
│ ├─directfb
│ ├─eventtest
│ ├─GFX
│ ├─GFX Rotation
│ ├─jpg_rotate
│ ├─pri_screensaver
│ ├─pri_statusbar
│ ├─QT
│ └─security_SSDUI
├─usb_camera
├─vdec_getoutpubuf
├─wifi
└─Four-split screen+PIP
```

### 2. SSD2x2

#### 1. There will be some DEMOs in the `sdk` folder of the V014 version of the SDK. as follows

```shell
# V014 version sdk folder
├── driver
│ └── SensorDriver
└── verify
     ├── application
     │ ├── disp_pic_fastboot
     │ ├── jpeg2disp
     │ ├── logo
     │ ├── ota_test
     │ ├── qfn68_sensor_panel
     │ ├── smarthome
     │ ├── smarttalk
     │ ├── ssplayer
     │ ├── usbcamera
     │ └── usbcamera_fastboot
     ├──feature
     │ ├── fb
     │ │ ├── common
     │ │ ├── fb_clrkey
     │ │ ├── fb_color
     │ │ ├── fb_cursor
     │ │ ├── fb_dbbuf
     │ │ ├── fb_dispattr
     │ │ ├── fb_multi
     │ │ ├── fb_scale
     │ │ └── fb_total
     │ └── gfx
     │ ├── common
     │ ├── tc_bitblit
     │ ├── tc_blend
     │ ├── tc_fillrect
     │ └── tc_rotate
     └── mi_demo
         ├── 3rdparty
         ├── common
         │ ├── dla_fw
         │ ├── iniparser
         │ ├── lwfs
         │ ├── onvif
         │ ├── opencv
         │ ├── res
         │ ├── tem
         │ ├── uac
         │ └── uvc
         └── ikayaki
             ├── audio
             ├── audio_alg_AEC_demo
             ├── audio_alg_AED_demo
             ├── audio_alg_APC_AGC_demo
             ├── audio_alg_APC_ANR_demo
             ├── audio_alg_APC_demo
             ├── audio_alg_APC_EQ_demo
             ├── audio_alg_BF_demo
             ├── audio_alg_SRC_demo
             ├── audio_alg_SSL_demo
             ├── audio_all_alg_test_case
             ├── audio_all_test_case
             ├── audio_g711_codec_demo
             ├── audio_g726_codec_demo
             ├── internal
             ├── mix
             ├── panel
             ├── uvc
             ├── venc
             └── vpe

```

#### 2. The DEMO that is outside the SDK can be obtained from FAE.

- No updates released with SDK

```shell
# IKAYAKI_ReleaseDemo_20210528_f8248bc.tar.gz
├─audio
├─fb_demo
├─fb_gfx
├─JpegPlayer
├─panel
│ ├─PspiDemo
│ ├─SpiPanel
│ └─YuvToPanel
├─rotate
│ └─rotate420
│ ├─sstardisp
│ └─yuv-picture
├─scanpen
│ └─internal
│ ├─common
│ ├─rgn
│ ├─vif
│ └─vpe
├─sensor
│ └─internal
│ ├─common
│ ├─ive
│ ├─rgn
│ ├─spi
│ ├─vif
│ └─vpe
├─uvc
└─wifi
```

### 3. Others

#### 1. Other DEMOs provided by the original manufacturer

- [github path https://github.com/aaron201912?tab=repositories](https://github.com/aaron201912?tab=repositories)
- The content is like the Zhongke flthings DEMO that comes with the factory, as shown below

```shell
├─ SSD26X_ZK
├─ ffmpeg #ffmpeg cross-compile, use demo
├─ SSC268
├─ SSD222_Demo
├─ UuidSSDPlayer #Video player
├─ hp_customer
├─ RunTimeDemo #ZK UI DEMO for SSD20x and SSD2x2. new version
├─ amigos_customer
├─ Qt5.15_example # QT DEMO, connotative cross-compilation instructions
├─ rtsp-client
├─ 3rdparty
├─ SSD20xDemo
├─ SSD_PLAYER #IDE based on ZK UI player. old version
├─ DisplayDemo #Advertising publishing machineDemo
└─ VideoStream
```

## 7. Contact us<a name="demoDoc6"></a>

- If you have any questions, please directly raise `issues`
- Email: `weekend@111.com`
