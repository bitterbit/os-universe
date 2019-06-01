echo "folder2img"

if [[ $(file image.img) = *"ext4 filesystem"* ]]; then
    echo "image already ext4, skipping"
else
    mkfs.ext4 -F image.img
fi

mount -o loop /root/image.img /mnt/img
rsync folder/* /mnt/img/ -l --update --progress
umount /mnt/img
echo "Done"
