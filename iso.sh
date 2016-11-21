#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/moonix.kernel isodir/boot/moonix.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "Moonix" {
	multiboot /boot/moonix.kernel
}
EOF
grub-mkrescue -o moonix.iso isodir
