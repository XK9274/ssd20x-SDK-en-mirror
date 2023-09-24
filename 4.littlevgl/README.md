# Summary

## Notice

- The panel must be initialized before you can use these demos
- SSD20x needs to run the application that initializes the panel in the background before running fbdemo.
- The SSD2x2 platform panel is initialized during the boot phase. If the boot logo is displayed, it proves that the panel has been initialized.
- Useful to touch

## illustrate

#### demo use

- The demo here defaults to the first two parameters setting the width and height.
- Default 1024*600

##### 1. lv_demos_app

- ./lv_demos_app 1024 600 3
   - Indicates using a 1024*600 screen and using the demo of the third lvgl
- demo description
   - 0: Music player
   ![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-10.png)

   - 1: Stress test
    ![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-11.png)

   - 2: Keyboard Player
    ![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-12.png)

   - 3: widgets
    ![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-13.png)

##### 2. lv_test_all_app

- All demos tested by lvgl official components
- ./lv_test_all_app 1024 600 3
   - Executable shell_lv_test_all_app.sh script to quickly preview all demos
   - Indicates using a 1024*600 screen and using the demo of the third lvgl

##### 3. lv_lib_png_test_app

- png decoding test demo
- ./lv_lib_png_test_app 1024 600 ./res/png_decoder_test.png
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-9.png)

##### 4. lv_lib_gif_test_app

- gif decoding test demo
- ./lv_lib_gif_test_app 1024 600 ./res/example.gif
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-8.png)

##### 5. f_game_2048

- Reference 100ask 7.11 version 2048
- 2048 mini games
- ./f_game_2048 1024 600
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-7.png)

##### 6. lv_lib_split_jpg_test_app

- Decode 3 jpg pictures and switch the display, calling ./res/1.jpg 2.jpg 3.jpg by default
- ./lv_lib_split_jpg_test_app 1024 600
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-6.png)

##### 7. lv_lib_freetype_test_app

- LVGL only has English fonts by default. If you want to use Chinese, you will use freetype.
- ./lv_lib_freetype_test_app 1024 600 ./res/GBK_Mobil.TTF
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-5.png)

##### 8. lv_lib_bmp_test_app

- bmp decoding test demo
- ./lv_lib_bmp_test_app 1024 600 ./res/example_16bit.bmp
- You need to check the colors of the panel and choose bmp accordingly.
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-4.png)

##### 9. f_game_snake

- Simple snake game
- ./f_game_snake 1024 600
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-3.png)

##### 10. f_tool_file_browser

- Simple file browser
- Can enter the upper and lower levels of folders
- And can view png, jpg, gif, bmp, ttf files
- ./f_tool_file_browser 1024 600
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-2.png)

##### 11. f_game_tetris

- Simple Tetris game
- Made using the lv_canvas canvas component, which can be used for attributes to understand the usage of lv_canvas
- ./f_game_tetris 1024 600
![Image](https://gitee.com/mFlying/flying_picgo_img/raw/master/frame-1.png)