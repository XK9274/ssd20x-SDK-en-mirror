# SSD202 wifi test command
## After executing the following commands in sequence, you can connect to the wifi with the account SKY and the password 12345678
## Notice
- If each command returns FAIL, it proves that the command is wrong. You need to pay attention to adjusting the command.
### 0. Environment preparation
- Execute in sequence
1. `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/customer/lib:/customer/libdns:/lib:/config/wifi/`
2. `/config/wifi/ssw01bInit.sh`

### 1. Start wifi
`/config/wifi/wpa_supplicant -iwlan0 -Dnl80211 -c/appconfigs/wpa_supplicant.conf -B`

### 2. Scan ap
`/config/wifi/wpa_cli -i wlan0 scan -p /tmp/wifi/run/wpa_supplicant/`

### 3. Get the scan results (check whether the wifi to be connected is found, and check the signal strength. If it is too weak, you may not be able to connect)
`/config/wifi/wpa_cli -i wlan0 scan_result -p /tmp/wifi/run/wpa_supplicant`

![wifi2](https://gitee.com/mFlying/flying_picgo_img/raw/master/PicGo-updata-img/wifi2.png)
### 4. Add network - you must remember that the return value will be useful later (`assuming the return value is 0`)
`/config/wifi/wpa_cli -i wlan0 add_network -p /tmp/wifi/run/wpa_supplicant/`

### 5. Set the ssid to be connected
- The network is 0, which was obtained just now. SKY is ssid (wifi name)

`/config/wifi/wpa_cli -i wlan0 set_network 0 ssid '"SKY"' -p /tmp/wifi/run/wpa_supplicant/`

### 6. Set the wifi password to connect to
- The network is 0, which was obtained just now. 12345678 is the wifi password

`/config/wifi/wpa_cli -i wlan0 set_network 0 psk '"12345678"' -p /tmp/wifi/run/wpa_supplicant/`

### 7. Select network,
`/config/wifi/wpa_cli -i wlan0 select_network 0 -p /tmp/wifi/run/wpa_supplicant/`

### 8. Enable network
`/config/wifi/wpa_cli -i wlan0 enable_network 0 -p /tmp/wifi/run/wpa_supplicant/`

### 9. Turn on wifi dhcp to automatically connect and obtain ip
`udhcpc -q -i wlan0 -s /etc/init.d/udhcpc.script &`

### 10. Save the configuration just now
`/config/wifi/wpa_cli -i wlan0 save_config -p /tmp/wifi/run/wpa_supplicant/`

### 11. Check whether the wifi connection is successful
`ifconfig`
- If the IP appears on wlan0, it proves that the connection is successful.
![wifi1](https://gitee.com/mFlying/flying_picgo_img/raw/master/PicGo-updata-img/wifi1.png)
