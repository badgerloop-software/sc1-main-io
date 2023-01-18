#!/bin/bash

sudo modprobe i2c-dev
sudo modprobe i2c-stub chip_addr=0x24
