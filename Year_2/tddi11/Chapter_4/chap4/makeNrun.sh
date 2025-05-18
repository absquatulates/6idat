#!/bin/bash

clear
echo "This script includes commands to make the project and run it"

echo "clean up the directory with make clean"
make clean
echo "make the project with make."
make
echo "Guiding mtools mcopy to its configuration file"
export MTOOLSRC=mtools.conf
echo "Copying the binary to floppy image"
/courses/TDDI11/sw/bin/mcopy embedded.bin a:
echo "Duplicating the floppy image"
cp floppy.img floppy_copy.img
echo "We assume port 50152 is free. Check below, if it is not free, select another port"
netstat | grep ":50152"
echo "Proceeding with port 50152 on localhost=127.0.0.1"
echo "Starting Qemu with given binary in the floppy image, as server"
qemu-system-i386 -drive format=raw,file=floppy.img,if=floppy -serial tcp:127.0.0.1:50152,server,nowait &
echo "Starting another Qemu with given binary in the floppy image, as client. Wait a second for server to connect"
sleep 1
qemu-system-i386 -drive format=raw,file=floppy_copy.img,if=floppy -serial tcp:127.0.0.1:50152 &
