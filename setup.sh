#!/bin/bash
sudo apt purge libdpdk-dev -y
sudo apt install meson ninja-build linux-headers-$(uname -r) -y
cp patch/dpdk-stable-20.11.1/*.patch dpdk-stable-20.11.1/
cd dpdk-stable-20.11.1/
patch -p1 -f < 0001-kni-use-netlink-event-for-multicast-driver-part.patch
patch -p1 -f < 0002-pdump-change-dpdk-pdump-tool-for-dpvs.patch