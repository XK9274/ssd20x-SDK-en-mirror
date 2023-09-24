/**
  * @copyright : Copyright (c) 2020 Hu Enrong
  */
#include "gpio_cfg.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// gpio path
#define SYS_GPIO_DIR "/sys/class/gpio"

//Maximum length of command buf
#define CMD_BUF_MAX_LEN 60

/**
  * @brief Export gpio to user space
  * @param gpio_num: input parameter, gpio number to be exported
  * @return success: 0
  * Failure: -1
  */
int gpio_export(const uint16_t gpio_num)
{
     int ret = -1;
     int fd = -1;
     int len = 0;
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio has been exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf),
              "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio has been exported, return directly
     if (0 == ret)
     {
         return 0;
     }

     //Open file: /sys/class/gpio/export
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/export", SYS_GPIO_DIR);
     fd = open(cmd_buf, O_WRONLY);
     if (fd < 0)
     {
         return -1;
     }

     //Write information in the export file and write the gpio number to be exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", gpio_num);
     ret = write(fd, cmd_buf, len);
     if (-1 == ret)
     {
         close(fd);

         return -1;
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Cancel gpio exported to user space
  * @param gpio_num: input parameter, the gpio number to be cancelled.
  * @return success: 0
  * Failure: -1
  */
int gpio_unexport(const uint16_t gpio_num)
{
     int ret = -1;
     int fd = -1;
     int len = 0;
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio is exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio is not exported, return directly
     if (-1 == ret)
     {
         return 0;
     }

     //Open file: /sys/class/gpio/unexport
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/unexport", SYS_GPIO_DIR);
     fd = open(cmd_buf, O_WRONLY);
     if (fd < 0)
     {
         return -1;
     }

     //Write information in the export file, write the GPIO number to be cancelled.
     memset(cmd_buf, 0, sizeof(cmd_buf));
     len = snprintf(cmd_buf, sizeof(cmd_buf), "%d", gpio_num);
     ret = write(fd, cmd_buf, len);
     if (-1 == ret)
     {
         close(fd);

         return -1;
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Set gpio direction
  * @param gpio_num: input parameter, gpio number to be set
  * @param direction: input parameter, gpio direction to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_direction(const uint16_t gpio_num,
                        const enum gpio_direction direction)
{
     int fd = -1; // file descriptor
     int ret = -1; // function return value
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio is exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio is not exported, return directly
     if (-1 == ret)
     {
         return -1;
     }

     //Open file: /sys/class/gpio/gpiox/direction
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf),
              "%s/gpio%d/direction", SYS_GPIO_DIR, gpio_num);
     fd = open(cmd_buf, O_WRONLY);
     if (fd < 0)
     {
         return -1;
     }

     switch (direction)
     {
     // Set to input mode
     case GPIO_IN:
     {
         ret = write(fd, "in", 3);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     // Set to output mode
     case GPIO_OUT:
     {
         ret = write(fd, "out", 4);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     default:
     {
         return -1;
     }
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Set the gpio output level value
  * @param gpio_num: input parameter, gpio number to be set
  * @param value: input parameter, gpio level value to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_value(const uint16_t gpio_num, const enum gpio_value value)
{
     int ret = -1;
     int fd = -1;
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio is exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio is not exported, return directly
     if (-1 == ret)
     {
         return -1;
     }

     //Open file: /sys/class/gpio/gpiox/value
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf),
              "%s/gpio%d/value", SYS_GPIO_DIR, gpio_num);
     fd = open(cmd_buf, O_WRONLY);
     if (fd < 0)
     {
         perror("gpio_set_value");

         return -1;
     }

     switch(value)
     {
     //Set the output low level
     case GPIO_LOW:
     {
         ret = write(fd, "0", 2);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     //Set the output high level
     case GPIO_HIGH:
     {
         ret = write(fd, "1", 2);
         if (-1 == ret)
         {
             close(fd);
             return -1;
         }

         break;
     }

     default:
     {
         return -1;
     }
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Get the level value of gpio
  * @param value: gpio level value
  * @param gpio_num: gpio number
  * @return success: 0
  * Failure: -1
  */
int gpio_get_value(enum gpio_value *value, const uint16_t gpio_num)
{
     int ret = -1;
     int fd = -1;
     char ch = 0; // Obtained gpio level value
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio is exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio is not exported, return directly
     if (-1 == ret)
     {
         return -1;
     }

     //Open file: /sys/class/gpio/gpiox/value
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf),
              "%s/gpio%d/value", SYS_GPIO_DIR, gpio_num);
     fd = open(cmd_buf, O_RDONLY);
     if (fd < 0)
     {
         return -1;
     }

     // Get gpio level value
     ret = read(fd, &ch, 1);
     if (-1 == ret)
     {
         close(fd);

         return -1;
     }

     //Return data based on the obtained level value
     switch (ch)
     {
     case '0':
     {
         *value = GPIO_LOW;

         break;
     }

     case '1':
     {
         *value = GPIO_HIGH;

         break;
     }

     default:
     {
         close(fd);

         return -1;
     }
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Set gpio trigger edge
  * @param gpio_num: input parameter, gpio number to be set
  * @param edge: input parameter, gpio edge to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_edge(const uint16_t gpio_num, const enum gpio_edge edge)
{
     int ret = -1;
     int fd = -1;
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     // Determine whether gpio is exported
     memset(cmd_buf, 0, sizeof(cmd_buf));
     snprintf(cmd_buf, sizeof(cmd_buf), "%s/gpio%d", SYS_GPIO_DIR, gpio_num);
     ret = access(cmd_buf, F_OK);
     // gpio is not exported, return directly
     if (-1 == ret)
     {
         return -1;
     }

     //Open file: /sys/class/gpio/gpiox/edge
     memset(cmd_buf, 0, sizeof(cmd_buf));
     ret = snprintf(cmd_buf, sizeof(cmd_buf),
                    "%s/gpio%d/edge", SYS_GPIO_DIR, gpio_num);
     fd = open(cmd_buf, O_WRONLY);
     if (fd < 0)
     {
         return -1;
     }

     switch (edge)
     {
     // Not an interrupt
     case GPIO_NONE:
     {
         ret = write(fd, "none", strlen("none") + 1);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     //Interrupt input, rising edge
     case GPIO_RISING:
     {
         ret = write(fd, "rising", strlen("rising") + 1);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     //Interrupt input, falling edge
     case GPIO_FALLING:
     {
         ret = write(fd, "falling", strlen("falling") + 1);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     //Interrupt input, rising edge and falling edge
     case GPIO_BOTH:
     {
         ret = write(fd, "both", strlen("both") + 1);
         if (-1 == ret)
         {
             close(fd);

             return -1;
         }

         break;
     }

     default:
     {
         return -1;
     }
     }

     // close file
     ret = close(fd);
     if (-1 == ret)
     {
         return -1;
     }

     return 0;
}

/**
  * @brief Open gpio device
  * @param gpio_num: input parameter, gpio number to be opened
  * @return success: return device file descriptor
  * Failure: -1
  */
int gpio_open(const uint16_t gpio_num)
{
     int fd = -1;
     char cmd_buf[CMD_BUF_MAX_LEN] = {0};

     snprintf(cmd_buf, sizeof(cmd_buf),
              "%s/gpio%d/value", SYS_GPIO_DIR, gpio_num);

     fd = open(cmd_buf, O_RDONLY | O_NONBLOCK);
     if (fd < 0)
     {
         return -1;
     }

     return fd;
}

/**
  * @brief Close gpio device
  * @param fd: input parameter, device file descriptor to be closed
  * @return success: 0
  * Failure: -1
  */
int gpio_close(const int fd)
{
     int ret = -1;

     ret = close(fd);

     return ret;
}
             