#!/bin/bash
export DPDK_NAME=dpdk
export PKG_CONFIG_PATH=$(pwd)/$DPDK_NAME/dpdklib/lib/x86_64-linux-gnu/pkgconfig
HOME=$(pwd)

cd $DPDK_NAME
mkdir dpdklib                 # user desired install folder
mkdir dpdkbuild               # user desired build folder
meson -Denable_kmods=true -Dprefix=$(pwd)/dpdklib dpdkbuild
ninja -C dpdkbuild
cd dpdkbuild; ninja install

cd $HOME
make -j$(nproc)
make install