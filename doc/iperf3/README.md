# Introduction
- Perf3 is a tool that actively measures the maximum achievable bandwidth on an IP network. It supports tuning of various parameters related to time, buffers and protocols (TCP, UDP, SCTP with IPv4 and IPv6). For each test, it reports bandwidth, loss, and other parameters. This is a new implementation that does not share code with the original iPerf and is not backwards compatible. iPerf was originally developed by NLANR/DAST.
- Official website: https://iperf.fr/
- Source code download path (you can also find it on the official website): https://github.com/esnet/iperf/releases
- The following takes the current (2021-09-01) latest release version as an example (3.10.1)

# Cross compile
## environment
-ubuntu20.04
- Cross-compilation tool arm-linux-gnueabihf-gcc 8.2.1 20180802 (GNU Toolchain for the A-profile Architecture 8.2-2018-08 (arm-rel-8.23))
- SSD20X SDK V30 version
- **res is the compiled application, which can be run directly on SSD20x**

### Decompress, configure and compile
- SSL is not supported. If you need to enable SSL support, you must modify and compile it yourself.
```shell
#
tar -zxvf iperf-3.10.1.tar.gz
cd iperf-3.10.1/
mkdir build

./configure --host=arm-linux-gnueabihf \
CC=arm-linux-gnueabihf-gcc \
CXX=arm-linux-gnueabihf-g++ \
RANLIB=arm-linux-gnueabihf-ranlib \
STRIP=arm-linux-gnueabihf-strip \
ac_cv_func_malloc_0_nonnull=yes \
CFLAGS=-static \
CXXFLAGS=-static \
--with-openssl=no \
--prefix=$PWD/build

make -j8
make install
```

# Instructions
### Test command
e.g.:
```
Client:
iperf3 -c 192.168.1.100 -l50 -i1 -b100k -u -t14400 -p10000
server:
iperf3 -s -p10000 -i1 -V > D.txt
```
### iperf Done.
- Parameters
```
-p, --port #, the port number for server monitoring and client connection;

-f, --format [kmgKMG], the data unit used in the report, Kbits, Mbits, KBytes, Mbytes;

-i, --interval #, the interval for each report, in seconds;

-F, --file name, the file name of the file used for testing. If used on the client side, the file is sent for testing; if used on the server side, the data is written to the file instead of discarded;

-A, --affinity n/n,m, set CPU affinity;

-B, --bind, bind the specified network card interface;

-V, --verbose, output more details when running;

-J, --json, output the results in JSON format during runtime;

--logfile f, output to file;

-d, --debug, output results in debug mode;

-v, --version, display version information and exit;

-h, --help, display help information and exit.
```
- Server side parameters:
```
-s, --server, run in Server mode;

-D, --daemon, runs as a daemon process in the background;

-I, --pidfile file, specify the pid file;

-1, --one-off, accept only 1 test from the client and then exit.
```
- clinet side parameters
```
-c, --client, run in Client mode and specify the address of the Server;

-u, --udp, test with UDP protocol;

-b, --bandwidth #[KMG][/#], limit the test bandwidth. UDP defaults to 1Mbit/second, TCP defaults to unlimited;

-t, --time #, use time as the test end condition for testing, the default is 10 seconds;

-n, --bytes #[KMG], test based on the data transfer size as the test end condition;

-k, --blockcount #[KMG], test based on the number of transmitted data packets as the test end condition;

-l, --len #[KMG], the length of the read and write buffer, the default is 128K for TCP and 8K for UDP;

--cport, specify the TCP or UDP port used by the client to run, the default is a temporary port;

-P, --parallel #, test the number of concurrent data streams;

-R, --reverse, run in reverse mode (server sends, client receives);

-w, --window #[KMG], set the socket buffer size, which is the window size in TCP mode;

-C, --congestion, set the TCP congestion control algorithm (only supports Linux and FreeBSD);

-M, --set-mss #, set the TCP/SCTP maximum segment length (MSS, MTU minus 40 bytes);

-N, --no-delay, set TCP/SCTP no delay, shield Nagle algorithm;

-4, --version4, only use IPv4;

-6, --version6, only use IPv6;

-S, --tos N, set IP service type (TOS, Type Of Service);

-L, --flowlabel N, set IPv6 flow label (supports Linux only);

-Z, --zerocopy, use the "zero copy" method to send data;

-O, --omit N, ignore the first n seconds of testing;

-T, --title str, set the prefix of each line of test results;

--get-server-output, get the test results from the server;

--udp-counters-64bit, use 64-bit counters in UDP test packets (prevent counter overflow).
```
