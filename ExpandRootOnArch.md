# How to Expand Root on Arch

```
sudo fdisk /dev/mmcblk0
p
d
2
n
e
2
default
default
n
l
default
default
p
w
sudo reboot
...
sudo resize2fs /dev/mmcblk0p5
df
```
