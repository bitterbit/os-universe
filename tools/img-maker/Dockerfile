FROM debian
RUN apt-get update
RUN apt-get install -y wget git gcc make syslinux syslinux-utils genisoimage isolinux 
RUN apt-get install -y syslinux-efi 

ENV HOME=/root
WORKDIR $HOME

RUN mkdir stage1 stage2 out 

#################### createEfiImage / image ####################

RUN git clone https://github.com/xobs/genfatfs.git
RUN cd genfatfs && make && cp genfatfs /bin/

ADD out/bzImage                 stage1/bzImage
ADD out/rootfs-chrome.cpio.gz   stage1/initrd.img
ADD syslinux.cfg                stage1/syslinux.cfg
#RUN cp /usr/lib/SYSLINUX.EFI/efi64/syslinux.efi    stage1/
#RUN cp /usr/lib/syslinux/modules/efi64/ldlinux.e64 stage1/

# Size in KB, round up to 1024K align + 1024
# RUN size=$(du -ks input/ | cut -f1)  && echo $size
# TODO: round up
# Note: if rootfs is big remeber to supply enough ram to open initramfs (in vmware, qemu, etc...)

RUN genfatfs -b 256000 --root stage1/ stage2/boot.img
RUN cp stage2/boot.img out/boot.img
RUN syslinux --install out/boot.img

#################### output: output/boot.img  ####################
####################      createIsoImage      ####################

RUN cp stage1/* stage2/
RUN cp /usr/lib/ISOLINUX/isolinux.bin stage2/
RUN cp /usr/lib/syslinux/modules/bios/ldlinux.c32 stage2/

RUN genisoimage -V os-universe \
    -b isolinux.bin      \
      -no-emul-boot      \
      -boot-load-size 4  \
      -boot-info-table   \
    -c boot.cat     \ 
    -o out/boot.iso \
    stage2/ 

RUN isohybrid out/boot.iso 
RUN echo "Done"
