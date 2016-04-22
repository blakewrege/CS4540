#!/bin/bash
#Creates, loads, and removes kernel module
#NOTE: run as sudo
dmesg -c
make
insmod ProjectA6.ko
rmmod ProjectA6
dmesg > dmesg-output.txt
cat dmesg-output.txt

