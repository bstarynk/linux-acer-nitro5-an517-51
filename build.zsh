#!/bin/zsh -x
# in https://github.com/bstarynk/linux-acer-nitro5-an517-51

### USE AT YOUR OWN RISK. IT COULD DAMAGE YOUR LAPTOP

## a GPLv3+ script that you need to adapt to your system! It should
## buid a bootable image

LINUX_KERNEL_SRCDIR=/usr/src/Kernel/linux-5.4.14
NBCORES=$(lscpu|awk '/^Core/{print $4}')

function build_kernel() {
    printf "you have %d cores\n" $NBCORES
    cp $LINUX_KERNEL_SRCDIR/.config my-$(basename $LINUX_KERNEL_SRCDIR)-config
    loadkeys -s -d > $LINUX_KERNEL_SRCDIR/drivers/tty/vt/defkeymap.c
    pushd $LINUX_KERNEL_SRCDIR
    make -j $[$NBCORES / 2] vmlinux
    popd
}



build_kernel

## end of file build.zsh
