#!/bin/bash

# configfs directories
DEVICE="/config/gpio-sim/gpio-device"
CHIP0="$DEVICE/gpiochip0"
CHIP1="$DEVICE/gpiochip1"
LINE0="$CHIP0/line0"
LINE1="$CHIP0/line1"
LINE2="$CHIP0/line2"
LINE62="$CHIP1/line30"
LINE63="$CHIP1/line31"

# line manipulation
_DEVICE="/sys/devices/platform/gpio-sim.0"
_CHIP0="$_DEVICE/gpiochip0"
_CHIP1="$_DEVICE/gpiochip1"
_LINE0="$_CHIP0/sim_gpio0"
_LINE62="$_CHIP1/sim_gpio30"
_LINE63="$_CHIP1/sim_gpio31"

# use rmdir (not rm -r) and mkdir to test your own configs
sudo su - << EOF
modprobe gpio-sim
[ -d /config ] || mkdir /config
mount -t configfs none /config
mkdir -p $DEVICE
echo 0 > $DEVICE/live
mkdir -p $LINE0
mkdir -p $LINE1
mkdir -p $LINE2
mkdir -p $LINE62
mkdir -p $LINE63
echo 32 > $CHIP0/num_lines
echo 32 > $CHIP1/num_lines
echo 1 > $DEVICE/live
echo 'pull-up' > $_LINE0/pull
echo 'pull-up' > $_LINE62/pull
echo 'pull-down' > $_LINE63/pull
EOF
