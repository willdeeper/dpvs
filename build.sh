#!/bin/bash
set -xe
export DPDK_NAME=dpdk
export PKG_CONFIG_PATH=$(pwd)/$DPDK_NAME/dpdklib/lib/x86_64-linux-gnu/pkgconfig

HOME=$(pwd)

cd $DPDK_NAME
# 高版本bear用 bear -- bash -c
bear ninja -C dpdkbuild\
&& cd dpdkbuild && ninja install\
&& cd $HOME \
&& make -j$(nproc)
cd $HOME;
make install