qemu-system-x86_64 \
  -kernel out/bzImage \
  -initrd out/rootfs-chrome.cpio.gz \
  -m size=2048 \
  -netdev user,id=un0,net=10.7.0.0/24,host=10.7.0.177  \
  -device e1000e,netdev=un0  \
  -device virtio-scsi-pci,id=scsi \
  -device scsi-hd,drive=hd \
  -drive media=disk,file=out/chrome.img,if=none,id=hd \
  -nographic -append "console=ttyS0"
