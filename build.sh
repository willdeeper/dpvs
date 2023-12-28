#!/bin/bash
set -xe
export DPDK_NAME=dpdk
export PKG_CONFIG_PATH=$(pwd)/$DPDK_NAME/dpdklib/lib/x86_64-linux-gnu/pkgconfig

HOME=$(pwd)

cd $DPDK_NAME
[ -d "dpdklib" ] || mkdir -p dpdklib
[ -d "dpdkbuild" ] || mkdir dpdkbuild
meson -Denable_kmods=true -Dprefix=$(pwd)/dpdklib dpdkbuild
ninja -C dpdkbuild
cd dpdkbuild; ninja install
cd $HOME
make -j$(nproc)
make install