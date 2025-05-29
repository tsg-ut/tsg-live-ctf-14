#!/bin/sh

cd /home/user
#timeout --foreground -s 9 600000s stdbuf -i0 -o0 -e0 ./traditional_fork_chall # debug
 timeout --foreground -s 9 60s stdbuf -i0 -o0 -e0 ./traditional_fork_chall
