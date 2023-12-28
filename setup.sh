#!/bin/bash
git submodule update --init --remote --recursive --progress
# 删除debian内置的dpdk
# 避免include header冲突
sudo apt update
sudo apt remove libdpdk-dev -y
sudo apt autoremove
sudo apt install pkg-config python3-pip meson ninja-build libnuma-dev libpopt-dev linux-headers-$(uname -r) -y
pip3 install pyelftools
cd dpdk
git clean -df
git checkout .
cp ../patch/dpdk-stable-20.11.1/*.patch ./
patch -p1 < 0001-kni-use-netlink-event-for-multicast-driver-part.patch
patch -p1 < 0002-pdump-change-dpdk-pdump-tool-for-dpvs.patch
rm -rf dpdk/dpdklib
rm -rf dpdk/dpdkbuild