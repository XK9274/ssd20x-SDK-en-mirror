# Summary
```
1. dtsi configures the corresponding pin into normal IO mode
like:
<PAD_PM_LED0 PINMUX_FOR_GPIO_MODE MDRV_PUSE_NA>,
<PAD_PM_LED1 PINMUX_FOR_GPIO_MODE MDRV_PUSE_NA>,

2. Then enter /sys/class/gpio to directly operate the file.
Here's a summary:
direction
     Set output or input mode
     Set as input: echo “in” > direction
     Set as output: echo "out" > direction
value
     When outputting, control the high and low levels; when inputting, obtain the high and low levels.
     High level: echo 1 > value
     Low level: echo 0 > value
edge
     Control the interrupt trigger mode. After the pin is configured as an interrupt, you can use the poll() function to monitor the pin.
     Non-interrupt pin: echo “none” > edge
     Rising edge trigger: echo “rising” > edge
     Falling edge trigger: echo “falling” > edge
     Edge trigger: echo “both” > edge

3. Currently, only rising edge or falling edge triggering is supported. Edge triggering is not supported.

4. Poll monitoring can be used in user mode

```
### common
- Universal gpio interface

### gpio_test1
- Simply call the system interface to control the high and low levels of gpio output


### gpio_test2
- Call the encapsulated general interface to control the high and low levels of gpio output

### gpio_test_input
- Call the encapsulated general interface to detect key input through interrupts.
- Interrupt does not support edge triggering. . Platform driver issues


### gpio_test_fast_rollover
- Verification test on SSD20x V030
- Directly call registers to achieve fast flipping
- Register operation reference `kernel/drivers/sstar/samples/riu.c`
- Register view data sheet
- By operating registers, the flip speed can reach 21.6MHz
- Key: bit5: (0: output, 1: input) bit4 (0: output low level, 1: output high level) bit0: (level value read by the current IO port)
-eg:
```
#shell command can control gpio as follows

#Control gpio43 (TTL24)
     Pull high: riu_w 0x103C 0x38 0x0010
     Pull low: riu_w 0x103C 0x38 0x0000
#Control gpio11 (SPI0_DO)
     Pull high: riu_w 0x103C 0x0b 0x0010
     Pull low: riu_w 0x103C 0x0b 0x0000
```
