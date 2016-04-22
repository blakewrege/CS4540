#!/bin/bash
#Creates, loads, and removes kernel module
sudo dmesg -c
make
sudo insmod ProjectA6.ko
sudo rmmod ProjectA6
sudo dmesg > dmesg-output.txt
chown blake dmesg-output.txt
cat dmesg-output.txt

