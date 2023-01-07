#!/bin/bash


DEVICE="/config/gpio-sim/gpio-device"
CHIP0="$DEVICE/gpiochip0"
LINE0="$CHIP0/line0"


sudo su - << EOF
modprobe gpio-sim
mkdir /config
mount -t configfs none /config
mkdir -p $LINE0
echo 1 > $DEVICE/live
echo 1 > $CHIP0/num_lines
EOF
