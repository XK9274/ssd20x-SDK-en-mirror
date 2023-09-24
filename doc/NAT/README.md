# 1. Introduction to NAT
- NAT (Network Address Translation) was proposed in 1994. When some hosts within the private network have been assigned local IP addresses (that is, private addresses used only within this private network), but want to communicate with hosts on the Internet (without encryption), the NAT method can be used .
## 1.1, Reference
1. [ARM WIFI AP mode uses iptables nat forwarding to access the Internet through LAN cable](https://www.cnblogs.com/ningci/p/6834640.html)

2. [iptables cross-compilation](https://www.cnblogs.com/eleclsc/p/11686287.html)

3. [Network Address Translation NAT Principle](https://blog.csdn.net/weixin_38044696/article/details/80282162)

4. [iptables detailed explanation](https://blog.csdn.net/wangyunfeis/article/details/77725964)


# 2. Linux dual network card configuration packet forwarding
- This article mainly introduces the use of iptables to implement the NAT function under the Linux platform. In the traditional standard TCP/IP communication process, all routers only act as a middleman, which is commonly known as store and forward. The router does not modify the forwarded data packets. To be more precise, The router will not make any modifications to the forwarded packets except changing the source MAC address to its own MAC address.
- NAT (Network Address Translation) is an operation that rewrites the source IP address, destination IP address, source port, and destination port of the data packet for some special needs. Change the address information in the internal network data packets into unified external address information to prevent the internal network hosts from being directly exposed to the Internet to ensure the security of the internal network hosts. At the same time, this function is also commonly used to achieve shared Internet access.
![net1](https://gitee.com/mFlying/flying_picgo_img/raw/master/PicGo-updata-img/net1.png)
- When the IP packet passes through the NAT gateway, the NAT Gateway will convert the source IP of the IP packet to the public IP of the NAT Gateway and forward it to the public network. At this time, the IP packet (Dst=202.20.65.4, Src=202.20.65.5) has It does not contain any private network IP information. Since the source IP of the IP packet has been converted to the public IP of the NAT Gateway, the response IP packet (Dst= 202.20.65.5, Src=202.20.65.4) sent by the Web Server will be sent to the NAT Gateway.
---------------
- Netfilter/IPTables is a subsystem introduced after Linux 2.4.x. Its important tool module IPTables is connected from iptables in user mode to Netfilter in kernel mode. Netfilter and
The IP protocol stack is seamless and allows users to filter, address translate (NAT), and process datagrams. iptables is an application that can configure netfilter (packet filtering
rules, NAT, etc.).
![net2](https://gitee.com/mFlying/flying_picgo_img/raw/master/PicGo-updata-img/net2.png)
- This picture intuitively reflects the relationship and communication methods between iptables in user space and Netfilter-based ip_tables module in kernel space, as well as the role Netfilter plays in this.
---------------
- Therefore, to implement NAT on the Linux platform, we must start from two aspects:
    - 1) The kernel supports netfilter
    - 2) User layer iptables configuration command
    - **Netfilter** is a function in the official kernel that provides filtering and modification of message packets. It is located in the message processing framework of the tcp/ip protocol stack in the kernel. It can be used to add certain hooks at different stages. Function (hook) scope network protocol stack. Netfilter itself does not filter data packets, it only allows functions that can filter data packets or modify data packets to be hooked into the appropriate location in the kernel network protocol stack. These functions are customizable.
    - **iptables** is a user-level tool. It provides a command line interface and can add rules and policies to Netfilter to implement packet filtering, modification and other functions. There are many such tools in Linux. On centos6, it is iptables, and on centos7, it is firewalld. However, on centos 7, it is still called iptables according to custom.
    - It can be simply understood that when we travel by car, Netfilter is the car, and iptables is the person sitting in the car. The car does not have the ability to select routes, but a car can provide the ability to drive and change routes, and decide whether to drive or not. Where you drive is determined by the person sitting in the car.
## 2.1, SSD20X kernel configuration, kernel support netfilter
- SDK V030 version
- kernel configuration
```
Linux Kernel Configuration
     -> Networking support
         -> Networking options
             -> Network packet filtering framework(netfilter)
                 -> Core netfilter configuration
                     -> Netfilter connection tracking support
                     -> NetBIOS name service protocol support
                     -> Netfilter Xtables support (required for ip_tables)


Linux Kernel Configuration
     -> Networking support
         -> Networking options
             -> Network packet filtering framework(netfilter)
                 -> IP: Netfilter Configuration
                     -> IPv4 connection tracking support (require for NAT)
                     -> IPv4 NAT
                     -> IP tables support (required for filtering/masq/NAT)
                     -> iptables NAT support
                          ->MASQUERADE target support
                          ->NETMAP target support
                          ->REDIRECT target support
                     -> raw table support (required for NOTRACK/TRACE)
```

## 2.2. Configuration and use of iptables
#### 2.2.1. Source code download
- Use git to download the latest release version under ubuntu.
```
git clone git://git.netfilter.org/iptables
cd iptables/
# git tag can view the latest release version
git checkout v1.8.7
```

#### 2.2.2. Cross compilation
- SSD20X as an example
- Enter iptables, execute autogen.sh (`./autogen.sh`), and get the configure file.
- Execute the command as follows

```
./autogen.sh
mkidr build
./configure --enable-static --prefix=$PWD/build CC=arm-linux-gnueabihf-gcc --host=arm-linux-gnueabihf --disable-nftables --disable-shared
make -j8
make install
```
-The compiled files can then be seen in the build folder. The main file is sbin and has been copied to the iptables_sbin folder in the current document.

#### 2.2.3. Instructions for use
- The compiled file is in bin/sbin under the current path. The final file is xtables-legacy-multi, but xtables-legacy-multi cannot be run directly. A soft connection must be established or renamed to iptables.
- Basic parameters and usage of iptables command:
    - iptables –[A|I chain] [-i|o network interface] [-p protocol] [-s source ip/domain] [-d target ip/domain] –j[ACCEPT|DROP]
    - Details Baidu
    - eg: View the current NAT table `./iptables -t nat -L`
