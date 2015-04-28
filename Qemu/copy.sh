sudo mount -t vfat /dev/mmcblk0p1 /media/external -o uid=1000,gid=1000,utf8,dmask=027,fmask=137
cp /home/kaijiezhou/cs631/project03/CS631_Project03/Qemu/kernel.img /media/external/
sudo umount /dev/mmcblk0p1
