sudo mount -t vfat /dev/sdg1 /media/external -o uid=1000,gid=1000,utf8,dmask=027,fmask=137
cp /tmp/CS631_Project03/kernel.img /media/external/
sudo umount /dev/sdg1
