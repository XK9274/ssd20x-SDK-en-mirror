# Summary
- You need to enable the wifi function and have wifi related libraries and tools.

## wifi_demo1
- SSD202 - SDK verification for v030 version
- Interface using MI WLAN
- blocking
- Connection timeout is 10 seconds

```shell
# Indicates that the name of the wifi that needs to be operated is xxxxx and the password is 12345678
# The name of the created ap is: xxxxx_ssd2xx
./wifi_demo1 xxxxx 12345678

Enter ‘m’ to switch STA/AP mode, the default is STA mode;
printf("please input option command:\n");
printf("m. switch STA/AP mode, input 'm'\n");
printf("c. connect wifi hotspot, input 'n'\n");
printf("d. disconnect wifi hotspot, input 'd'\n");
printf("p. print wifi hotspot's info, input 'p'\n");
printf("h. help\n");
printf("q. exit, input 'q'\n\n");
```

## wifi_sta_saync
- SSD202 - SDK verification for v030 version
- Interface using MI WLAN
- Connect to wifi asynchronously
- MI interfaces are all blocking, so a thread is opened in the DMEO to specifically handle wifi configuration, and then returned to the main thread through the callback function.
- Use the interface to common-list

```shell
# When wifi is opened successfully, you will be prompted to enter the following command. Just follow the prompts
./wifi_sta_saync

     printf("please input option command:\n");
     printf("g. Scan wifi\n");
     printf("c. Connect to wifi, then enter as prompted\n");
     printf("d. Manually disconnect wifi\n");
```
