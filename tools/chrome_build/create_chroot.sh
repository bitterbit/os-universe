cd chroot
mount -t proc proc ./proc
mount -t sysfs sysfs ./sys
mount -o bind /dev dev
#mknod -m 666 /dev/null c 1 3
#mknod -m 666 /dev/zero c 1 5 
#mknod -m 444 /dev/random c 1 8 
#mknod -m 444 /dev/urandom c 1 9 
chroot . /bin/bash
export PS1="\(chroot\) \w \$" 
