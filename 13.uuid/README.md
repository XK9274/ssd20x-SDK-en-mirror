# Summary

- UUID chip unique identification
- The original factory provides three ways to read UUID, see the official documentation
- The UUID is 6 bytes, and the mac setting requires 6 bytes of data. It can be set to MAC, which saves the time of setting up the MAC specifically for small projects.
- **The following three DEMOs refer to the original documents, read the UUID, and set it to the mac address of eth0**

## shell_uuid_to_mac

- Use the riu_r/riu_w register writing tool that comes with the SDK to directly read the UUID and set it to the MAC of eth0
- Script form, can be run directly on the public board
- Need to use awk, ifconfig, grep commands

## base_c_uuid_read

- Do not use the MI function, directly use basic C to read the UUID in the register
- After reading, set it to the MAC of eth0

## mi_sys_uuid_read

- Read UUID using MI function
- After reading, set it to the MAC of eth0

## other

- After verification, in this DEMO, the MAC set directly through UUID may fail to set
- The processing method can be found at https://blog.csdn.net/qq_33611327/article/details/78357755
