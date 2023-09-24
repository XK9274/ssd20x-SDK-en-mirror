# Summary
## Notice
- The panel must be initialized before you can use these demos
- SSD20x needs to run the application that initializes the panel in the background before running fbdemo.
- The SSD2x2 platform panel is initialized during the boot phase. If the boot logo is displayed, it proves that the panel has been initialized.

## illustrate
### common
- Universal FB interface
- fb information printing interface
- fb simple rectangle filling interface

### fb_info
- Print all fb information demo

### fb_rect_test
- Simple fb rectangle filling demo
- Fillable RGB8888/565/1444/1555 type

### bmp_img_24bit
- Display 24bit pictures on ARGB888
- eg:`./bmp_img_24bit res/saturation_800x480_24bit.bmp`

### jpeg_img
- Can display jpg pictures on FB
-eg:
```shell
#Specify libjpeg library path
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
./jpeg_img res/detail.jpg
```
