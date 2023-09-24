# Summary
- Refer to SDK UART documentation.
- SSD20x pinout
```shell
# The current correspondence between the four UARTs on the public version of the demo board is as follows:
 
make infinity2m_spinand_ssc011a_s01a_minigui_defconfig
vim arch/arm/boot/dts/infinity2m-ssc011a-s01a-padmux-display.dtsi

<PAD_FUART_RX PINMUX_FOR_FUART_MODE_2 MDRV_PUSE_FUART_RX >,
<PAD_FUART_TX PINMUX_FOR_FUART_MODE_2 MDRV_PUSE_FUART_TX >,
<PAD_UART1_RX PINMUX_FOR_UART1_MODE_1 MDRV_PUSE_UART1_RX >,
<PAD_UART1_TX PINMUX_FOR_UART1_MODE_1 MDRV_PUSE_UART1_TX >,
<PAD_GPIO8 PINMUX_FOR_UART2_MODE_2 MDRV_PUSE_UART2_RX>,
<PAD_GPIO9 PINMUX_FOR_UART2_MODE_2 MDRV_PUSE_UART2_TX>,
# PM_UART is the terminal serial port. It has been configured by default and no additional configuration is required.
<PAD_PM_UART_RX PINMUX_FOR_UART0_MODE_0 MDRV_PUSE_UART0_RX>,
<PAD_PM_UART_TX PINMUX_FOR_UART0_MODE_0 MDRV_PUSE_UART0_TX>,
```

- SSD2X2 serial port pins

| UART | Group | Mode | TX | RX | CT | RTS | DEV |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| Fuart | 6 | PAD_GPIO5 | PAD_GPIO6 | PAD_GPIO7 | PAD_GPIO8 | /dev/ttyS2 |
| Uart1 | 8 |PAD_GPIO1| PAD_GPIO2 |-- |--| /dev/ttyS1|
| Uart2 | 6 |PAD_GPIO3| PAD_GPIO4 | -- |--| /dev/ttyS3|

- The driver and device tree in the kernel require corresponding configurations

### common
- Universal uart interface

### uart_test1
- Simply call the system interface to control pwm
- uart simple sending and receiving

### uart_test2
- Called the encapsulated uart interface implementation to implement sending and receiving
- Using polling to receive data will occupy a lot of CPU. You can hang it in the background and then use the `top` command to check the CPU usage.

### uart_test3_poll
- Called the encapsulated uart interface implementation to implement sending and receiving
- A receiving thread is opened to receive serial port data.
- Poll IO multiplexing is used to ensure timely collection of data and effectively reduce CPU usage.
- When the last character received is '\n' || The data exceeds 1023 bytes || When no other data is received for 500ms, print the data received

### uart_test4_signal
- Called the encapsulated uart interface implementation to implement sending and receiving
- Receive serial port data in interrupt mode
- If no data is received, the thread sleeps permanently. When there is data, an interrupt will be triggered and sleep will stop.
