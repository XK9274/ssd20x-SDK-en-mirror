/*------------------------------------------------ ----------------------------------
* @File name : main.cpp
* @author: flying
* @mail: weekend@111.com
* @Summary : None
* @Note: None
* Modification history**************************************************** **********************
* Time Author Description
-------------------------------------------------- ----------------------------*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "sstarFb.h"

int fb_printf_base_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     struct fb_fix_screeninfo finfo;
     //Get screen fixed information
     if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo))
     {
         printf("Error reading fixed information/n");
         return -1;
     }
     printf("\r\n****************fb info****************\r\n");
     //Other parameters are either not supported or fixed. See the SDK documentation.
     printf("Device driver name: %s\r\n", finfo.id);
     printf("Video memory starting physical address: %p\r\n", finfo.smem_start);
     printf("Video memory size: %u\r\n", finfo.smem_len);
     printf("Number of bytes per line: %u\r\n", finfo.line_length);

     struct fb_var_screeninfo vinfo;
     long screensize = 0;
     //Get screen variable information
     if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
     {
         printf("Error reading variable information/n");
         return -1;
     }
     printf("Visible screen (number of pixels) width, height: (%u, %u)\r\n", vinfo.xres, vinfo.yres);
     printf("Virtual screen width, height: (%u,%u)\r\n", vinfo.xres_virtual, vinfo.yres_virtual);
     printf("Number of offset pixels in the (x,y) direction: (%u,%u)\r\n", vinfo.xoffset, vinfo.xoffset);
     printf("The number of bits occupied by each pixel: %u\r\n", vinfo.bits_per_pixel);
     printf("Bitfield information of (alpha, red, green, blue) in color components:\r\n{\r\n");
     printf("Component start bit: (%u,%u,%u,%u)\r\n", vinfo.transp.offset, vinfo.red.offset, vinfo.green.offset, vinfo.blue. offset);
     printf("The bit length occupied by the color component: (%u,%u,%u,%u)\r\n", vinfo.transp.length, vinfo.red.length, vinfo.green.length, vinfo.blue .length);
     printf("}\r\n");

     screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

     printf("Calculated: display requires %d(byte), the current frame has a total of %d buffers\n", screensize, finfo.smem_len / screensize);
     return 0;
}

int fb_printf_displayer_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     MI_FB_DisplayLayerAttr_t pstLayerInfo;
     //Get layer information
     if (ioctl(fd, FBIOGET_DISPLAYLAYER_ATTRIBUTES, &pstLayerInfo))
     {
         printf("Error reading FBIOGET_DISPLAYLAYER_ATTRIBUTES information/n");
         return -1;
     }
     printf("\r\nGet layer information:\r\n{\r\n");
     printf("The origin (horizontal, vertical) coordinates of the layer on the screen: (%u,%u)\r\n", pstLayerInfo.u32Xpos, pstLayerInfo.u32YPos);
     printf("Layer display on screen (width, height): (%u,%u)\r\n", pstLayerInfo.u32dstWidth, pstLayerInfo.u32dstHeight);
     printf("Video memory resolution (width, height): (%u,%u)\r\n", pstLayerInfo.u32DisplayWidth, pstLayerInfo.u32DisplayHeight);
     printf("Screen display resolution (width, height): (%u,%u)\r\n", pstLayerInfo.u32ScreenWidth, pstLayerInfo.u32ScreenHeight);
     printf("Whether the data in FB is premultiplied data: %u\r\n", pstLayerInfo.bPreMul);
     printf("Parameter modification mask bit when setting layer information: %u\r\n", pstLayerInfo.u32SetAttrMask);
     switch (pstLayerInfo.eFbColorFmt)
     {
     case E_MI_FB_COLOR_FMT_RGB565:
         printf("Current pixel format: RGB565 format\r\n");
         break;
     case E_MI_FB_COLOR_FMT_ARGB4444:
         printf("Current pixel format: ARGB444 format\r\n");
         break;
     case E_MI_FB_COLOR_FMT_ARGB8888:
         printf("Current pixel format: ARGB8888 format\r\n");
         break;
     case E_MI_FB_COLOR_FMT_ARGB1555:
         printf("Current pixel format: ARGB1555 format\r\n");
         break;
     case E_MI_FB_COLOR_FMT_YUV422:
         printf("Current pixel format: YUV422 format\r\n");
         break;
     default:
         printf("Current pixel format: invalid pixel format\r\n");
         break;
     }
     switch (pstLayerInfo.eFbOutputColorSpace)
     {
     case E_MI_FB_OUTPUT_RGB:
         printf("Output color format: RGB ColorSpace\r\n");
         break;
     case E_MI_FB_OUTPUT_YUV:
         printf("Output color format: YUV ColorSpace\r\n");
         break;
     default:
         printf("Output color format: ERROR\r\n");
         break;
     }
     //This interface is only valid for Ikayaki series chips
     //SStarFB overlay is output to the destination module of the display chain. By configuring different Display chains, you can choose which overlays participate in the image adjustment process.
     switch (pstLayerInfo.eFbDestDisplayPlane)
     {
     case E_MI_FB_DST_OP0:
         printf("Destination module of display chain: OP0\r\n");
         break;
     case E_MI_FB_DST_OP1:
         printf("Destination module of display chain: OP1\r\n");
         break;
     default:
         printf("Destination module of display chain: not supported\r\n");
         break;
     }
     printf("}\r\n");
     return 0;
}
int fb_printf_rectangl_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }
     MI_FB_Rectangle_t rectangl;
     //Get the area where the overlay is displayed on the screen
     if (ioctl(fd, FBIOGET_SCREEN_LOCATION, &rectangl))
     {
         printf("Error reading FBIOGET_SCREEN_LOCATION information/n");
         return -1;
     }
     printf("\r\nGet the area where the overlay is displayed on the screen:\r\n{\r\n");
     printf(" (Xpos,Ypos,Width,Height): (%u,%u,%u,%u)\r\n", rectangl.u16Xpos, rectangl.u16Ypos, rectangl.u16Width, rectangl.u16Height);
     printf("}\r\n");
     return 0;
}
int fb_printf_show_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     MI_BOOL bShow;
     // Get the overlay display status
     if (ioctl(fd, FBIOGET_SHOW, &bShow))
     {
         printf("Error reading FBIOGET_SHOW information/n");
         return -1;
     }
     printf("\r\nGet overlay display status:\r\n{\r\n");
     bShow == TRUE ? printf("The current overlay is in the displayed state\r\n") : printf("The current overlay is in the hidden state\r\n");
     printf("}\r\n");
     return 0;
}

int fb_printf_global_alpha_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     MI_FB_GlobalAlpha_t pstAlpha;
     //Alpha settings for the current overlay
     if (ioctl(fd, FBIOGET_GLOBAL_ALPHA, &pstAlpha))
     {
         printf("Error reading FBIOGET_GLOBAL_ALPHA information/n");
         return -1;
     }
     printf("\r\nCurrent overlay's Alpha setting:\r\n{\r\n");
     printf("Alpha overlay enable: %d\r\n", pstAlpha.bAlphaEnable);
     printf("Alpha channel enable: %d\r\n", pstAlpha.bAlphaChannel);
     //Alpha0 value, range 0~255, default is 255. In RGB1:5:5:5 format, when the highest bit is 0, this value is selected as the alpha value of the alpha overlay.
     printf("Alpha0 value: %d(0x%02x)\r\n", pstAlpha.u8Alpha0, pstAlpha.u8Alpha0);
     //Alpha1 value, range 0~255, default is 255. In RGB1:5:5:5 format, when the highest bit is 1, this value is selected as the alpha value of the alpha overlay.
     printf("Alpha1 value: %d(0x%02x)\r\n", pstAlpha.u8Alpha1, pstAlpha.u8Alpha1);
     printf("Global Alpha value: %d(0x%02x)\r\n", pstAlpha.u8GlobalAlpha, pstAlpha.u8GlobalAlpha);
     printf("}\r\n");

     return 0;
}

int fb_printf_color_key_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     MI_FB_ColorKey_t pstColorKey;
     //Get the colorkey of the overlay
     if (ioctl(fd, FBIOGET_COLORKEY, &pstColorKey))
     {
         printf("Error reading FBIOGET_COLORKEY information/n");
         return -1;
     }
     printf("\r\nLayer colorkey information:\r\n{\r\n");
     printf("Colorkey is enabled: %d\r\n", pstColorKey.bKeyEnable);
     printf(" (R:G:B):(0x%02x:0x%02x:0x%02x)\r\n", pstColorKey.u8Red, pstColorKey.u8Green, pstColorKey.u8Blue);
     printf("}\r\n");
     return 0;
}

int fb_printf_cursor_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     MI_FB_CursorAttr_t pstCursorAttr;
     //Get mouse layer information
     if (ioctl(fd, FBIOGET_CURSOR_ATTRIBUTE, &pstCursorAttr))
     {
         printf("Error reading FBIOGET_CURSOR_ATTRIBUTE information/n");
         return -1;
     }
     printf("\r\nGet mouse layer information:\r\n{\r\n");
     printf("Mouse position (horizontal, vertical) coordinates: (%u,%u)\r\n", pstCursorAttr.u32XPos, pstCursorAttr.u32YPos);
     printf("Mouse hot spot (horizontal, vertical) coordinates: (%u,%u)\r\n", pstCursorAttr.u32HotSpotX, pstCursorAttr.u32HotSpotY);
     printf("Is the mouse visible: %d\r\n", pstCursorAttr.bShown);
     printf("Set mouse layer parameter modification mask bit: %d\r\n", pstCursorAttr.u16CursorAttrMask);
     printf("\r\n Mouse layer alpha information:\r\n {\r\n");
     printf("Alpha overlay enable: %d\r\n", pstCursorAttr.stAlpha.bAlphaEnable);
     printf("Alpha channel enable: %d\r\n", pstCursorAttr.stAlpha.bAlphaChannel);
     //Alpha0 value, range 0~255, default is 255. In RGB1:5:5:5 format, when the highest bit is 0, this value is selected as the alpha value of the alpha overlay.
     printf("Alpha0 value: %d(0x%02x)\r\n", pstCursorAttr.stAlpha.u8Alpha0, pstCursorAttr.stAlpha.u8Alpha0);
     //Alpha1 value, range 0~255, default is 255. In RGB1:5:5:5 format, when the highest bit is 1, this value is selected as the alpha value of the alpha overlay.
     printf("Alpha1 value: %d(0x%02x)\r\n", pstCursorAttr.stAlpha.u8Alpha1, pstCursorAttr.stAlpha.u8Alpha1);
     printf("Global Alpha value: %d(0x%02x)\r\n", pstCursorAttr.stAlpha.u8GlobalAlpha, pstCursorAttr.stAlpha.u8GlobalAlpha);
     printf(" }\r\n");
     printf("\r\n Mouse layer colorkey information:\r\n {\r\n");
     printf("Colorkey is enabled: %d\r\n", pstCursorAttr.stColorKey.bKeyEnable);
     printf(" (R:G:B):(0x%02x:0x%02x:0x%02x)\r\n", pstCursorAttr.stColorKey.u8Red, pstCursorAttr.stColorKey.u8Green, pstCursorAttr.stColorKey.u8Blue);
     printf(" }\r\n");
     printf("\r\n Icon data information:\r\n {\r\n");
     printf("Mouse (width, height, pitch): (%u,%u,%u)\r\n", pstCursorAttr.stCursorImageInfo.u32Width, pstCursorAttr.stCursorImageInfo.u32Height, pstCursorAttr.stCursorImageInfo.u32Pitch);
     printf(" }\r\n");
     printf("}\r\n");
     return 0;
}

int fb_printf_proc_mi_info(int fd)
{
     if (fd < 0)
     {
         printf("%s Error :fb < 0 \r\n", __func__);
         return -1;
     }

     printf("\r\ncat /proc/mi_modules/fb/mi_fb0\r\n");
     system("cat /proc/mi_modules/fb/mi_fb0");
     return 0;
}