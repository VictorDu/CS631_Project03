sudo mount -t vfat /dev/sde1 /media/external -o uid=1000,gid=1000,utf8,dmask=027,fmask=137
cp /home/kaijiezhou/Desktop/CS631_Project03/BareMetal/kernel.img /media/external/
sudo umount /dev/sde1
