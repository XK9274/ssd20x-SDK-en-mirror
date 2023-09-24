# Summary
### common
- Watchdog general API, you can copy it directly and use it yourself
### watchdog_test1
- Simple watchdog demo, set the watchdog time to 20 seconds, and do not feed the dog
### watchdog_test2
- Command form, test watchdog, the specific command format can be seen in the prompt after running.
# Instructions for use
### Kernel configuration
- Execute make menuconfig to open the watchdog driver (Device Drivers --->[*] SStar SoC platform drivers ---><*> watchdog driver)
- After recompiling and burning the kernel, /dev/watchdog existing on the board can be seen
### limit
- The current minimum time is 5 seconds and the maximum time is 357 seconds (driver limit, it will overflow after setting exceeds 357 seconds. If 400 seconds is set, the actual setting is 400-357=43 seconds)
