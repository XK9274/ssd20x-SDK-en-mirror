#valgrind Introduction
- algrind is a collection of open source (GPL V2) simulation and debugging tools under Linux. Valgrind consists of a core and other debugging tools based on the core. The kernel is similar to a framework, which simulates a CPU environment and provides services to other tools; while other tools are similar to plug-ins, using the services provided by the kernel to complete various specific memory debugging tasks ( Memory leak detection tool valgrind artifact - Zhihu https://zhuanlan.zhihu.com/p/75416381)
- Official website https://www.valgrind.org/
- User manual https://www.valgrind.org/docs/manual/valgrind_manual.html.tar.bz2
- Source code download https://sourceware.org/pub/valgrind/valgrind-3.17.0.tar.bz2 (latest release version: 2021-08-20)
- 2.2 Command introduction
    - Usage: valgrind[options] prog-and-args [options]: Common options, applicable to all Valgrind tools
    - -tool=<name> Most commonly used options. Run the tool named toolname in valgrind. Default memcheck.
    -h –help displays help information.
    - -version displays the version of the valgrind kernel, each tool has its own version.
    -q –quiet Run quietly, printing only error messages.
    -v –verbose provides more detailed information and increases error statistics.
    - -trace-children=no|yes Trace child threads? [no]
    - -track-fds=no|yes Track open file descriptions? [no]
    - -time-stamp=no|yes Add timestamp to LOG information? [no]
    - -log-fd=<number> Output LOG to descriptor file [2=stderr]
    - -log-file=<file> Write the output information to the file filename.PID. PID is the process ID of the running program.
    - -log-file-exactly=<file> Output LOG information to file
    - -log-file-qualifier=<VAR> Get the value of the environment variable as the file name of the output information. [none]
    - -log-socket=ipaddr:port output LOG to socket, ipaddr:port
    - LOG information output:
       - -xml=yes Output the information in xml format, only memcheck is available
       - -num-callers=<number> show <number> callers in stack traces [12]
       - -error-limit=no|yes Stop showing new errors if too many errors? [yes]
       - -error-exitcode=<number> Return error code [0=disable] if an error is found
       - -db-attach=no|yes When an error occurs, valgrind will automatically start the debugger gdb. [no]
       - -db-command=<command> Command line option to start the debugger [gdb -nw %f %p]
    - Related options for Memcheck tool:
       - -leak-check=no|summary|full Ask for detailed information about leak? [summary]
       - -leak-resolution=low|med|high how much bt merging in leak check [low]
       - -show-reachable=no|yes show reachable blocks in leak check? [no]
# Ubuntu environment setup
- Download valgrind and execute the following commands to install it.
```shell
tar -xvf valgrind-3.17.0.tar.bz2
cd valgrind-3.17.0/
./configure
sudo make -j8
sudo make install
```
- Execute the `valgrind --version` command to check whether the installation is successful

# test case
### 1. Memory out of bounds, memory leak
- test code
```c
   1 #include <stdio.h>
   2 #include <stdlib.h>
   3 void func()
   4 {
   5 char *a= malloc(8);
   6 a[8] = 9; //Memory out of bounds
   7 }//Memory leak
   8 
   9 int main(int argc, char *argv[])
  10 {
  11 func();
  12 return 0;
  13}
```
- Compilation and testing
```shell
# -g: Indicates the use of gdb, and only in valgrind can the specific exception location be realized.
gcc main.c -o main -g
# --tool=memcheck: Indicates using the memory detection tool
# --leak-check=full: Indicates all leak checks
valgrind --tool=memcheck --leak-check=full ./main
```
-The output results are as follows
    - `Invalid write of size 1` means that the memory is out of bounds by one byte. The following at can be traced to the specific location of the problem `at 0x10916B: func (main.c:6)` in the sixth line of the man.c file
    - `8 bytes in 1 blocks are definitely lost in loss record 1 of 1` means that the applied memory is lost (memory leak). You can see the location of the applied memory later.
    - `HEAP SUMMARY` heap summary
    - `LEAK SUMMARY` Leak summary
```c
==54392== Memcheck, a memory error detector
==54392== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==54392== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==54392== Command: ./main
==54392==
==54392== Invalid write of size 1
==54392== at 0x10916B: func (main.c:6)
==54392== by 0x10918D: main (main.c:11)
==54392== Address 0x4a5a048 is 0 bytes after a block of size 8 alloc'd
==54392== at 0x483C855: malloc (vg_replace_malloc.c:380)
==54392== by 0x10915E: func (main.c:5)
==54392== by 0x10918D: main (main.c:11)
==54392==
==54392==
==54392== HEAP SUMMARY:
==54392== in use at exit: 8 bytes in 1 blocks
==54392== total heap usage: 1 allocs, 0 frees, 8 bytes allocated
==54392==
==54392== 8 bytes in 1 blocks are definitely lost in loss record 1 of 1
==54392== at 0x483C855: malloc (vg_replace_malloc.c:380)
==54392== by 0x10915E: func (main.c:5)
==54392== by 0x10918D: main (main.c:11)
==54392==
==54392== LEAK SUMMARY:
==54392== definitely lost: 8 bytes in 1 blocks
==54392== indirectly lost: 0 bytes in 0 blocks
==54392== possibly lost: 0 bytes in 0 blocks
==54392== still reachable: 0 bytes in 0 blocks
==54392== suppressed: 0 bytes in 0 blocks
==54392==
==54392== For lists of detected and suppressed errors, rerun with: -s
==54392== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
### 2. Read the memory after it is released
- test code
```c
   1 #include <stdio.h>
   2 #include <stdlib.h>
   3 void func()
   4 {
   5 char *a= malloc(1);
   6 *a = '1';
   7 printf("%c\r\n",*(1+a));
   8 free(a);
   9 printf("%c\r\n",*a);
  10}
  11
  12 int main(int argc, char *argv[])
  13 {
  14 func();
  15 return 0;
  16}
```
- Compilation test
```shell
# -g: Indicates the use of gdb, and only in valgrind can the specific exception location be realized.
gcc main.c -o main -g
# --tool=memcheck: Indicates using the memory detection tool
# --leak-check=full: Indicates all leak checks
valgrind --tool=memcheck --leak-check=full ./main
```
-The output results are as follows
    - `Invalid read of size 1` means that after the memory is released, it is still read (or out of bounds read), and the specific exception location can be seen later.
```c
==54947== Memcheck, a memory error detector
==54947== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==54947== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==54947== Command: ./main
==54947==
==54947== Invalid read of size 1
==54947== at 0x1091B2: func (main.c:7)
==54947== by 0x109213: main (main.c:14)
==54947== Address 0x4a5a041 is 0 byte
s after a block of size 1 alloc'd
==54947== at 0x483C855: malloc (vg_replace_malloc.c:380)
==54947== by 0x10919E: func (main.c:5)
==54947== by 0x109213: main (main.c:14)
==54947==

==54947== Invalid read of size 1
==54947== at 0x1091DB: func (main.c:9)
==54947== by 0x109213: main (main.c:14)
==54947== Address 0x4a5a040 is 0 bytes inside a block of size 1 free'd
==54947== at 0x483F0C3: free (vg_replace_malloc.c:755)
==54947== by 0x1091D6: func (main.c:8)
==54947== by 0x109213: main (main.c:14)
==54947== Block was alloc'd at
==54947== at 0x483C855: malloc (vg_replace_malloc.c:380)
==54947== by 0x10919E: func (main.c:5)
==54947== by 0x109213: main (main.c:14)
==54947==
1
==54947==
==54947== HEAP SUMMARY:
==54947== in use at exit: 0 bytes in 0 blocks
==54947== total heap usage: 2 allocs, 2 frees, 1,025 bytes allocated
==54947==
==54947== All heap blocks were freed -- no leaks are possible
==54947==
==54947== For lists of detected and suppressed errors, rerun with: -s
==54947== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

# Cross compilation method
- Take SSD20x V030 version as an example

### Decompress, configure and compile
```shell
#
tar -xvf valgrind-3.17.0.tar.bz2
cd valgrind-3.17.0/
mkdir build
#vim Modify armv7 to arm as follows
vim configure
./configure CC=arm-linux-gnueabihf-gcc --host=arm-linux --prefix=$PWD/build
make -j8
make install
```
-vim configure is modified as follows
    - Modify line 5968 as follows
```makefile
  5968 arm*)
  5969 { $as_echo "$as_me:${as_lineno-$LINENO}: result: ok (${host_cpu})" >&5
  5970 $as_echo "ok (${host_cpu})" >&6; }
  5971 ARCH_MAX="arm"
  5972;;

```
### Error description
- The error `valgrind: failed to start tool 'memcheck' for platform 'arm-linux': Not a directory` is prompted during execution because the lib library cannot be found. When using it, you need to set the path to libexec additionally, as shown below
- libexec is too big and will not be uploaded here. You can cross-compile it yourself if necessary.
```
# Set the location of the libexec environment variable, otherwise it cannot be used. You need to modify it according to the position of your own board.
export VALGRIND_LIB="/vendor/res/libexec/valgrind"
# Test, only if the version can be printed out normally.
./valgrind --version
```

- The version can be printed normally, but an error will be reported after testing the command `/valgrind ls -l`, as shown below
```
==870== Memcheck, a memory error detector
==870== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==870== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==870== Command: ../../main
==870==

valgrind: Fatal error at startup: a function redirection
valgrind: which is mandatory for this platform-tool combination
valgrind: cannot be set up. Details of the redirection are:
valgrind:
valgrind: A must-be-redirected function
valgrind: whose name matches the pattern: index
valgrind: in an object with soname matching: ld-linux-armhf.so.3
valgrind: was not found whilst processing
valgrind: symbols from the object with soname: ld-linux-armhf.so.3
valgrind:
valgrind: Possible fixes: (1, short term): install glibc's debuginfo
valgrind: package on this machine. (2, longer term): ask the packagers
valgrind: for your Linux distribution to please ship a non-
valgrind: stripped ld.so (or whatever the dynamic linker .so is called)
valgrind: that exports the above-named function using the standard
valgrind: calling conventions for this platform. The package you need
valgrind: to install for fix (1) is called
valgrind:
valgrind: On Debian, Ubuntu: libc6-dbg
valgrind: On SuSE, openSuSE, Fedora, RHEL: glibc-debuginfo
valgrind:
valgrind: Note that if you are debugging a 32 bit process on a
valgrind: 64 bit system, you will need a corresponding 32 bit debuginfo
valgrind: package (e.g. libc6-dbg:i386).
valgrind:
valgrind: Cannot continue -- exiting now. Sorry.

```
- The above error is because there is no libc6-dbg, so you need to install libc6-dbg again, which also requires gdb. If you use gdb later, you can transplant it.
