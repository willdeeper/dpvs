#!/bin/bash
# 删除debian内置的dpdk
# 避免include header冲突
sudo apt remove libdpdk-dev -y
sudo apt autoremove
sudo apt install meson ninja-build libnuma-dev libpopt-dev linux-headers-$(uname -r) -y

cp patch/dpdk-stable-20.11.1/*.patch dpdk
cd dpdk
patch -p1 -f < 0001-kni-use-netlink-event-for-multicast-driver-part.patch
patch -p1 -f < 0002-pdump-change-dpdk-pdump-tool-for-dpvs.patch