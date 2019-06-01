mkfs.ext4 -F image.img
mount -o loop /root/image.img /mnt/img
rsync folder/* /mnt/img/ -l --progress
umount /mnt/img
echo "Done"
