#!/bin/bash
workdir=`pwd`
echo $workdir
cd lemon-1.2
./configure --prefix="$workdir/lemon"
make
make install
cp -rl "$workdir/lemon" "$workdir/lemon$1"
