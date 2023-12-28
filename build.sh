#!/bin/bash
HOME=$(pwd)
apt install meson ninja-build linux-headers-$(uname -r) -y
cp patch/dpdk-stable-20.11.1/*.patch dpdk-stable-20.11.1/
cd dpdk-stable-20.11.1/
patch -p1 < 0001-kni-use-netlink-event-for-multicast-driver-part.patch
patch -p1 < 0002-pdump-change-dpdk-pdump-tool-for-dpvs.patch
cd ../
cd dpdk-stable-20.11.1
mkdir dpdklib                 # user desired install folder
mkdir dpdkbuild               # user desired build folder
meson -Denable_kmods=true -Dprefix=$(pwd)/dpdklib dpdkbuild
ninja -C dpdkbuild
cd dpdkbuild; ninja install
export PKG_CONFIG_PATH=$(pwd)/../dpdklib/lib64/pkgconfig/

cd $HOME
make -j$(nproc)
