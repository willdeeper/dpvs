#!/bin/bash
set -xe
export DPDK_NAME=dpdk
export PKG_CONFIG_PATH=$(pwd)/$DPDK_NAME/dpdklib/lib/x86_64-linux-gnu/pkgconfig

WORKDIR=$(pwd)

cd $DPDK_NAME
ninja  -C dpdkbuild -t compdb > $WORKDIR/compile_commands.json
cd dpdkbuild && ninja install
cd $WORKDIR
# 高版本bear用 bear -a --
bear -a make -j$(nproc)
make install