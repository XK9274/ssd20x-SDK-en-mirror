# 交叉编译

## 环境

- ubuntu20.04
- 交叉编译工具 arm-linux-gnueabihf-gcc 8.2.1 20180802 (GNU Toolchain for the A-profile Architecture 8.2-2018-08 (arm-rel-8.23))

## 下载

- 下载地址 https://github.com/libts/tslib.git


### 解压、配置编译

```shell
# 
git clone https://github.com/libts/tslib.git
cd tslib
./autogen.sh
mkdir build
./configure CC=arm-linux-gnueabihf-gcc --host=arm-linux --prefix=$PWD/build
#./configure CC=arm-none-linux-gnueabihf-gcc --host=arm-none-linux --prefix=$PWD/build
make -j8
make install 
```