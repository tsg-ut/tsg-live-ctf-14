#!/bin/sh

cd /home/user
timeout --foreground -s 9 60s stdbuf -i0 -o0 -e0 qemu-system-x86_64 \
  -kernel ./bzImage \
  -initrd ./rootfs.cpio \
  -nographic \
  -monitor /dev/null \
  -cpu kvm64,-smep,-smap \
  -net nic,model=virtio \
  -net user \
  -append "console=ttyS0 nokaslr oops=panic panic=1 quiet nopti" \
  -no-reboot \
  -m 64M
