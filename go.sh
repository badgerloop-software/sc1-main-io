#!/bin/bash

./bloop-dev cross && rsync -a out debian@beaglebone.local:~/pod-embedded-beta
