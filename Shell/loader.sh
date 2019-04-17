#!/bin/bash
# your real command here, instead of sleep
clear;
sleep 1 &
PID=$!
i=1
sp="/-\|"
echo -n ' '
printf "\n\n\n\n\n\t\t\t\t\t"
while [ -d /proc/$PID ]
do
  printf "\b${sp:i++%${#sp}:1}"
done