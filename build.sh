#!/bin/bash
HOME=$(pwd)
cd dpdk-stable-20.11.1
mkdir dpdklib                 # user desired install folder
mkdir dpdkbuild               # user desired build folder
meson -Denable_kmods=true -Dprefix=$(pwd)/dpdklib dpdkbuild
ninja -C dpdkbuild
cd dpdkbuild; ninja install
export PKG_CONFIG_PATH=$(pwd)/dpdk-stable-20.11.1/dpdklib/lib64/pkgconfig/

cd $HOME
make -j$(nproc)
