# illustrate
During the development process, it is often necessary to copy the application to the board and run it. If you package it through the project image and then download it, it will be a waste of time and unnecessary. Here are a few that can be found on the public board SDK** Directly implement the method of copying applications.

## Copy via USB/SD card
- This method is slower and more time-consuming to debug.

1. Copy the application to USB/SD card
2. Insert the USB/SD card into the board
3. Mount the USB/or SD card. The commands can be referenced as follows:
```shell
# Mount the SD card. When /dev/mmcblk0p1 inserts the SD card and connects to USB, the corresponding log will be displayed.
mkdir /customer/sd
mount -t vfat /dev/mmcblk0p1 /customer/sd/
```
4. After the mounting is completed, just cp your own application to the board.


## Copy via network
- Set the board IP, and then use the existing shell command to implement the download/upload function of the application
- The network port configuration method is as follows
```shell
# Automatically obtain ip using dhcpc method
ifconfig eth0 up
ifconfig eth0 hw ether 00:70:27:00:00:01
udhcpc -i eth0 -s /etc/init.d/udhcpc.script

# Set static ip
ifconfig eth0 up
ifconfig eth0 172.19.24.186 netmask 255.255.255.0
ifconfig eth0 hw ether 00:70:27:00:00:01
```
- It is also possible through wifi, but wifi configuration is relatively complicated and will not be explained in detail here.

#### 1. Download through wget command
- The wget command can download files from http. The command is as follows `wget http://192.168.204.174:8888/http-server.bin`
- The premise is that the host of 192.168.204.174 needs to have the http server service of port 8888 enabled.
- There are many ways to open the http server service. You can use Baidu. Here is a simple python command to quickly open the http server.

```shell
# On the window, after installing python3, use ``win+R` to open the `cmd` port and enter the following command to open the http server service in the current folder of the terminal.
# The ip address is your own windows ip address
python -m http.server 8888

# On ubuntu, you can directly run the following command to start the http server service in the current folder.
python3 -m http.server 8888
```
#### 2. Download via tftp command
- tftp download command such as `tftp -g -l songti.ttf -r songti.ttf 192.168.204.174`
- The premise is that the tftp service needs to be turned on. How to turn on the tftp service on Baidu in Ubuntu class?
- On Windows, in the SDK, there is the `Tftpd32.rar` application. Open it, set the IP, and set the folder.
- ps: Upload command: `tftp -p -l songti.ttf -r songti.ttf 192.168.204.174`

#### 3. Download via nfs command
- nfs download command such as `:mount -t nfs -o nolock 192.168.204.174:/h/tmp tmp`
- The premise is that the nfs service needs to be turned on. You can learn how to turn on the nfs service on Baidu in Ubuntu.
- On windows, in the SDK, there is the `win_nfs.rar` application, just open the settings and set the folder.
- After this method is configured, it is the most convenient to use
