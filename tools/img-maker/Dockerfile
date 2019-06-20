FROM debian
RUN apt-get update
RUN apt-get install -y wget git gcc make syslinux

ENV HOME=/root
WORKDIR $HOME

RUN git clone https://github.com/xobs/genfatfs.git
RUN cd genfatfs && make && cp genfatfs /bin/

RUN mkdir input output 

ADD out/bzImage                 input/bzImage
ADD out/rootfs-chrome.cpio.gz   input/rootfs.cpio.gz
ADD syslinux.cfg                input/syslinux.cfg

# Size in KB, round up to 1024K align + 1024
# Size = $(du -ks input/ | cut -f1)
# TODO: round up
# Note: if rootfs is big remeber to supply enough ram to open initramfs (in vmware, qemu, etc...)

RUN genfatfs -b 256000 --root input/ output/boot.img
RUN syslinux --install output/boot.img
