#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <poll.h>
#include <string.h>
#include <pthread.h>
#include "uart_cfg.h"

#define UART_PATH "/dev/ttyS1"

static void *uart_recv_pthread(void *pdata)
{
     int fd = (int)pdata;
     int ret = -1;
     nfds_t nfds = 1; //Specify the number of items in the fds array
     struct pollfd fds[1]; // Specify the file descriptor set to be monitored
     int total_data_len = 0; // length of read data
     int remain_data_len = 0; // Unread data length
     uint8_t recv_data[1024] = {0};
     uint32_t recv_data_len = 1023;

     while (1)
     {
         //Set the file descriptor to be monitored
         memset(fds, 0, sizeof(fds));
         fds[0].fd = fd;
         fds[0].events = POLLIN;

         ret = poll(fds, nfds, 500); //500ms timeout
         if (ret < 0)
         {
             perror("Error: poll");
             return NULL;
         }
         //return 0, timeout
         else if (0 == ret)
         {
             // If after timeout, the read data length is greater than 0, return the actual received data length
             if (total_data_len > 0)
             {
                 printf("recv: %s\r\n", recv_data);
                 memset(recv_data, 0, sizeof(recv_data));
                 total_data_len = 0;
                 remain_data_len = 0;
             }

             continue;
         }

         // Determine whether it is the expected return
         if (fds[0].revents & POLLIN)
         {
             //Start reading data from the beginning of the file
             lseek(fds[0].fd, 0, SEEK_SET);
             ret = uart_read_data(fds[0].fd, &recv_data[total_data_len],remain_data_len);
             if (ret < 0)
             {
                 perror("Error: serial read error");
                 continue;
             }

             total_data_len += ret;
             remain_data_len = (recv_data_len - total_data_len);

             //Last received\nor successful reception when the data is too long
             if (total_data_len == recv_data_len || recv_data[total_data_len - 1] == '\n')
             {
                 printf("recv: %s\r\n", recv_data);
                 memset(recv_data, 0, sizeof(recv_data));
                 total_data_len = 0;
                 remain_data_len = 0;
                 continue;
             }
         }
     }
}

int main(int argc, char **argv)
{
     int fd = -1;
     int reg;
     fd = uart_open(UART_PATH, UART_BAUD_RATE_115200, UART_DATA_BIT_8, UART_PARITY_BIT_NONE, UART_STOP_BIT_1);
     if (fd < 0)
     {
         printf("Error : OPEN %s fail\r\n", UART_PATH);
         return -1;
     }

     uart_write_buff(fd, "\r\n uart init success: ");
     pthread_t g_pt;

     pthread_create(&g_pt, NULL, uart_recv_pthread, (void *)fd);
     if (g_pt <= 0)
     {
         printf("Error: create check uart thread failed\n");
         return -1;
     }

#if 1
     char buff[1024];
     while (1)
     {
         printf("send: ");
         scanf("%s", buff);
         uart_write_buff(fd, buff);
     }
#else
     while (1)
     {
         printf("You can open the process and background mode (eg: %s &), and then use top to check the CPU usage\r\n", argv[0]);
         sleep(1);
     }
#endif
     return 0;
}