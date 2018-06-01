#!/bin/bash

echo "$1" > /sys/class/gpio/export
echo gpio : $1
echo "out" > /sys/class/gpio/gpio$1/direction

for ((i=0; i<10; i++)) ; do
	echo "1" > /sys/class/gpio/gpio$1/value
	echo LED ON
	sleep 1
	echo "0" > /sys/class/gpio/gpio$1/value
	echo LED OFF
	sleep 1
done; 

echo "$1" > /sys/calss/gpio/unexport
