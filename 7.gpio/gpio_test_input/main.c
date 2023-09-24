#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gpio_cfg.h"

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <poll.h>

#include "gpio_cfg.h"

// gpio pin definition
#define GPIO_LED 10
#define GPIO_KEY 11

//LED status control
#define LED_ON() gpio_set_value(GPIO_LED, GPIO_LOW)
#define LED_OFF() gpio_set_value(GPIO_LED, GPIO_HIGH)

int main(int argc, char *argv[])
{
     int fd = -1;
     int ret = -1;
     nfds_t nfds = 1; //Specify the number of items in the fds array
     struct pollfd fds[1]; // Specify the file descriptor set to be monitored
     int timeout = 0; // poll timeout (unit: milliseconds)
     char gpio_ch = 0; // read gpio value
     uint8_t cnt = 0; // Record the number of reads

     //Export each gpio
     gpio_export(GPIO_LED);
     gpio_export(GPIO_KEY);

     //Set gpio direction
     gpio_set_direction(GPIO_LED, GPIO_OUT);
     gpio_set_direction(GPIO_KEY, GPIO_IN);

     //Set gpio falling edge trigger --SSD2xx does not support edge trigger
     gpio_set_edge(GPIO_KEY, GPIO_FALLING);

     // Turn off the LED and buzzer
     LED_OFF();

     //Open the device
     fd = gpio_open(GPIO_KEY);
     if (-1 == fd)
     {
         perror("open gpio key fail");

         return -1;
     }

     // Determine whether the button is pressed
     while (1)
     {
         //Set the timeout to 1s
         timeout = (1 * 1000);

         //Set the file descriptor to be monitored
         // When monitoring gpio, events need to use POLLPRI (indicating that there is urgent data that needs to be read), POLLIN cannot be used
         memset(fds, 0, sizeof(fds));
         fds[0].fd = fd;
         fds[0].events = POLLPRI;

         ret = poll(fds, nfds, timeout);
         // Return a negative value, an error occurred
         if (ret < 0)
         {
             perror("poll error");

             return -1;
         }
         //return 0, timeout
         else if (0 == ret)
         {
             continue;
         }
         //The return value is greater than 0, success
         else
         {
             // Determine whether it is the expected return
             if (fds[0].revents & POLLPRI)
             {
                 //Start reading data from the beginning of the file
                 lseek(fds[0].fd, 0, SEEK_SET);
                 ret = read(fds[0].fd, &gpio_ch, 1);
                 if ((1 == ret) && (cnt > 0))
                 {
                     usleep(20 * 1000); //Button debounce

                     enum gpio_value value = GPIO_LOW;
                     gpio_get_value(&value, GPIO_KEY);
                     // Release the button (rising edge), turn off the LED, and turn off the buzzer
                     if ((GPIO_HIGH == value) && (0x31 == gpio_ch))
                     {
                         printf("release button\n");

                         // Turn off the LED
                         LED_OFF();
                     }
                     // Press the button (falling edge), light the LED, and turn on the buzzer
                     else
                     {
                         printf("press button\n");

                         //Light up the LED
                         LED_ON();
                     }
                     cnt = 0; // Clear the number of reads
                 }
                 cnt++; // Add after judgment to prevent execution after first reading
             }
         }
     }

     gpio_close(fd);

     return 0;
}