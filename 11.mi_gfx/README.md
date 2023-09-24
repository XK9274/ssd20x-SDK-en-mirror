# Summary
- MI_GFX use demo



## fb_gfx_fill_rect
- Use to fill fb
- This DEMO does not have a screen initialization action. If the panel is not initialized, it needs to be initialized in advance.
- Run it directly, the full screen will be drawn in purple, and a red box will be drawn in the upper left corner. ARGB888

## fb_gfx_draw_line
- Use GFX to draw lines on fb
- This DEMO does not have a screen initialization action. If the panel is not initialized, it needs to be initialized in advance.

## gfx_rotate_yuv420
- Streamlined original demo, can display ARGB888 and flip YUV420 images on the public version
- eg: `./gfx_rotate_yuv420 ./res/YUV420SP_1280_720_NV12_img.yuv 1280 720`
