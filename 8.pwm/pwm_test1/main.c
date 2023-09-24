#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
     //PWM1(GPIO5)
     system("echo 1 > /sys/class/pwm/pwmchip0/export");
     system("echo 2000 > /sys/class/pwm/pwmchip0/pwm1/period");
     system("echo 100 > /sys/class/pwm/pwmchip0/pwm1/duty_cycle"); //Duty cycle 100%
     system("echo 1 > /sys/class/pwm/pwmchip0/pwm1/enable");

     //PWM0(GPIO4)
     system("echo 0 > /sys/class/pwm/pwmchip0/export");
     system("echo 2000 > /sys/class/pwm/pwmchip0/pwm0/period"); //frequency 2kHz
     system("echo 60 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle"); //Duty cycle 30%
     system("echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable"); //Enable
     for(int i=0;i<100;i++){
         char buff[100];
         sprintf(buff,"echo %d > /sys/class/pwm/pwmchip0/pwm0/duty_cycle",i);
         system(buff);
         usleep(10*1000);
     }
     system("echo 50 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle");

     sleep(2);
      system("echo 0 > /sys/class/pwm/pwmchip0/pwm0/enable"); //Cancel enable
      system("echo 0 > /sys/class/pwm/pwmchip0/pwm1/enable");
      system("echo 1 > /sys/class/pwm/pwmchip0/unexport"); //Export
      system("echo 0 > /sys/class/pwm/pwmchip0/unexport");
     return 0;
}